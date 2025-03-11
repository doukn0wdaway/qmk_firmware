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
#define _ENTFUNC 5  // media layer
#define _SPCFUNC 6
#include QMK_KEYBOARD_H

// custom defines for short kc
#define MO_L MO(_LOWER)
#define MO_R MO(_RAISE)
#define MO_ADJ MO(_ADJUST)
#define KC_REDO C(KC_U)
#define FL_SPC LT(_BASE, KC_SPC)
const uint16_t FL_ENT = LT(_ENTFUNC, KC_ENT);
const uint16_t copy = C(KC_C);
const uint16_t paste = C(KC_V);
const uint16_t cut = C(KC_X);
const uint16_t undo = C(KC_Z);

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;       
          register_code(KC_LALT);
        }
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      return false;
    case LT(0, KC_SPC):
      if (record->tap.count && record->event.pressed) {
        register_code(KC_SPC);
      } else if (record->event.pressed) {
        layer_on(_SPCFUNC);
      } else {
        unregister_code(KC_SPC);
        unregister_code(KC_LALT);
        layer_off(_SPCFUNC);
        is_alt_tab_active = false;
      }
      return false;
    default:
      return true;
  }
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
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
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
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
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
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
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
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_Z, KC_Z,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),

     [_GAME] = LAYOUT_split_4x6_3(
      KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
//|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_6,   KC_7,  KC_SPC,         KC_Z, _______,   KC_ENT,   KC_F3, KC_LALT
                                      //`--------------------------'                  `--------------------------'
  ),
  [_ENTFUNC] = LAYOUT_split_4x6_3(
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //,-----------------------------------------------------.                                    ,-----------------------------------------------------.
       KC_TAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX,  KC_SPC, KC_MUTE, KC_MPLY,   _______, XXXXXXX, KC_LALT
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

const uint16_t PROGMEM rusH[] = {KC_P, KC_BSPC, COMBO_END};
combo_t key_combos[] = {
    COMBO(rusH, KC_LBRC),
};


