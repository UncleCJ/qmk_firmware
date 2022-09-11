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
int current_wpm = 0;
led_t led_usb_state;

static void render_logo(void) {
    static const char PROGMEM hiq_logo[] = {
        0,  0,  0, 12, 28, 28, 60, 60, 63,127,255,252,240,224,224,224,192,192,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 14, 30, 30, 62, 60, 60,124,120,248,240,247,255,255,255,241,193,195,131,135,135,  7, 15, 14, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 96,240,248,248,240,240,225,239,255,255,255,  7,  7, 15, 15, 15, 31, 30, 30, 62, 60,124,120,120,  0,  0,  0,  0,  0,  0,192,192,224,225,239,255,255,252,224,193,193,195,192,128,128,  6, 15, 15, 14, 30, 30, 60,  0,  0,  0,  0,  0,  0,
        0,  0,  0, 15, 63,255,255,243,193,129,  7,127,255,255,227,  3,  3,  7,  7, 15, 15, 30, 30, 60,124,248,240,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7, 15, 31, 31, 63,255,255,252,248,240,240,224,224,224,224,192,192,192,225,227,255,255,255,124,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,255,255,255,  0,  1,  1,  1,  1,  3,  3,  3,  3,  3,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_set_cursor(0, 2);
    oled_write_raw_P(hiq_logo, sizeof(hiq_logo));
}

static void render_wpm(void) {
    char wpm_str[4];
    current_wpm = get_current_wpm();
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + current_wpm % 10;
    wpm_str[1] = '0' + (current_wpm /= 10) % 10;
    wpm_str[0] = '0' + current_wpm / 10;

    oled_set_cursor(0, 12);
    oled_write(wpm_str, false);
    oled_set_cursor(0, 13);
    oled_write(" wpm", false);
}

// KEYBOARD PET START
#define MIN_WALK_SPEED 5
#define MIN_RUN_SPEED 30

#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE 96

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

uint8_t current_frame = 0;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

static void render_luna(int LUNA_X, int LUNA_Y) {
    static const char PROGMEM sit[2][ANIM_SIZE] = {
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9,
            0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10,
            0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82,
            0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
            0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9,
            0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08,
            0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82,
            0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
            0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };
    static const char PROGMEM walk[2][ANIM_SIZE] = {
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20,
            0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
            0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10,
            0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
            0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
            0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
            0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
            0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20,
            0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8,
            0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10,
            0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
            0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
            0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };
    static const char PROGMEM run[2][ANIM_SIZE] = {
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08,
            0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90,
            0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4,
            0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04,
            0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
            0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32,
            0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30,
            0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11,
            0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
            0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };
    static const char PROGMEM bark[2][ANIM_SIZE] = {
        {
            0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08,
            0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28,
            0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
            0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
            0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04,
            0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48,
            0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05,
            0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };
    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
            0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80,
            0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04,
            0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
            0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01,
            0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c,
            0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
            0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04,
            0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00
        },
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
            0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0,
            0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04,
            0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
            0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00,
            0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20,
            0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
            0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06,
            0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    void animate_luna(void) {
        if (isJumping || !showedJump) {
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            showedJump = true;
        } else {
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y);
        }
        current_frame = (current_frame + 1) % 2;
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(
                bark[abs(1 - current_frame)],
                ANIM_SIZE
            );
        } else if (isSneaking) {
            oled_write_raw_P(
                sneak[abs(1 - current_frame)],
                ANIM_SIZE
            );
        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(
                sit[abs(1 - current_frame)],
                ANIM_SIZE
            );
        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(
                walk[abs(1 - current_frame)],
                ANIM_SIZE
            );
        } else {
            oled_write_raw_P(
                run[abs(1 - current_frame)],
                ANIM_SIZE
            );
        }
    }

    if (
        timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION &&
        timer_elapsed32(anim_sleep) < OLED_TIMEOUT
    ) {
        anim_timer = timer_read32();
        animate_luna();
    }

    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    }
}
// KEYBOARD PET END

static void print_status_narrow(void) {
    oled_set_cursor(0, 3);
    oled_write("LAYER", false);
    oled_set_cursor(0, 4);
    switch (get_highest_layer(default_layer_state)) {
        case U_BASE:
            oled_write("Base ", false);
            break;
        case U_EXTRA:
            oled_write("Extra", false);
            break;
        case U_NAV:
            oled_write("Nav  ", false);
            break;
        case U_MOUSE:
            oled_write("Mouse", false);
            break;
        case U_MEDIA:
            oled_write("Media", false);
            break;
        case U_NUM:
            oled_write("Num  ", false);
            break;
        case U_SYM:
            oled_write("Sym  ", false);
            break;
        case U_FUN:
            oled_write("Fun  ", false);
            break;
        default:
            oled_write("UNDEF", false);
    }
    oled_set_cursor(0, 5);
    oled_write(" -", false);
    oled_set_cursor(0, 6);
    switch (get_highest_layer(layer_state)) {
        case U_BASE:
            oled_write("Base ", false);
            break;
        case U_EXTRA:
            oled_write("Extra", false);
            break;
        case U_NAV:
            oled_write("Nav  ", false);
            break;
        case U_MOUSE:
            oled_write("Mouse", false);
            break;
        case U_MEDIA:
            oled_write("Media", false);
            break;
        case U_NUM:
            oled_write("Num  ", false);
            break;
        case U_SYM:
            oled_write("Sym  ", false);
            break;
        case U_FUN:
            oled_write("Fun  ", false);
            break;
        default:
            oled_write("Undef", false);
    }

    oled_set_cursor(0, 8);
    if (led_usb_state.caps_lock) {
        oled_write("CPSLK", false);
    } else {
        oled_write("     ", false);
    }

    // KEYBOARD PET RENDER START
    render_luna(0, 11);
    // KEYBOARD PET RENDER END
}

static void print_logo_narrow(void) {
    render_logo();
    render_wpm();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    // KEYBOARD PET VARIABLES START
    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    // KEYBOARD PET VARIABLES END

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // KEYBOARD PET STATUS START
        case LCTL_T(KC_D):
        case LCTL_T(KC_K):
        case LCTL_T(KC_S):
        case LCTL_T(KC_E):
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case LT(U_NAV,KC_SPC):
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
        // KEYBOARD PET STATUS END
    }
    return true;
}
#endif // OLED_ENABLE
