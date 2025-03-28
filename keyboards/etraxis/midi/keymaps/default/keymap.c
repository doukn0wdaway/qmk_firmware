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

#include QMK_KEYBOARD_H

#define _BASE 0
enum combos {
  MIDI_CD,
  MIDI_DE,
  MIDI_EF
};

const uint16_t PROGMEM CD_combo[] = {MI_C, MI_D, COMBO_END};
const uint16_t PROGMEM DE_combo[] = {MI_D, MI_E, COMBO_END};
const uint16_t PROGMEM EF_combo[] = {MI_E, MI_F, COMBO_END};

combo_t key_combos[] = {
  [MIDI_CD] = COMBO(CD_combo, MI_Cs),
  [MIDI_DE] = COMBO(DE_combo, MI_Ds),
  [MIDI_EF] = COMBO(EF_combo, MI_Fs),
};


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
//  debug_keyboard=true;
  //debug_mouse=true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        MI_C, MI_D, MI_E, MI_F
        // KC_Q, KC_W, KC_E, KC_R
    ),
};
