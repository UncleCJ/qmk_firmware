// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case U_BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case U_EXTRA:
            oled_write_ln_P(PSTR("Extra"), false);
            break;
        case U_NAV:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case U_MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case U_MEDIA:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case U_NUM:
            oled_write_ln_P(PSTR("Num"), false);
            break;
        case U_SYM:
            oled_write_ln_P(PSTR("Sym"), false);
            break;
        case U_FUN:
            oled_write_ln_P(PSTR("Fun"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (
        (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)
    ) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(
        keylog_str,
        sizeof(keylog_str),
        "%dx%d, k%2d : %c",
        record->event.key.row,
        record->event.key.col,
        keycode,
        name
    );
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void oled_render_logo(void) {
    static const char PROGMEM hiq_logo[] = {
        0,  0,  0, 12, 28, 28, 60, 60, 63,127,255,252,240,224,224,224,192,192,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 14, 30, 30, 62, 60, 60,124,120,248,240,247,255,255,255,241,193,195,131,135,135,  7, 15, 14, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 96,240,248,248,240,240,225,239,255,255,255,  7,  7, 15, 15, 15, 31, 30, 30, 62, 60,124,120,120,  0,  0,  0,  0,  0,  0,192,192,224,225,239,255,255,252,224,193,193,195,192,128,128,  6, 15, 15, 14, 30, 30, 60,  0,  0,  0,  0,  0,  0,
        0,  0,  0, 15, 63,255,255,243,193,129,  7,127,255,255,227,  3,  3,  7,  7, 15, 15, 30, 30, 60,124,248,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 31, 63,255,255,252,248,240,240,224,224,224,224,192,192,192,225,227,255,255,255,124,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,255,255,255,  0,  1,  1,  1,  1,  3,  3,  3,  3,  3,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_set_cursor(0, 2);
    oled_write_raw_P(hiq_logo, sizeof(hiq_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}
#endif // OLED_ENABLE
