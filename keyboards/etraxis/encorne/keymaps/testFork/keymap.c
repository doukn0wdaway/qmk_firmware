#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _GAME 3
#define _GAME_RAISE 4
#define _MEDIA 5
#include QMK_KEYBOARD_H
#include "print.h"

// custom defines for short kc
#define MO_L MO(_LOWER)
#define MO_R MO(_RAISE)
#define KC_REDO C(KC_U)
#define FL_SPC LT(_BASE, KC_SPC)
#define ESC_MEDIA LT(_MEDIA, KC_ESC)
#define LT_P1_GAME_RAISE LT(_GAME_RAISE, KC_P1)

// void keyboard_post_init_user(void) {
//  // Customise these values to desired behaviour
//  debug_enable=true;
//  // debug_matrix=true;
//  // debug_keyboard=true;
//  // debug_mouse=true;
// }
//
const uint16_t copy = C(KC_C);
const uint16_t paste = C(KC_V);
const uint16_t cut = C(KC_X);
const uint16_t undo = C(KC_Z);

enum combos {
 RESET_L,
 RESET_R,
 RUS_H,
 FN_F1,
 FN_F2,
 FN_F3,
 FN_F4,
 FN_F5,
 FN_F6,
 FN_F7,
 FN_F8,
 FN_F9,
 FN_F10,
 FN_F11,
 FN_F12
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
const uint16_t PROGMEM bspc_scrolllock_combo[] = {KC_BSPC, KC_SCRL, COMBO_END};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
 uprintf("Current layer: 0x%02X\n", layer_state);

 if (layer_state_is(_GAME) || layer_state_is(_GAME_RAISE)) {
 uprintf("Combo blocked on _GAME or _GAME_RAISE layer\n");
 return false;
 }

 return true;
}

enum custom_keycodes {
  GITHUB = SAFE_RANGE,
  EMAIL1,
  EMAIL2,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GITHUB:
            if (record->event.pressed) {
                SEND_STRING("https://github.com/doukn0wdaway");
            }
            return false;

        case EMAIL1:
            if (record->event.pressed) {
                SEND_STRING("anisimov.sasha370@gmail.com");
            }
            return false;

        case EMAIL2:
            if (record->event.pressed) {
                SEND_STRING("anisimov.sasha20@gmail.com");
            }
            return false;
    }

    return true;
}

combo_t key_combos[] = {
 [RUS_H] = COMBO(p_backspace_combo, KC_LBRC),
 [RESET_L] = COMBO(zsefb_combo, QK_BOOT),
 [RESET_R] = COMBO(njil_backslash_combo, QK_BOOT),
 [FN_F1] = COMBO(esc_tab_combo, KC_F1),
 [FN_F2] = COMBO(q1_combo, KC_F2),
 [FN_F3] = COMBO(w2_combo, KC_F3),
 [FN_F4] = COMBO(e3_combo, KC_F4),
 [FN_F5] = COMBO(r4_combo, KC_F5),
 [FN_F6] = COMBO(t5_combo, KC_F6),
 [FN_F7] = COMBO(y6_combo, KC_F7),
 [FN_F8] = COMBO(u7_combo, KC_F8),
 [FN_F9] = COMBO(i8_combo, KC_F9),
 [FN_F10] = COMBO(o9_combo, KC_F10),
 [FN_F11] = COMBO(p0_combo, KC_F11),
 [FN_F12] = COMBO(bspc_scrolllock_combo, KC_F12),
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_4x6_3(
   //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      ESC_MEDIA,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                       KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_F12,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                          KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                          KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                          KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ESC,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┘
                                    KC_LGUI,  MO_L,     FL_SPC,   TG(_GAME),KC_RALT,   KC_ENT,   MO_R,     KC_LALT
   //                              └─────────┴─────────┴─────────┴─────────┴──────────┴─────────┴─────────┴─────────┘
    ),

    [_LOWER] = LAYOUT_split_4x6_3(
   //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                        KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_TAB,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LCTL,  XXXXXXX,  XXXXXXX,  KC_DEL,   XXXXXXX,  XXXXXXX,                      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, XXXXXXX,  XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┘
                                    KC_LGUI,  _______,  KC_SPC,   XXXXXXX,  XXXXXXX,  KC_ENT,   XXXXXXX,  KC_LALT
   //                              └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
    ),

    [_RAISE] = LAYOUT_split_4x6_3(
   //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                          KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_F12,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_TAB,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                       KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_GRV,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TILD,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┘
                                    KC_LGUI,  XXXXXXX,  KC_SPC,   KC_Z,     KC_Z,      KC_ENT,   _______,  KC_LALT
   //                              └─────────┴─────────┴─────────┴─────────┴──────────┴─────────┴─────────┴─────────┘
    ),

    [_GAME] = LAYOUT_split_4x6_3(
        ESC_MEDIA, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_SCRL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
        KC_P2, LT_P1_GAME_RAISE, KC_SPC,  TG(_GAME),KC_Z, KC_ENT, KC_P4, KC_LALT
    ),

    [_GAME_RAISE] = LAYOUT_split_4x6_3(
        KC_GRV, KC_6, KC_7, KC_8, KC_9, KC_0, KC_6, KC_7, KC_8, KC_9, KC_0, KC_SCRL,
        KC_TAB, KC_P, KC_O, KC_E, KC_U, KC_Y, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_SCLN, KC_S, KC_D, KC_F, KC_H, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
        KC_P3, _______, KC_SPC,  TG(_GAME),KC_Z, KC_ENT, KC_P4, KC_LALT
    ),


    [_MEDIA] = LAYOUT_split_4x6_3(
   //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      _______,  KC_MPRV,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_MNXT,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_MUTE,  KC_VOLU,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX,  GITHUB,   EMAIL1,   EMAIL2,   XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┘
                                    XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
   //                              └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
    ),
   //  [_MEDIA] = LAYOUT_split_4x6_3(
   // //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
   //    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   // //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   //    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   // //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   //    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   // //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   //    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   // //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┬─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┘
   //                                  XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   //                               └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
// ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
     [_BASE] = { ENCODER_CCW_CW(KC_TAB, S(KC_TAB)), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
     [_LOWER] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
     [_RAISE] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
     [_GAME] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
     [_MEDIA] = { ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

