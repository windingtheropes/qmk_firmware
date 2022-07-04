#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "rgb_matrix_map.h"

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static void set_rgb_indicators(void);

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
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          _______,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    _______,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [1] = LAYOUT(
        RESET,   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,           KC_SLEP,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, _______, _______,          KC_INT5,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PENT, _______, _______,          KC_INT6,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,          _______,          KC_INT7,
        _______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_P0,   _______, KC_PDOT, KC_PPLS,          _______, KC_PGUP, KC_INT8,
        _______, _______, _______,                            _______,                            _______  , _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

};

// clang-format on

void keyboard_post_init_user(void) {
    // Turn rgb mode to none
    // rgb_matrix_set_flags(LED_FLAG_NONE);

    // if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
    //     rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    // }
}

#ifdef RGB_MATRIX_ENABLE
// RGB Key indicators
void set_rgb_indicators() {}

// When RGB renders
void rgb_matrix_indicators_user() {
    // will always set the keys to black if the rgb mode is none
    // if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
    //     rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    // }

    set_rgb_indicators();
}

#endif // RGB_MATRIX_ENABLE

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // do stuff with the received data
    switch (data[0]) {
        case 1:
            // simple rgb payload: changes the colour of one key
            // [1, 45, 0, 0, 0]

            rgb_matrix_set_color(data[1], data[2], data[3], data[4]);
            break;
        case 2:
            // simple rgb payload for all keys: changes the colour of all keys
            // [2, 0, 0, 0]

            rgb_matrix_set_color_all(data[1], data[2], data[3]);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        // the key is released
        uint8_t response[RAW_EPSIZE];
        memset(response, 0, RAW_EPSIZE);
        response[0] = 0x1;
        response[1] = keycode;
        raw_hid_send(response, RAW_EPSIZE);
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
    return false;
}
#endif // ENCODER_ENABLED
