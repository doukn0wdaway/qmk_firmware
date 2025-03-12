/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _GAME 4
#define _GAME_RAISE 5
#define _SPCFUNC 6
#include QMK_KEYBOARD_H

// custom defines for short kc
#define MO_L MO(_LOWER)
#define MO_R MO(_RAISE)
#define MO_ADJ MO(_ADJUST)
#define KC_REDO C(KC_U)
#define FL_SPC LT(_BASE, KC_SPC)
#define LT_NUM1_GAME_RAISE LT(_GAME_RAISE, KC_NUM1)
#define FL_ENT LT(_ENTFUNC, KC_ENT)

const uint16_t copy = C(KC_C);
const uint16_t paste = C(KC_V);
const uint16_t cut = C(KC_X);
const uint16_t undo = C(KC_Z);

enum combos {
    RESET_L,
    RESET_R,
    RUS_H,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12
};

const uint16_t PROGMEM p_backspace_combo[] = {KC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM zsefb_combo[] = {KC_Z, KC_S, KC_E, KC_F, KC_B, COMBO_END};
const uint16_t PROGMEM njil_backslash_combo[] = {KC_N, KC_J, KC_I, KC_L, KC_SLSH, COMBO_END};
const uint16_t PROGMEM esc_tab_combo[] = {KC_ESC, KC_TAB, COMBO_END};
const uint16_t PROGMEM q1_combo[] = {KC_Q, KC_1, COMBO_END};
const uint16_t PROGMEM w2_combo[] = {KC_W, KC_2, COMBO_END};
const uint16_t PROGMEM e3_combo[] = {KC_E, KC_3, COMBO_END};
const uint16_t PROGMEM r4_combo[] = {KC_R, KC_4, COMBO_END};
const uint16_t PROGMEM t5_combo[] = {KC_T, KC_5, COMBO_END};
const uint16_t PROGMEM y6_combo[] = {KC_Y, KC_6, COMBO_END};
const uint16_t PROGMEM u7_combo[] = {KC_U, KC_7, COMBO_END};
const uint16_t PROGMEM i8_combo[] = {KC_I, KC_8, COMBO_END};
const uint16_t PROGMEM o9_combo[] = {KC_O, KC_9, COMBO_END};
const uint16_t PROGMEM p0_combo[] = {KC_P, KC_0, COMBO_END};
const uint16_t PROGMEM bspc_scrolllock_combo[] = {KC_BSPC, ,KC_SCRL COMBO_END};


combo_t key_combos[] = {
    [RUS_H] = COMBO(p_backspace_combo, KC_LBRC),
    [RESET_L] = COMBO(zsefb_combo, QK_BOOT),
    [RESET_R] = COMBO(njil_backslash_combo, QK_BOOT),
    [F1] = COMBO(esc_tab_combo, KC_F1),
    [F2] = COMBO(q1_combo, KC_F2),
    [F3] = COMBO(w2_combo, KC_F3),
    [F4] = COMBO(e3_combo, KC_F4),
    [F5] = COMBO(r4_combo, KC_F5),
    [F6] = COMBO(t5_combo, KC_F6),
    [F7] = COMBO(y6_combo, KC_F7),
    [F8] = COMBO(u7_combo, KC_F8),
    [F9] = COMBO(i8_combo, KC_F9),
    [F10] = COMBO(o9_combo, KC_F10),
    [F11] = COMBO(p0_combo, KC_F11),
    [F12] = COMBO(bspc_scrolllock_combo, KC_F12),
};



bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};

bool is_combo_in_enum(uint16_t combo_index) {
    return (combo_index >= RESET_L && combo_index <= F12);
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (is_combo_in_enum(combo_index) && layer_state_is(_BASE)) {
        return true;
    }

    return false;
}


void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        // Leader, a, s => GUI+S
        tap_code16(LGUI(KC_S));
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_4x6_3(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_SCRL,
  //,-----------------------------------------------------.                                  ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                  |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                  |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|                |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LGUI,   MO_L,  FL_SPC, KC_LALT, TG(_GAME),   FL_ENT,    MO_R, KC_LALT
                                      //`--------------------------'                `--------------------------'

  ),
    [_LOWER] = LAYOUT_split_4x6_3(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_SCRL,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX, XXXXXXX,                                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_Z, KC_Z,     KC_ENT,  MO_ADJ, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_4x6_3(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_SCRL,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO_ADJ,  KC_SPC,    KC_Z, KC_Z,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_4x6_3(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_Z, KC_Z,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),

     [_GAME] = LAYOUT_split_4x6_3(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_SCRL,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NUM2,   LT_NUM1_GAME_RAISE,  KC_SPC,     KC_Z,   TG(_GAME),   KC_ENT,   KC_NUM4, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),

     [_GAME_RAISE] = LAYOUT_split_4x6_3(
       KC_GRV,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_SCRL,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB,    KC_P,    KC_O,    KC_E,    KC_U,    KC_Y,                                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_SCLN,    KC_S,    KC_D,    KC_F,    KC_H,                                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SLSH,  KC_DOT, KC_COMM,    KC_M,    KC_N,                                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_NUM3, _______,  KC_SPC, KC_Z,  TG(_GAME),   KC_ENT, KC_NUM4, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),


  [_SPCFUNC] = LAYOUT_split_4x6_3(
      KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
      ALT_TAB,    KC_1,    KC_2,    KC_3, A(KC_F4),    KC_5,                                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, C(KC_BSPC),
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, C(KC_A), LSG(KC_S), XXXXXXX, XXXXXXX, XXXXXXX,                                 C(KC_LEFT), C(KC_DOWN), C(KC_UP),C(KC_RIGHT), XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    undo,     cut,    copy,   paste, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX, _______,     KC_Z, KC_Z,     KC_ENT, XXXXXXX, XXXXXXX
                                      //`--------------------------'                  `--------------------------'
  ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_TAB,  S(KC_TAB)), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [_LOWER] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_RAISE] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),          ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [_GAME] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN),          ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [_ENTFUNC] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),          ENCODER_CCW_CW(KC_MRWD, KC_MFFD) },
    [_SPCFUNC] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),          ENCODER_CCW_CW(KC_UNDO, KC_REDO) },
};
#endif

