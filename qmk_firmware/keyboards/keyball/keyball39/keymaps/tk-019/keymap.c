#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _NUM,
    _MOVE,
    _FUNC,
    _MOUSE,
};

#define MOUSE_TIMEOUT 1000  // ms

static uint32_t last_mouse_activity = 0;
static bool mouse_layer_active = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                  KC_LCTL, MO(_NUM), MO(_MOVE),        MO(_NUM), MO(_MOVE)
    ),

    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   KC_P7,   KC_P8,   KC_P9,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_P4,   KC_P5,   KC_P6,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_DOT,  _______,
                                  _______, _______, _______,            _______, _______
    ),

    [_MOVE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_UP,   KC_END,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,            _______, _______
    ),

    [_FUNC] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,            _______, _______
    ),

    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, KC_MS_U, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_BTN2, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______,            _______, _______
    )
};

const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_qw, KC_TAB),
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.x || mouse_report.y || mouse_report.h || mouse_report.v) {
        last_mouse_activity = timer_read();
        if (!mouse_layer_active) {
            layer_on(_MOUSE);
            mouse_layer_active = true;
        }
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (mouse_layer_active && timer_elapsed(last_mouse_activity) > MOUSE_TIMEOUT) {
        layer_off(_MOUSE);
        mouse_layer_active = false;
    }
}
