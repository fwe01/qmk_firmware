/* Copyright 2022 imchipwood && deveth0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{// Key Matrix to LED Index
                              {NO_LED, 0, 1, 2, 3},
                              {NO_LED, 7, 6, 5, 4},
                              {NO_LED, 8, 9, 10, 11},
                              {NO_LED, 15, 14, 13, 12}},
                             {// LED Index to Physical Position
                              {0, 0},
                              {75, 0},
                              {149, 0},
                              {224, 0},

                              {224, 21},
                              {149, 21},
                              {75, 21},
                              {0, 21},

                              {0, 43},
                              {75, 43},
                              {149, 43},
                              {224, 43},

                              {224, 64},
                              {149, 64},
                              {75, 64},
                              {0, 64}},
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};
#endif

void keyboard_pre_init_kb(void) {
    // Set LED IO as outputs
    gpio_set_pin_output(LED_00);
    gpio_set_pin_output(LED_01);
    gpio_set_pin_output(LED_02);
    gpio_set_pin_output(LED_03);
    gpio_set_pin_output(LED_04);
    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    // Shutdown LEDs
    gpio_write_pin_low(LED_00);
    gpio_write_pin_low(LED_01);
    gpio_write_pin_low(LED_02);
    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Layer LEDs act as binary indication of current layer
    uint8_t layer = get_highest_layer(state);
    gpio_write_pin(LED_00, layer & 0b1);
    gpio_write_pin(LED_01, (layer >> 1) & 0b1);
    gpio_write_pin(LED_02, (layer >> 2) & 0b1);
    gpio_write_pin(LED_03, !(layer >> 3) & 0b1);
    return layer_state_set_user(state);
}

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    uint8_t led_delay_ms = 80;
    for (int i = 0; i < 2; i++) {
        gpio_write_pin_high(LED_00);
        gpio_write_pin_high(LED_01);
        gpio_write_pin_high(LED_02);
        wait_ms(led_delay_ms);
        gpio_write_pin_low(LED_00);
        gpio_write_pin_low(LED_01);
        gpio_write_pin_low(LED_02);
        if (i < 1) {
            wait_ms(led_delay_ms);
        }
    }

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    // SET NUMLOCK LED
    if (!led_update_user(led_state)) return false;
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    gpio_write_pin(LED_04, led_state.num_lock);
    return true;
}
