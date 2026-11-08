#include <hidapi/hidapi.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOFLE_VID 0xFC32
#define SOFLE_PID 0x0287
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE 0x61
#define REPORT_SIZE 32
#define COMMAND_SET_HSV 0xA1

static int parse_hex_rgb(const char *text, uint8_t *r, uint8_t *g, uint8_t *b) {
    if (*text == '#') {
        text++;
    }

    if (strlen(text) != 6) {
        return 0;
    }

    char *end = NULL;
    unsigned long value = strtoul(text, &end, 16);
    if (end != text + 6) {
        return 0;
    }

    *r = (value >> 16) & 0xFF;
    *g = (value >> 8) & 0xFF;
    *b = value & 0xFF;
    return 1;
}

static void rgb_to_qmk_hsv(uint8_t r8, uint8_t g8, uint8_t b8, uint8_t *h, uint8_t *s, uint8_t *v) {
    float r = r8 / 255.0f;
    float g = g8 / 255.0f;
    float b = b8 / 255.0f;
    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float delta = max - min;
    float hue = 0.0f;

    if (delta > 0.0f) {
        if (max == r) {
            hue = (g - b) / delta;
            if (hue < 0.0f) hue += 6.0f;
        } else if (max == g) {
            hue = (b - r) / delta + 2.0f;
        } else {
            hue = (r - g) / delta + 4.0f;
        }
        hue /= 6.0f;
    }

    *h = (uint8_t)(hue * 255.0f);
    *s = max == 0.0f ? 0 : (uint8_t)((delta / max) * 255.0f);
    *v = (uint8_t)(max * 255.0f);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s '#RRGGBB'\n", argv[0]);
        return 2;
    }

    uint8_t r, g, b, h, s, v;
    if (!parse_hex_rgb(argv[1], &r, &g, &b)) {
        fprintf(stderr, "Invalid RGB color: %s\n", argv[1]);
        return 2;
    }
    rgb_to_qmk_hsv(r, g, b, &h, &s, &v);

    if (hid_init() != 0) {
        fputs("Could not initialize hidapi\n", stderr);
        return 1;
    }

    struct hid_device_info *devices = hid_enumerate(SOFLE_VID, SOFLE_PID);
    hid_device *keyboard = NULL;
    for (struct hid_device_info *device = devices; device; device = device->next) {
        if (device->usage_page == RAW_USAGE_PAGE && device->usage == RAW_USAGE) {
            keyboard = hid_open_path(device->path);
            if (keyboard) break;
        }
    }
    hid_free_enumeration(devices);

    if (!keyboard) {
        fputs("Sofle Raw HID interface not found or could not be opened\n", stderr);
        hid_exit();
        return 1;
    }

    // hidapi prepends the zero report ID; QMK receives the following 32 bytes.
    unsigned char request[REPORT_SIZE + 1] = {0};
    request[1] = COMMAND_SET_HSV;
    request[2] = h;
    request[3] = s;
    request[4] = v;

    int written = hid_write(keyboard, request, sizeof(request));
    if (written != (int)sizeof(request)) {
        fputs("Could not send the RGB command to the Sofle\n", stderr);
        hid_close(keyboard);
        hid_exit();
        return 1;
    }

    unsigned char response[REPORT_SIZE + 1] = {0};
    int received = hid_read_timeout(keyboard, response, sizeof(response), 500);
    // hidapi returns unnumbered QMK Raw HID reports without a report-ID byte.
    int acknowledged = received >= 4 && response[0] == COMMAND_SET_HSV &&
                       response[1] == h && response[2] == s && response[3] == v;

    hid_close(keyboard);
    hid_exit();

    if (!acknowledged) {
        fputs("Sofle did not acknowledge the RGB command\n", stderr);
        return 1;
    }
    return 0;
}
