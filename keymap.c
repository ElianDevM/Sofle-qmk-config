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

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s, Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv, Override)

// Light combinations
#define SET_LAYER_ID(hsv)                                       \
    {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {     \
        36 + 0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS) \
    }

enum sofle_layers { _DEFAULTS = 0, _QWERTY = 0, _COLEMAK, _DVORAK, _LOWER, _RAISE, _ADJUST, _NUMPAD, _SWITCH };

enum custom_keycodes { KC_LOWER = SAFE_RANGE, KC_RAISE, KC_ADJUST, KC_D_MUTE, KC_ALT_TAB, KC_ALT_SHIFT_TAB };

#define KC_QWERTY PDF(_QWERTY)
#define KC_COLEMAK PDF(_COLEMAK)
#define KC_DVORAK PDF(_DVORAK)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-------------------------------------------.                  ,-----------------------------------------.
     * |   Cps  |   1  |   2  |   3  |   4  |   5  |                  |   6  |   7  |   8  |   9  |   0  | Bspc |
     * |--------+------+------+------+------+------|                  |------+------+------+------+------+------|
     * |   TAB  |   Q  |   W  |   E  |   R  |   T  |                  |   Y  |   U  |   I  |   O  |   P  |  `   |
     * |--------+------+------+------+------+------|                  |------+------+------+------+------+------|
     * |CTRL-ESC|   A  |   S  |   D  |   F  |   G  |-------.  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+--------|Click  |  |Ctrl(F)|------+------+------+------+------+------|
     * |   Lsft |   Z  |   X  |   C  |   V  |   B  |-------|  |-------|   N  |   M  |   ,  |   .  |   /  | Rsft |
     * `-----------------------------------------/        /    \      \`-----------------------------------------/'
     *           |SWITCH|  WIN | LAlt |LOWER |  / Space  /       \Enter \ |NUMPAD|RAISE | RAlt | Menu | | WIN |LWIN |n
     *            |     |      |      |      |/       /          \      \|      |      |      |      |
     *            `----------------------------------'             '------''---------------------------'
     */
    [_QWERTY] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_CAPS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        //|------ +-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MS_BTN1, C(KC_F), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        //|------ +-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        MO(_SWITCH), KC_LGUI, KC_LALT, KC_LOWER, KC_SPC, GUI_T(KC_ENT), KC_RAISE, MO(_NUMPAD), KC_RALT, KC_APP
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /*
     * COLEMAK
     * ,-------------------------------------------.                     ,-----------------------------------------.
     * |   ESC  |   1  |   2  |   3  |   4  |   5  |                     |   6  |   7  |   8  |   9  |   0  | Bspc |
     * |--------+------+------+------+------+------|                     |------+------+------+------+------+------|
     * |   TAB  |   Q  |   W  |   F  |   P  |   G  |                     |   J  |   L  |   U  |   Y  |   ;  |  `   |
     * |--------+------+------+------+------+------|                     |------+------+------+------+------+------|
     * |Cps-lsft|   A  |   R  |   S  |   T  |   D  |-------.     ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
     * |------+------+------+------+------+--------|  Click  |   |Ctrl(F)|------+------+------+------+------+------|
     * |  LCTR  |   Z  |   X  |   C  |   V  |   B  |---------|   |--------|   K  |   M  |   ,  |   .  |   /  |  -   |
     * `-------------------------------------------/        /     \      \-----------------------------------------'
     *            | WIN | LAlt  | SWITCH| LOWER| / Space  /        \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |     |       |       |      |/        /          \      \|      |      |      |      |
     *            `------------------------------------'           '------''---------------------------'
     */
    [_COLEMAK] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_TRNS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_TRNS, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /*

     * DVORAK
     * ,-------------------------------------------.                     ,-----------------------------------------.
     * |   ESC  |   1  |   2  |   3  |   4  |   5  |                     |   6  |   7  |   8  |   9  |   0  | Bspc |
     * |--------+------+------+------+------+------|                     |------+------+------+------+------+------|
     * |   TAB  |   /  |   ,  |   .  |   P  |   Y  |                     |   F  |   G  |   C  |   R  |   L  |  `   |
     * |--------+------+------+------+------+------|                     |------+------+------+------+------+------|
     * |Cps-lsft|   A  |   O  |   E  |   U  |   I  |---------.    ,------|   D  |   H  |   T  |   N  |   S  |  '   |
     * |------+------+------+------+------+--------|  Click  |   |Ctrl(F)|------+------+------+------+------+------|
     * | LCTR   |   ;  |   Q  |   J  |   K  |   X  |---------|   |-------|   B  |   M  |   W  |   V  |   Z  |  -   |
     * `-------------------------------------------/       /     \       \-----------------------------------------'
     *            |  WIN | LAlt | SWITCH|LOWER| / Space  /        \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /           \      \|      |      |      |      |
     *            `----------------------------------'              '------''---------------------------'
     */
    [_DVORAK] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_SLSH, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_TRNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_TRNS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_TRNS, KC_TRNS, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_TRNS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | trans|      |      |      |      |      |                    |      |      |      |       |      |Delete|
     * |------+------+------+------+------+------|                    |------+------+------+-------+------+------|
     * | trans|      |      |  [   |  ]   |  +   |                    |      | Home |  Up  |  End  |      | Ps Cr|
     * |------+------+------+------+------+------|                    |------+------+------+-------+------+------|
     * | trans|      |      |  {   |  }   |  =   |-------.    ,-------|Ctrl <| Left | Down | Right |Ctrl >|Insert|
     * |------+------+------+------+------+------|Ctrl(T)|    |Ctrl(N)|------+------+------+-------+------+------|
     * | trans|      |      |  (   |  )   |      |-------|    |-------|      | BCSP |      |  DEL  |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |  WIN | LAlt |SWITCH|LOWER| / Space /       \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_LOWER] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_EQL, KC_NO, KC_HOME, KC_UP, KC_END, KC_NO, KC_PSCR,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_PLUS, LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_RGHT), KC_INS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, C(KC_T), C(KC_N), KC_NO, KC_BSPC, KC_NO, KC_DEL, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* RAISE
     * ,----------------------------------------.                     ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |                    |  \ | |   &  |  *   |  :   |  '   |  "   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------.    ,-------| - _  |  $   |  %   |  ^   |  *   |  !   |
     * |------+------+------+------+------+------|Ctrl(G)|    |Ctrl(S)|------+------+------+------+------+------|
     * | trans|      |Ctrl+x|Ctrl+c|Ctrl+v|      |-------.    ,-------|  ^   |   ~  |  %   |  #   |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | WIN  | LAlt |SWITCH| LOWER| / Space /       \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_RAISE] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, LSFT(KC_9), LSFT(KC_8), KC_COLN, KC_QUOT, KC_DQUO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), KC_ASTR, KC_EXLM,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, C(KC_G), C(KC_S), KC_EQL, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      | bri ^|      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Reset|      |      | bri v|      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |UG_TOGG|hue^ |sat ^ | bri ^|      |      |-------.   ,--------|      |QWERTY|COLEMAK|DVORAK|      |      |
     * |------+------+------+------+------+------|        |   |       |------+------+------+------+------+------|
     * |Nxt mod| hue v|sat v| bri v|      |      |--------|   |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | WIN  | LAlt |SWITCH| LOWER| / Space /       \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_ADJUST] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_NO, KC_NO, KC_NO, KC_BRIU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        QK_BOOT, KC_NO, KC_NO, KC_BRID, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, KC_NO, KC_NO, KC_NO, KC_QWERTY, KC_COLEMAK, KC_DVORAK, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        UG_NEXT, UG_HUED, UG_SATD, UG_VALD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* NUMPAD
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |   +  |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |                    |   _  |   7  |   8  |   9  |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------.    ,-------|   *  |   4  |   5  |   6  |      |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * | trans|      | Prev | Play | Next |      |-------|    |-------|   0  |   1  |   2  |   3  |      |      |
     * `-----------------------------------------/       /    \      \-----------------------------------------'
     *            | WIN  | LAlt |SWITCH| LOWER| / Space /       \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_NUMPAD] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_PPLS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MINS, KC_P7, KC_P8, KC_P9, KC_NO, KC_PMNS,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PAST, KC_P4, KC_P5, KC_P6, KC_NO, KC_PAST,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_P0, KC_P1, KC_P2, KC_P3, KC_NO, KC_PSLS,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* SWITCH
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | qwer | cole |dvorak| low  | raise| adj  |                    |numpad|      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |NUMPAD|RAISE|      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|Ctrl(0)|    |  Mute |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | WIN  | LAlt |SWITCH| LOWER| / Space /       \Enter \ |NUMPAD|RAISE | RAlt | Menu |
     *            |      |      |      |      |/       /         \      \|      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    // layer switcher
    [_SWITCH] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_NO, TO(0), TO(1), TO(2), TO(3), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        KC_NO, TO(4), TO(5), TO(6), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(KC_0), KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
};

#ifdef RGBLIGHT_ENABLE
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[]  = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_WHITE));
const rgblight_segment_t PROGMEM layer_colemak_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));
const rgblight_segment_t PROGMEM layer_dvorak_lights[]  = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_TEAL));

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_GREEN));

// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE));

// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PINK));

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));

// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_YELLOW));

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_qwerty_lights,
                                                                               layer_num_lights, // overrides layer 1
                                                                               layer_symbol_lights, layer_command_lights, layer_numpad_lights,
                                                                               layer_switcher_lights, // Overrides other layers
                                                                               layer_colemak_lights, layer_dvorak_lights);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _COLEMAK));
    rgblight_set_layer_state(8, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _DVORAK));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    // rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT); // haven't found a way to set this in a more useful way
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT); // haven't found a way to set this in a more useful way
}
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM berserk_logo[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0x40, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xC0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0xF0, 0xD0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x24, 0x7F, 0xFF, 0xF7, 0xF1, 0xF1, 0x01, 0x01, 0x01, 0x81, 0xF1, 0x71, 0x71, 0x31, 0x01, 0x01, 0x81, 0xC1, 0xE1, 0x31, 0x31, 0x01, 0x01, 0x00, 0x00, 0x20, 0x21, 0x21, 0x21, 0x31, 0x31, 0x3D, 0x39, 0x21, 0xE1, 0xE1, 0x21, 0x01, 0x01, 0x01, 0x21, 0x11, 0x01, 0x01, 0x81, 0xC1, 0x31, 0x0F, 0x01, 0x01, 0x21, 0x31, 0x21, 0x21, 0x21, 0x31, 0x21, 0x21, 0x71, 0x3F, 0x21, 0x01, 0x00, 0x00, 0x20, 0x20, 0x21, 0x21, 0x21, 0x21, 0x31, 0x3F, 0x31, 0xA1, 0xF3, 0x73, 0x01, 0x01, 0x01, 0x01, 0x21, 0x01, 0x01, 0x01, 0x81, 0xC1, 0x33, 0x03, 0x01, 0x01, 0x01, 0x0F, 0x87, 0xC3, 0xC3, 0xE1, 0xF1, 0xF1, 0xF9, 0xF9, 0xF9, 0xFD, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x17, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0xFF, 0xFF, 0x9F, 0x81, 0x80, 0x80, 0x80, 0x81, 0x80, 0x88, 0x88, 0x80, 0x80, 0x81, 0x87, 0xBF, 0xFE, 0xFE, 0xC0, 0x80, 0x80, 0x80, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x9E, 0x87, 0x83, 0xC1, 0xE0, 0xF8, 0xFC, 0xF4, 0xC0, 0x80, 0x02, 0x07, 0x0F, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0x0E, 0x80, 0xC0, 0xE0, 0xF0, 0xFE, 0xFE, 0xE4, 0x80, 0x80, 0x80, 0x8C, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0xCE, 0x9E, 0x07, 0x83, 0xC0, 0xE0, 0xF8, 0xFC, 0xE4, 0xC0, 0x80, 0x02, 0x0F, 0x1F, 0x3F, 0xE7, 0x80, 0x80, 0x80, 0x8C, 0x88, 0xF0, 0xE0, 0xE1, 0xC3, 0x83, 0x07, 0x8F, 0xDF, 0xFF, 0xFF, 0xFC, 0x7C, 0x6C, 0x40, 0xE0, 0xC0, 0xC0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x03, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x17, 0x13, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x03, 0x07, 0x03, 0x03, 0x07, 0x0F, 0x1C, 0x38, 0x78, 0x3C, 0x1E, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x07, 0x03, 0x01, 0x01, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x78, 0x3C, 0x1F, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0B, 0x0B, 0x0F, 0x1F, 0x1F, 0x1F, 0x1B, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
    oled_write_raw_P(berserk_logo, sizeof(berserk_logo));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("Rorschard"), false);

    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        case _DVORAK:
            oled_write_ln_P(PSTR("Dvrk"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QWERTY:
        case _DVORAK:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        case _SWITCH:
            oled_write_P(PSTR("Swit\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
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
            }
            return false;
            break;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
            return false;
            break;
        case KC_ALT_TAB:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LALT);
            }
            return false;
            break;
        case KC_ALT_SHIFT_TAB:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_TAB);
            } else {
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
            }
            return false;
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _COLEMAK:
            case _QWERTY:
            case _DVORAK:
                if (clockwise) {
                    tap_code16(KC_LEFT);
                } else {
                    tap_code16(KC_RIGHT);
                }
                return false;
            case _RAISE:
                if (clockwise) {
                    tap_code16(LCTL(KC_Z));
                } else {
                    tap_code16(LCTL(KC_Y));
                }
                return false;
            case _LOWER:
                if (clockwise) {
                    tap_code16(LCTL(KC_PGDN));
                } else {
                    tap_code16(LCTL(KC_PGUP));
                }
                return false;
            case _NUMPAD:
                if (clockwise) {
                    register_code(KC_RALT);
                    register_code(KC_LSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_RALT);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_RALT);
                    tap_code(KC_TAB);
                    unregister_code(KC_RALT);
                }
                return false;
            // case _ADJUST:
            //     if (clockwise) {
            //         tap_code16(UG_SATU);
            //     } else {
            //         tap_code16(UG_SATD);
            //     }
            //     return false;
            case _SWITCH:
                if (clockwise) {
                    tap_code16(C(KC_MINUS)); // Acción para avanzar página en la capa NUMPAD
                } else {
                    tap_code16(C(KC_EQUAL)); // Acción para retroceder página en la capa NUMPAD
                }
                return false;
            default:
                if (clockwise) {
                    tap_code(KC_LEFT);
                } else {
                    tap_code(KC_RIGHT);
                }
                return false;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _COLEMAK:
            case _QWERTY:
            case _DVORAK:
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
                return false;
            // case _RAISE:
            //     if (clockwise) {
            //         tap_code16();
            //     } else {
            //         tap_code16();
            //     return false;
            case _LOWER:
                if (clockwise) {
                    tap_code16(KC_PGUP);
                } else {
                    tap_code16(KC_PGDN);
                }
                return false;
            case _NUMPAD:
                if (clockwise) {
                    tap_code16(C(G(KC_LEFT))); // Acción para avanzar página en la capa NUMPAD
                } else {
                    tap_code16(C(G(KC_RGHT))); // Acción para retroceder página en la capa NUMPAD
                }
                return false;
            // case _ADJUST:
            //     if (clockwise) {
            //         tap_code16(UG_HUEU); // Acción para avanzar página en la capa NUMPAD
            //     } else {
            //         tap_code16(UG_HUED); // Acción para retroceder página en la capa NUMPAD
            //     }
            //     return false;
            case _SWITCH:
                if (clockwise) {
                    tap_code16(KC_VOLD); // Acción para avanzar página en la capa NUMPAD
                } else {
                    tap_code16(KC_VOLU); // Acción para retroceder página en la capa NUMPAD
                }
                return false;
            default:
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
                return false;
        }
    }
    return false;
}

#endif
