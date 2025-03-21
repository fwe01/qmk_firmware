/*
Copyright 2022 imchipwood && deveth0

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Num Pad
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |    -    |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    *    |
    |-------------|---------|---------|---------|---------|
    |    Mute     |  TT(1)  |    0    |         |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,      KC_P8,    KC_P9,          KC_PMNS,
                    KC_P4,      KC_P5,    KC_P6,          KC_PSLS,
                    KC_P1,      KC_P2,    KC_P3,          KC_PAST,
        KC_MUTE,    TT(1),      KC_P0,    KC_PPLS,        KC_ENTER
    ),
    /*
            SUB LAYER  - RGB controls, Modes on encoder
    /-----------------------------------------------------`
    |             | On/Off  | Bright- | Bright+ |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         | Hue-    | Hue+    |         |
    |             |---------|---------|---------|---------|
    |             |         | Sat-    | Sat+    |         |
    |-------------|---------|---------|---------|---------|
    |             |  TT(1)  | Effect- | Effect+ |         |
    \-----------------------------------------------------'
    */
    // RGB LAYER
    // [1] = LAYOUT(
    //                 RM_TOGG,    RM_VALD,     RM_VALU,      QK_BOOT,
    //                 KC_NO,      RM_HUED,     RM_HUEU,      KC_NO,
    //                 KC_NO,      RM_SATD,     RM_SATU,      KC_NO,
    //     KC_NO,      TT(2),    RM_SPDD,     RM_SPDU,      KC_NO
    // ),

    [1] = LAYOUT(
                    KC_HOME,     KC_UP,     KC_PGUP,      KC_NO,
                    KC_LEFT,     _____,     KC_RGHT,      KC_NO,
                    KC_END,      KC_DOWN,   KC_PGDN,      KC_NO,
        KC_MUTE,      TT(2),     _____,     KC_COPY,      KC_PSTE
    ),

    [2] = LAYOUT(
                    KC_HOME,     KC_UP,     KC_PGUP,      KC_NO,
                    KC_LEFT,     _____,     KC_RGHT,      KC_NO,
                    KC_END,      KC_DOWN,   KC_PGDN,      KC_NO,
        KC_MUTE,      TT(0),     _____,     KC_COPY,      KC_PSTE
    ),
};
// clang-format on

// ENCODER ON THE KEYBOAR IS FLIPPED!!!
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case 1:
            // rgb control layer, effects
            if (!clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
            break;
        default:
            // main layer, volume
            if (!clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return false;
}
