/* Copyright 2021 Dane Evans
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H
#include "keymap_us.h"

// Omarchy: SUPER + CTRL + ENTER abre/adjunta la sesión de Herdr.
#define KC_HERDR LGUI(LCTL(KC_ENT))

enum sofle_layers { _QWERTY = 0, _LOWER, _RAISE, _ADJUST, _NUMPAD };

enum custom_keycodes { KC_LOWER = SAFE_RANGE, KC_RAISE };

#ifdef RGB_MATRIX_ENABLE
static bool rgb_adjust_dirty = false;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-------------------------------------------.                  ,-----------------------------------------.
     * |  Caps   |  1  |  2  |  3  |  4  |  5  |                  |  6  |  7  |  8  |  9  |  0  | Bspc |
     * |--------+------+------+------+------+------|                  |------+------+------+------+------+------|
     * |   TAB  |   Q  |   W  |   E  |   R  |   T  |                  |   Y  |   U  |   I  |   O  |   P  |  `   |
     * |--------+------+------+------+------+------|                  |------+------+------+------+------+------|
     * |CTRL-ESC|   A  |   S  |   D  |   F  |   G  |-------.  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |--------+------+------+------+------+------|Middle |  |Ctrl(F)|------+------+------+------+------+------|
     * |  LSFT  |   Z  |   X  |   C  |   V  |   B  |-------|  |-------|   N  |   M  |   ,  |   .  |   /  | RSFT |
     * `-----------------------------------------/        /    \      \`-----------------------------------------/'
     *           |HERDR | WIN | LAlt |LOWER |  / Space  /       \Enter \ |RAISE |NUMPAD| RAlt | Menu |
     *           |      |     |      |      |/       /          \      \|      |      |      |      |
     *           `----------------------------------'             '------''---------------------------'
     */
    [_QWERTY] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_CAPS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MS_BTN3, C(KC_F), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_HERDR, GUI_T(KC_ENT), KC_LALT, KC_LOWER, KC_SPC, GUI_T(KC_ENT), KC_RAISE, MO(_NUMPAD), KC_RALT, KC_APP
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* LOWER - navegacion y edicion
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | trans|  1  |  2  |  3  |  4  |  5  |                    |  6  |  7  |  8  |  9  |  0  |Delete|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|C+Hm |C+End |C+S < |C+S > | C+0  |                    |      | Home |  Up  |  End |      | Ps Cr|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|C+Bsp |C+Del |      |      |      |-------.    ,-------|Ctrl <| Left | Down | Right|Ctrl >|Insert|
     * |------+------+------+------+------+------|C+W key|    |C+T key|------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------|    |-------|      | BCSP |      |  DEL |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      |      | LAlt |LOWER | / Space /       \Enter \ |RAISE |NUMPAD| RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_LOWER] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, C(KC_HOME), C(KC_END), C(LSFT(KC_LEFT)), C(LSFT(KC_RGHT)), C(KC_0), KC_NO, KC_HOME, KC_UP, KC_END, KC_NO, KC_PSCR,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, C(KC_BSPC), C(KC_DEL), KC_NO, KC_NO, KC_NO, LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_RGHT), KC_INS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(KC_W), C(KC_T), KC_NO, KC_BSPC, KC_NO, KC_DEL, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* RAISE - simbolos en la mano izquierda
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   ~  |  !  |  @  |  #  |  $  |  %  |                    |  ^  |  &  |  *  |  (  |  )  |   _  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|  {  |  }  |  [  |  ]  |  *  |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|  (  |  )  |  =  |  +  |  -  |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|  ? key|    |C+S key|------+------+------+------+------+------|
     * | trans|  \  |  |  |  <  |  >  |  :  |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      |      | LAlt |LOWER | / Space /       \Enter \ |RAISE |NUMPAD| RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_RAISE] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_ASTR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_LPRN, KC_RPRN, KC_EQL, KC_PLUS, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_BSLS, KC_PIPE, KC_LABK, KC_RABK, KC_COLN, KC_QUES, C(KC_S), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* ADJUST - RGB y boot
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      | bri ^|      |      |                    |      |      |      |      |      | BOOT |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      | bri v|      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | hue ^|sat ^ | bri ^|      |      |      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|Nxt mod|    | Toggle|------+------+------+------+------+------|
     * | hue v|sat v | bri v|      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      |      | LAlt |LOWER | / Space /       \Enter \ |RAISE |NUMPAD| RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_ADJUST] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_NO, KC_NO, KC_NO, KC_BRIU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_NO, KC_NO, KC_NO, KC_BRID, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        UG_HUEU, UG_SATU, UG_VALU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        UG_HUED, UG_SATD, UG_VALD, KC_NO, KC_NO, KC_NO, UG_NEXT, UG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* NUMPAD - F1-F12, numeros y media
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |      |      |      |      |      |   +  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |                    | Mute |   7  |   8  |   9  |      |   -  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------.    ,-------|  Ent |   4  |   5  |   6  |   .  |   *  |
     * |------+------+------+------+------+------|Mute key|   |Play key|------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------|    |-------|      |   0  |   1  |   2  |   3  |   /  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      |      | LAlt |LOWER | / Space /       \Enter \ |RAISE |NUMPAD| RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_NUMPAD] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PPLS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MUTE, KC_P7, KC_P8, KC_P9, KC_NO, KC_PMNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PENT, KC_P4, KC_P5, KC_P6, KC_PDOT, KC_PAST,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_MPLY, KC_NO, KC_P0, KC_P1, KC_P2, KC_P3, KC_PSLS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM berserk_logo[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0x40, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xC0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0xF0, 0xD0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x24, 0x7F, 0xFF, 0xF7, 0xF1, 0xF1, 0x01, 0x01, 0x01, 0x81, 0xF1, 0x71, 0x71, 0x31, 0x01, 0x01, 0x81, 0xC1, 0xE1, 0x31, 0x31, 0x01, 0x01, 0x00, 0x00, 0x20, 0x21, 0x21, 0x21, 0x31, 0x31, 0x3D, 0x39, 0x21, 0xE1, 0xE1, 0x21, 0x01, 0x01, 0x01, 0x21, 0x11, 0x01, 0x01, 0x81, 0xC1, 0x31, 0x0F, 0x01, 0x01, 0x21, 0x31, 0x21, 0x21, 0x21, 0x31, 0x21, 0x21, 0x71, 0x3F, 0x21, 0x01, 0x00, 0x00, 0x20, 0x20, 0x21, 0x21, 0x21, 0x21, 0x31, 0x3F, 0x31, 0xA1, 0xF3, 0x73, 0x01, 0x01, 0x01, 0x01, 0x21, 0x01, 0x01, 0x01, 0x81, 0xC1, 0x33, 0x03, 0x01, 0x01, 0x01, 0x0F, 0x87, 0xC3, 0xC3, 0xE1, 0xF1, 0xF1, 0xF9, 0xF9, 0xF9, 0xFD, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x17, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0xFF, 0xFF, 0x9F, 0x81, 0x80, 0x80, 0x80, 0x81, 0x80, 0x88, 0x88, 0x80, 0x80, 0x81, 0x87, 0xBF, 0xFE, 0xFE, 0xC0, 0x80, 0x80, 0x80, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x9E, 0x87, 0x83, 0xC1, 0xE0, 0xF8, 0xFC, 0xF4, 0xC0, 0x80, 0x02, 0x07, 0x0F, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0x0E, 0x80, 0xC0, 0xE0, 0xF0, 0xFE, 0xFE, 0xE4, 0x80, 0x80, 0x80, 0x8C, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0xCE, 0x9E, 0x07, 0x83, 0xC0, 0xE0, 0xF8, 0xFC, 0xE4, 0xC0, 0x80, 0x02, 0x0F, 0x1F, 0x3F, 0xE7, 0x80, 0x80, 0x80, 0x8C, 0x88, 0xF0, 0xE0, 0xE1, 0xC3, 0x83, 0x07, 0x8F, 0xDF, 0xFF, 0xFF, 0xFC, 0x7C, 0x6C, 0x40, 0xE0, 0xC0, 0xC0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x03, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x17, 0x13, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x07, 0x03, 0x03, 0x07, 0x0F, 0x1C, 0x38, 0x78, 0x3C, 0x1E, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x07, 0x03, 0x01, 0x01, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x78, 0x3C, 0x1F, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0B, 0x0B, 0x0F, 0x1F, 0x1F, 0x1F, 0x1B, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
    oled_write_raw_P(berserk_logo, sizeof(berserk_logo));
}

#define SPLASH_DURATION_MS 2000

static const char *layer_label(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            return PSTR("LOWER");
        case _RAISE:
            return PSTR("RAISE");
        case _ADJUST:
            return PSTR("ADJ");
        case _NUMPAD:
            return PSTR("NUM");
        default:
            return PSTR("QWRT");
    }
}

// QMK renders one dirty OLED block per update. Clearing the buffer every frame
// keeps marking every block dirty and starves the later ones, which shows up as
// garbage at the bottom edge. Instead we pad every line to full width and let
// the dirty-block diff update only what changed.
static char    oled_line_buf[24];
static uint8_t oled_line_pos;

static void oled_line_begin(void) {
    memset(oled_line_buf, ' ', sizeof(oled_line_buf));
    oled_line_pos = 0;
}

static void oled_line_puts(const char *text) {
    char c;
    while ((c = (char)pgm_read_byte(text++)) != '\0' && oled_line_pos < sizeof(oled_line_buf)) {
        oled_line_buf[oled_line_pos++] = c;
    }
}

static void oled_line_putnum(uint8_t value) {
    char    digits[4];
    uint8_t n = 0;
    if (value >= 100) {
        digits[n++] = '0' + value / 100;
    }
    if (value >= 10) {
        digits[n++] = '0' + (value / 10) % 10;
    }
    digits[n++] = '0' + value % 10;
    for (uint8_t i = 0; i < n && oled_line_pos < sizeof(oled_line_buf); i++) {
        oled_line_buf[oled_line_pos++] = digits[i];
    }
}

static void oled_line_flush(uint8_t line, uint8_t width) {
    oled_set_cursor(0, line);
    for (uint8_t i = 0; i < width; i++) {
        oled_write_char(oled_line_buf[i], false);
    }
}

// Master half: vertical 32x128 status panel.
static void print_master_status(void) {
    const uint8_t width = oled_max_chars();

    oled_line_begin();
    oled_line_puts(PSTR("RORS"));
    oled_line_flush(0, width);

    oled_line_begin();
    oled_line_puts(PSTR("----"));
    oled_line_flush(1, width);

    oled_line_begin();
    oled_line_puts(PSTR("LYR"));
    oled_line_flush(2, width);

    oled_line_begin();
    oled_line_puts(layer_label());
    oled_line_flush(3, width);

    oled_line_begin();
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_SHIFT) {
        oled_line_puts(PSTR("S"));
    }
    if (mods & MOD_MASK_CTRL) {
        oled_line_puts(PSTR("C"));
    }
    if (mods & MOD_MASK_ALT) {
        oled_line_puts(PSTR("A"));
    }
    if (mods & MOD_MASK_GUI) {
        oled_line_puts(PSTR("G"));
    }
    oled_line_flush(5, width);

#ifdef WPM_ENABLE
    oled_line_begin();
    oled_line_puts(PSTR("WPM"));
    oled_line_flush(9, width);

    oled_line_begin();
    oled_line_putnum(get_current_wpm());
    oled_line_flush(10, width);
#endif
}

// Slave half: horizontal 128x32 panel.
static void print_slave_panel(void) {
    const uint8_t width = oled_max_chars();

    oled_line_begin();
    oled_line_puts(PSTR("    SOFLE RGB"));
    oled_line_flush(0, width);

    oled_line_begin();
    oled_line_puts(PSTR("LAYER "));
    oled_line_puts(layer_label());
    oled_line_flush(1, width);

#ifdef RGB_MATRIX_ENABLE
    oled_line_begin();
    oled_line_puts(PSTR("FX "));
    oled_line_putnum(rgb_matrix_get_mode());
    oled_line_puts(PSTR("  HUE "));
    oled_line_putnum(rgb_matrix_get_hue());
    oled_line_flush(2, width);

    oled_line_begin();
    uint8_t filled = (uint16_t)rgb_matrix_get_hue() * 12 / 255;
    for (uint8_t i = 0; i < 12; i++) {
        oled_line_buf[oled_line_pos++] = (i < filled) ? '#' : '-';
    }
    oled_line_puts(PSTR(" V"));
    oled_line_putnum(rgb_matrix_get_val());
    oled_line_flush(3, width);
#endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_master_status();
        return false;
    }

    static bool     splash_done  = false;
    static uint32_t splash_start = 0;
    if (!splash_done) {
        if (splash_start == 0) {
            splash_start = timer_read32();
        }
        if (timer_elapsed32(splash_start) < SPLASH_DURATION_MS) {
            render_logo();
            return false;
        }
        splash_done = true;
        // Wipe the logo once before drawing the panel.
        oled_clear();
    }

    print_slave_panel();
    return false;
}

#endif

#ifdef RGB_MATRIX_ENABLE
// Encoder changes stay in RAM while Adjust is held; persist them once when the
// layer is released so we do not hammer the EEPROM on every detent.
static void rgb_save_adjust_if_done(void) {
    if (rgb_adjust_dirty && get_highest_layer(layer_state) != _ADJUST) {
        rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val());
        rgb_adjust_dirty = false;
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
#ifdef RGB_MATRIX_ENABLE
                rgb_save_adjust_if_done();
#endif
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
#ifdef RGB_MATRIX_ENABLE
                rgb_save_adjust_if_done();
#endif
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    if (index == 0) {
        switch (layer) {
            case _LOWER:
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(C(LSFT(KC_TAB)));
                }
                break;
            case _RAISE:
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
            case _NUMPAD:
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            case _ADJUST:
#ifdef RGB_MATRIX_ENABLE
                // tap_code16() cannot send quantum keycodes (UG_*); it would
                // only send the low byte (0x7823 -> KC_6, 0x7827 -> KC_0).
                if (clockwise) {
                    rgb_matrix_increase_hue_noeeprom();
                } else {
                    rgb_matrix_decrease_hue_noeeprom();
                }
                rgb_adjust_dirty = true;
#endif
                break;
            default: // _QWERTY
                if (clockwise) {
                    tap_code16(LALT(KC_TAB));
                } else {
                    tap_code16(LALT(LSFT(KC_TAB)));
                }
                break;
        }
        return false;
    }

    if (index == 1) {
        switch (layer) {
            case _LOWER:
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;
            case _RAISE:
                if (clockwise) {
                    tap_code16(C(KC_EQL));
                } else {
                    tap_code16(C(KC_MINS));
                }
                break;
            case _NUMPAD:
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;
            case _ADJUST:
#ifdef RGB_MATRIX_ENABLE
                if (clockwise) {
                    rgb_matrix_increase_val_noeeprom();
                } else {
                    rgb_matrix_decrease_val_noeeprom();
                }
                rgb_adjust_dirty = true;
#endif
                break;
            default: // _QWERTY
                if (clockwise) {
                    tap_code16(MS_WHLU);
                } else {
                    tap_code16(MS_WHLD);
                }
                break;
        }
        return false;
    }

    return false;
}

#endif

#ifdef RGB_MATRIX_ENABLE

typedef struct {
    uint8_t row;
    uint8_t col;
} led_pos_t;

static const led_pos_t lower_markers[]  = {{4, 3}, {7, 4}, {7, 3}, {7, 2}};
static const led_pos_t raise_markers[]  = {{9, 3}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
static const led_pos_t adjust_markers[] = {{4, 3}, {9, 3}, {5, 0}};
static const led_pos_t numpad_markers[] = {{9, 2}, {6, 4}, {6, 2}, {8, 3}, {8, 1}};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == _QWERTY) {
        // Base layer: let the configured effect run untouched.
        return false;
    }

    const led_pos_t *markers = NULL;
    uint8_t          count   = 0;
    switch (layer) {
        case _LOWER:
            markers = lower_markers;
            count   = ARRAY_SIZE(lower_markers);
            break;
        case _RAISE:
            markers = raise_markers;
            count   = ARRAY_SIZE(raise_markers);
            break;
        case _ADJUST:
            markers = adjust_markers;
            count   = ARRAY_SIZE(adjust_markers);
            break;
        case _NUMPAD:
            markers = numpad_markers;
            count   = ARRAY_SIZE(numpad_markers);
            break;
        default:
            return false;
    }

    HSV     base = rgb_matrix_get_hsv();
    uint8_t val  = rgb_matrix_get_val();
    uint8_t dim  = val / 6;

    // Dim the effect output so it stays visible but the markers stand out.
    HSV hsv = base;
    hsv.v   = dim;
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    // Markers use the theme accent at the user's current brightness.
    hsv.v = val;
    rgb   = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < count; i++) {
        uint8_t idx = g_led_config.matrix_co[markers[i].row][markers[i].col];
        if (idx != NO_LED && idx >= led_min && idx < led_max) {
            rgb_matrix_set_color(idx, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
}

#endif

#ifdef RAW_ENABLE
#    include "raw_hid.h"

// Omarchy sends this packet over QMK Raw HID:
//   byte 0: command (0xA1)
//   byte 1: QMK hue (0-255)
//   byte 2: saturation (0-255)
//   byte 3: legacy value byte (ignored; user brightness is preserved)
// Echo the packet so the host can verify that the keyboard handled it.
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < 3 || data[0] != 0xA1) {
        return;
    }

    uint8_t current_mode       = rgb_matrix_get_mode();
    uint8_t current_brightness = rgb_matrix_get_val();
    HSV     current_hsv        = rgb_matrix_get_hsv();

    // Persist the theme accent so a power cycle keeps the last colour instead
    // of falling back to QMK's default red. The host resends the same packet
    // on every theme change, so only write the EEPROM when it actually differs.
    if (current_hsv.h != data[1] || current_hsv.s != data[2]) {
        rgb_matrix_sethsv(data[1], data[2], current_brightness);
    } else {
        rgb_matrix_sethsv_noeeprom(data[1], data[2], current_brightness);
    }
    // Re-render immediately even when the selected effect is a static color.
    rgb_matrix_mode_noeeprom(current_mode);

    raw_hid_send(data, length);
}
#endif
