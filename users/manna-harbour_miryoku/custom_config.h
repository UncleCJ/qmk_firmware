// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

//  One could use the Swedish extras SE_ARNG, SE_ADIA and SE_ODIA instead,
//  but as my working principle is "restoring" the default keymap as necessary, I stick to these
// #include keymap_extras/keymap_swedish.h

#if defined (KEYBOARD_crkbd)
    #define  MIRYOKU_MAPPING( \
        K00,  K01,  K02,  K03,  K04,         K05,  K06,  K07,  K08,  K09, \
        K10,  K11,  K12,  K13,  K14,         K15,  K16,  K17,  K18,  K19, \
        K20,  K21,  K22,  K23,  K24,         K25,  K26,  K27,  K28,  K29, \
        N30,  N31,  K32,  K33,  K34,         K35,  K36,  K37,  N38,  N39 \
    ) \
    LAYOUT_split_3x6_3( \
    XXX,      K00,  K01,  K02,  K03,  K04,         K05,  K06,  K07,  K08,  K09,  KC_LBRC, \
    XXX,      K10,  K11,  K12,  K13,  K14,         K15,  K16,  K17,  K18,  K19,  KC_QUOT, \
    KC_NUBS,  K20,  K21,  K22,  K23,  K24,         K25,  K26,  K27,  K28,  K29,  XXX, \
                          K32,  K33,  K34,         K35,  K36,  K37 \
    )
#endif

#define MIRYOKU_ALTERNATIVES_BASE_QWERTY_WIDE \
KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_SCLN),   \
LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH),\
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP
