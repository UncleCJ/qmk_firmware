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

#define MIRYOKU_ALTERNATIVES_BASE_QWERTY_split_3x6_3 \
KC_A,              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_D,              \
KC_B,              LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_QUOT),   KC_E,              \
KC_C,              LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH),KC_F,              \
U_NP,              U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_BASE_COLEMAKDH_split_3x6_3 \
KC_A,              KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,           KC_D,              \
KC_B,              LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),      KC_E,              \
KC_C,              LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH),KC_F,              \
U_NP,              U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_TAP_QWERTY_split_3x6_3 \
KC_A,              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_D,               \
KC_B,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_E,               \
KC_C,              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_F,               \
U_NP,              U_NP,              U_NP,              KC_ESC,            KC_SPC,            KC_TAB,            KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_NAV_VI_split_3x6_3 \
U_NA,              RESET,             DF(U_TAP),         DF(U_EXTRA),       DF(U_BASE),        U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             U_NA,              \
U_NA,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_CAPS,           U_NA,              \
U_NA,              U_NA,              KC_ALGR,           DF(U_NUM),         DF(U_NAV),         U_NA,              KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_INS,            U_NA,              \
U_NP,              U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MOUSE_VI_split_3x6_3 \
U_NA,              RESET,             DF(U_TAP),         DF(U_EXTRA),       DF(U_BASE),        U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             U_NA,              \
U_NA,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           U_NU,              U_NA,              \
U_NA,              U_NA,              KC_ALGR,           DF(U_SYM),         DF(U_MOUSE),       U_NA,              KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           U_NU,              U_NA,              \
U_NP,              U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_BTN2,           KC_BTN1,           KC_BTN3,           U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_MEDIA_VI_split_3x6_3 \
U_NA,              RESET,             DF(U_TAP),         DF(U_EXTRA),       DF(U_BASE),        U_NA,              RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           RGB_TOG,           U_NA,              \
U_NA,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           U_NU,              U_NA,              \
U_NA,              U_NA,              KC_ALGR,           DF(U_FUN),         DF(U_MEDIA),       U_NA,              U_NU,              U_NU,              U_NU,              U_NU,              OUT_AUTO,          U_NA,              \
U_NP,              U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_NUM_split_3x6_3 \
U_NA,              KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           U_NA,              DF(U_BASE),        DF(U_EXTRA),       DF(U_TAP),         RESET,             U_NA,              \
U_NA,              KC_SCLN,           KC_4,              KC_5,              KC_6,              KC_EQL,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              \
U_NA,              KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS,           U_NA,              DF(U_NUM),         DF(U_NAV),         KC_ALGR,           U_NA,              U_NA,              \
U_NP,              U_NP,              U_NP,              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_SYM_split_3x6_3 \
U_NA,              KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           U_NA,              DF(U_BASE),        DF(U_EXTRA),       DF(U_TAP),         RESET,             U_NA,              \
U_NA,              KC_COLN,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              \
U_NA,              KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE,           U_NA,              DF(U_SYM),         DF(U_MOUSE),       KC_ALGR,           U_NA,              U_NA,              \
U_NP,              U_NP,              U_NP,              KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_FUN_split_3x6_3 \
U_NA,              KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              DF(U_BASE),        DF(U_EXTRA),       DF(U_TAP),         RESET,             U_NA,              \
U_NA,              KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SLCK,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              \
U_NA,              KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS,           U_NA,              DF(U_FUN),         DF(U_MEDIA),       KC_ALGR,           U_NA,              U_NA,              \
U_NP,              U_NP,              U_NP,              KC_APP,            KC_SPC,            KC_TAB,            U_NA,              U_NA,              U_NA,              U_NP,              U_NP,              U_NP

#define MIRYOKU_ALTERNATIVES_BUTTON_split_3x6_3 \
U_NA,              U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             U_NA,              \
U_NA,              KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NU,              U_NU,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           U_NA,              \
U_NA,              U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             U_NA,              \
U_NP,              U_NP,              U_NP,              KC_BTN3,           KC_BTN1,           KC_BTN2,           KC_BTN2,           KC_BTN1,           KC_BTN3,           U_NP,              U_NP,              U_NP
