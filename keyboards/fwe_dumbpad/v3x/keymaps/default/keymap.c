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

#include <sys/types.h>
#include QMK_KEYBOARD_H

// DEFINE LAYERS
#define NUMPAD_LAYER 0
#define NUMLOCK_LAYER 1
#define BIOS_LAYER 2
#define VIM_LAYER 3
#define TBD_LAYER_4 4
#define TBD_LAYER_5 5
#define TBD_LAYER_6 6
#define LAYER_CHANGE_JUNCTION 15

#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END 3 // ENSURE is the highest numer available on keyboard

enum custom_keycodes { VIM_START_RECORD_A = SAFE_RANGE, VIM_PLAY_RECORD_A, VIM_END_RECORD, VIM_START_RECORD_B, VIM_PLAY_RECORD_B, VIM_REGISTER_C, VIM_REGISTER_D, VIM_REGISTER_E, VIM_REGISTER_F, KC_CYCLE_LAYERS };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VIM_END_RECORD:
            if (record->event.pressed) {
                SEND_STRING("\eq");
            } else {
            }
            break;
        case VIM_START_RECORD_A:
            if (record->event.pressed) {
                SEND_STRING("\eqa");
            } else {
            }
            break;
        case VIM_PLAY_RECORD_A:
            if (record->event.pressed) {
                SEND_STRING("\e@a");
            } else {
            }
            break;

        case VIM_START_RECORD_B:
            if (record->event.pressed) {
                SEND_STRING("\eqb");
            } else {
            }
            break;
        case VIM_PLAY_RECORD_B:
            if (record->event.pressed) {
                SEND_STRING("\e@b");
            } else {
            }
            break;

        case VIM_REGISTER_C:
            if (record->event.pressed) {
                SEND_STRING("\"c");
            } else {
            }
            break;
        case VIM_REGISTER_D:
            if (record->event.pressed) {
                SEND_STRING("\"d");
            } else {
            }
            break;
        case VIM_REGISTER_E:
            if (record->event.pressed) {
                SEND_STRING("\"e");
            } else {
            }
            break;
        case VIM_REGISTER_F:
            if (record->event.pressed) {
                SEND_STRING("\"f");
            } else {
            }
            break;
        case KC_CYCLE_LAYERS:
            // Our logic will happen on presses, nothing is done on releases
            if (!record->event.pressed) {
                // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
                return false;
            }

            uint8_t current_layer = get_highest_layer(layer_state);

            // Check if we are within the range, if not quit
            if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;
            }

            uint8_t next_layer = current_layer + 1;
            if (next_layer > LAYER_CYCLE_END) {
                next_layer = LAYER_CYCLE_START;
            }
            layer_move(next_layer);
            return false;
    }

    return true;
};

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
    [NUMPAD_LAYER] = LAYOUT(
                    KC_P7,            KC_P8,    KC_P9,          KC_PMNS,
                    KC_P4,            KC_P5,    KC_P6,          KC_PSLS,
                    KC_P1,            KC_P2,    KC_P3,          KC_PAST,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_P0,    KC_PPLS,        KC_ENTER
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

    [NUMLOCK_LAYER] = LAYOUT(
                    KC_HOME,                    KC_UP,     KC_PGUP,   KC_NO,
                    KC_LEFT,                    KC_NO,     KC_RGHT,   KC_NO,
                    KC_END,                     KC_DOWN,   KC_PGDN,   KC_NO,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_NO,     KC_NUM,    KC_ENT
    ),

    [BIOS_LAYER] = LAYOUT(
                    KC_F7,            KC_UP,     KC_F10,   KC_F11,
                    KC_LEFT,          KC_NO,     KC_RGHT,  KC_DEL,
                    KC_NO,            KC_DOWN,   KC_NO,    KC_NO,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_NO,     KC_NO,    KC_ENT
    ),

    [VIM_LAYER] = LAYOUT(
                    VIM_START_RECORD_A,   VIM_START_RECORD_B,   VIM_REGISTER_C,      KC_NO,
                    VIM_PLAY_RECORD_A,    VIM_PLAY_RECORD_B,    VIM_REGISTER_D,      KC_NO,
                    VIM_END_RECORD,       VIM_REGISTER_F,       VIM_REGISTER_E,      KC_NO,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),      KC_NO,                KC_NO,               KC_NO
    ),

    [TBD_LAYER_4] = LAYOUT(
                    KC_P7,            KC_P8,    KC_P9,          KC_PMNS,
                    KC_P4,            KC_P5,    KC_P6,          KC_PSLS,
                    KC_P1,            KC_P2,    KC_P3,          KC_PAST,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_P0,    KC_PPLS,        KC_ENTER
    ),

    [TBD_LAYER_5] = LAYOUT(
                    KC_P7,            KC_P8,    KC_P9,          KC_PMNS,
                    KC_P4,            KC_P5,    KC_P6,          KC_PSLS,
                    KC_P1,            KC_P2,    KC_P3,          KC_PAST,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_P0,    KC_PPLS,        KC_ENTER
    ),

    [TBD_LAYER_6] = LAYOUT(
                    KC_P7,            KC_P8,    KC_P9,          KC_PMNS,
                    KC_P4,            KC_P5,    KC_P6,          KC_PSLS,
                    KC_P1,            KC_P2,    KC_P3,          KC_PAST,
        KC_MUTE,    MO(LAYER_CHANGE_JUNCTION),  KC_P0,    KC_PPLS,        KC_ENTER
    ),

    [LAYER_CHANGE_JUNCTION] = LAYOUT(
                KC_NO,  KC_NO,    KC_NO,    KC_NO,
                TO(4),  TO(5),    TO(6),    KC_NO,
                TO(1),  TO(2),    TO(3),    KC_NO,
        KC_NO,  KC_NO,  TO(0),    KC_NO,    KC_NO
    ),
};

// ENCODER ON THE KEYBOAR IS FLIPPED!!!
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        // case 1:
        //     // rgb control layer, effects
        //     if (!clockwise) {
        //         rgblight_step();
        //     } else {
        //         rgblight_step_reverse();
        //     }
        //     break;
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
