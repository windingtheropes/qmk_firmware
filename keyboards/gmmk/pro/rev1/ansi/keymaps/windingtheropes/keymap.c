#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "rgb_matrix_map.h"

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
//    | Esc    | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | PrScr  |        | Mute   |
//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
//    | `~     | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BackSp |        | Del    |
//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
//    | Tab    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      |        |        |
//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
//    | Caps   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | Enter           |        |        |
//    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+        +--------+
//    | Shift           | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | Shift           +--------+        |
//    +-----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+ Up     +--------+
//    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+
//    | Ctrl   | Alt    | Super  |                            Space                             | Alt    | MO(1)  | Ctrl   | Left   | Down   | Right  |
//    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [1] = LAYOUT(
        RESET,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______,   _______,   _______,   _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______,   _______,   _______,   _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______,   _______,   _______,   _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______  , _______, _______, _______, _______, _______
    ),

};

// clang-format on

bool intercept = false;

uint8_t lighting[97][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
                           {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void keyboard_post_init_user(void) {
    // Turn off RGB saving and set the RGB mode to none
    rgb_matrix_set_flags(LED_FLAG_NONE);

    // Initially turn all RGB to black
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(1) && keycode == KC_ESC && !record->event.pressed) {
        return true;
    } else {
        uint8_t response[RAW_EPSIZE];
        memset(response, 0, RAW_EPSIZE);
        if (record->event.pressed) {
            // the key is pressed
            response[0] = 1;
            response[1] = keycode;
            raw_hid_send(response, RAW_EPSIZE);
        } else {
            // the key is released
            response[0] = 2;
            response[1] = keycode;
            raw_hid_send(response, RAW_EPSIZE);
        }
    }
    return !intercept; // if intercept is true, return false
}

void set_color(int led, uint8_t r, uint8_t g, uint8_t b) {
    rgb_matrix_set_color(led, r, g, b);
    lighting[led][0] = r;
    lighting[led][1] = g;
    lighting[led][2] = b;
}

void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < ARRAYSIZE(ALL_LEDS); i++) {
        set_color(ALL_LEDS[i], r, g, b);
        // rgb_matrix_set_color(LED_SIDE_RIGHT[i], data[2], data[3], data[4]);
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // do stuff with the received data
    // [1, 0,0,0]
    // 1 is the type

    // 0,0,0 are the options
    switch (data[0]) {
        case 1:
            // simple rgb payload: changes the colour of one key
            // [1, 45, 0, 0, 0]
            set_color(data[1], data[2], data[3], data[4]);
            // rgb_matrix_set_color(data[1], data[2], data[3], data[4]);
            break;
        case 2:
            // simple rgb payload for all keys: changes the colour of all keys
            // [2, 0, 0, 0]
            set_color_all(data[1], data[2], data[3]);
            // rgb_matrix_set_color_all(data[1], data[2], data[3]);
            break;
        case 3:
            // rgb payload for side leds: changes the colour of all the x side leds
            // [3, 0, 0, 0, 0]
            // [3, side, r,g,b]
            // side:
            // 0 =left
            // 1 = right
            if (data[1] == 0) {
                for (int i = 0; i < ARRAYSIZE(LED_SIDE_LEFT); i++) {
                    set_color(LED_SIDE_LEFT[i], data[2], data[3], data[4]);
                    // rgb_matrix_set_color(LED_SIDE_LEFT[i], data[2], data[3], data[4]);
                }
            } else if (data[1] == 1) {
                for (int i = 0; i < ARRAYSIZE(LED_SIDE_RIGHT); i++) {
                    set_color(LED_SIDE_RIGHT[i], data[2], data[3], data[4]);
                    // rgb_matrix_set_color(LED_SIDE_RIGHT[i], data[2], data[3], data[4]);
                }
            }
            break;
        case 4:
            // high level key manipulation: tap a key by its qmk keycode
            // [4, 0]
            tap_code(data[1]);
            break;
        case 5:
            // low level key manipulation: register / unregister a keypress
            // [5, 0, 0]
            // [5, unreg/reg, keycode]
            if (data[1] == 1) { // register
                register_code(data[2]);
            } else if (data[1] == 0) // unregister
            {
                unregister_code(data[2]);
            }
            break;
        case 6:
            // intercept mode: 0 is off 1 is on
            // [6, 0]
            // [5, on/off]
            if (data[1] == 0) {
                intercept = false;
            } else {
                intercept = true;
            }
            break;
        case 7:
            // conditional led: turns an led on if it's off and off if it's on
            // [7, 45, 25, 0, 0]
            // [7, key, r, g, b]
            if (data[2] == 0 && data[3] == 0 && data[4] == 0) {
                return;
            }
            if (lighting[data[1]][0] == 0 && lighting[data[1]][1] == 0 && lighting[data[1]][2] == 0) {
                // led is off
                set_color(data[1], data[2], data[3], data[4]);
            } else {
                set_color(data[1], 0, 0, 0);
            }
            break;
    }
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t response[RAW_EPSIZE];
    memset(response, 0, RAW_EPSIZE);
    response[0] = 3;
    response[1] = clockwise ? 1 : 0;
    raw_hid_send(response, RAW_EPSIZE);

    // switch (get_highest_layer(layer_state)) {
    //     case 0:
    //         clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD); // Base: Volume
    //         break;
    //     case 1:
    //         clockwise ? tap_code(KC_MEDIA_NEXT_TRACK) : tap_code(KC_MEDIA_PREV_TRACK); // Fn: Scroll
    //         break;
    // }
    return !intercept;
}
#endif // ENCODER_ENABLED
