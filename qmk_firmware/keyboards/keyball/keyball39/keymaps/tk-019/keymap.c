#include QMK_KEYBOARD_H

enum layer_names { _BASE, _NUM, _MOVE, _FUNC, _MOUSE };
#define MOUSE_TIMEOUT 1000

static uint32_t last_mouse_activity = 0;
static bool     mouse_layer_active  = false;

/* ───────── BASE ───────── */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_right_ball(
/* ┌─── 左手 18 ───┐                        ┌──── 右手 18 ────┐ */
  KC_Q,  KC_W, KC_E, KC_R, KC_T, KC_Y,            KC_U,   KC_I,   KC_O,    KC_P,    KC_L,    KC_ENT,
  KC_A,  KC_S, KC_D, KC_F, KC_G, KC_H,            KC_J,   KC_K,   KC_LBRC, KC_RBRC, KC_QUOT, KC_BSPC,
  KC_Z,  KC_X, KC_C, KC_V, KC_B, KC_N,            KC_M,   KC_COMM,KC_DOT,  MT(MOD_RSFT, KC_SLSH), KC_MINS,
/* └─左親指3─┘                               └──右親指2──┘   */
                   KC_ESC, KC_LALT, KC_LGUI,      MO(_NUM), MO(_MOVE)
),

/* ───────── NUM ───────── */
[_NUM] = LAYOUT_right_ball(
  _______, _______, _______, _______, _______, _______,    KC_P7,  KC_P8,  KC_P9,  _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_P4,  KC_P5,  KC_P6,  _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_P1,  KC_P2,  KC_P3,  KC_P0,  KC_DOT,  _______,
                   _______, _______, _______,     _______, _______
),

/* ───────── MOVE / FUNC / MOUSE ───────── (省略は空キー) */
[_MOVE] = LAYOUT_right_ball(
  _______, _______, _______, _______, _______, _______,    KC_HOME, KC_UP,   KC_END,  _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
                   _______, _______, _______,     _______, _______
),
[_FUNC] = LAYOUT_right_ball(
  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
                   _______, _______, _______,     _______, _______
),
[_MOUSE] = LAYOUT_right_ball(
  _______, _______, _______, _______, _______, _______,    _______, KC_MS_U, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_BTN2, _______,
  _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
                   _______, _______, _______,     _______, _______
)
};

/* ───────── Combos ───────── */
/* ──────────  記号コンボ  ────────── */
/* 座標は “a + H” のように 2 キー同時押し                  */
/* 出力キーは US/JIS どちらでも動く一般キーコードで記述   */

const uint16_t PROGMEM combo_ah[] = {KC_A, KC_H, COMBO_END};      // @
const uint16_t PROGMEM combo_sh[] = {KC_S, KC_H, COMBO_END};      // #
const uint16_t PROGMEM combo_dh[] = {KC_D, KC_H, COMBO_END};      // $
const uint16_t PROGMEM combo_pg[] = {KC_P, KC_G, COMBO_END};      // %
const uint16_t PROGMEM combo_ch[] = {KC_C, KC_H, COMBO_END};      // ^
const uint16_t PROGMEM combo_eh[] = {KC_E, KC_H, COMBO_END};      // !
const uint16_t PROGMEM combo_kG[] = {KC_K, KC_G, COMBO_END};      // *
const uint16_t PROGMEM combo_jG[] = {KC_J, KC_G, COMBO_END};      // +
const uint16_t PROGMEM combo_lG[] = {KC_L, KC_G, COMBO_END};      // -
const uint16_t PROGMEM combo_uG[] = {KC_U, KC_G, COMBO_END};      // _
const uint16_t PROGMEM combo_qH2[] = {KC_Q, KC_H, COMBO_END};     // '
const uint16_t PROGMEM combo_wH[] = {KC_W, KC_H, COMBO_END};      // "
const uint16_t PROGMEM combo_bH[] = {KC_B, KC_H, COMBO_END};      // \
const uint16_t PROGMEM combo_iG[] = {KC_I, KC_G, COMBO_END};      // [
const uint16_t PROGMEM combo_oG[] = {KC_O, KC_G, COMBO_END};      // ]
const uint16_t PROGMEM combo_tH[] = {KC_T, KC_H, COMBO_END};      // :
const uint16_t PROGMEM combo_yG[] = {KC_Y, KC_G, COMBO_END};      // ;
/* 出力が /, {, }, =, ? など物理キー依存のものはコンボより物理キーで入力する方が確実 */

combo_t key_combos[] = {
    /* 既存 */
    COMBO(combo_qw, KC_TAB),
    COMBO(combo_qh, LSFT(KC_SLASH)),
    /* 追加 */
    COMBO(combo_ah,  LSFT(KC_2)),          // @
    COMBO(combo_sh,  LSFT(KC_3)),          // #
    COMBO(combo_dh,  LSFT(KC_4)),          // $
    COMBO(combo_pg,  LSFT(KC_5)),          // %
    COMBO(combo_ch,  LSFT(KC_6)),          // ^
    COMBO(combo_eh,  LSFT(KC_1)),          // !
    COMBO(combo_kG,  LSFT(KC_8)),          // *
    COMBO(combo_jG,  LSFT(KC_EQL)),        // +
    COMBO(combo_lG,  KC_MINS),             // -
    COMBO(combo_uG,  LSFT(KC_MINS)),       // _
    COMBO(combo_qH2, KC_QUOT),             // '
    COMBO(combo_wH,  LSFT(KC_QUOT)),       // "
    COMBO(combo_bH,  KC_BSLS),             // \
    COMBO(combo_iG,  KC_LBRC),             // [
    COMBO(combo_oG,  KC_RBRC),             // ]
    COMBO(combo_tH,  LSFT(KC_SCLN)),       // :
    COMBO(combo_yG,  KC_SCLN),             // ;
};

/* ──────────  combo 数  ────────── */

/* ───────── Auto-mouse layer ───────── */
report_mouse_t pointing_device_task_user(report_mouse_t r){
    if(r.x||r.y||r.h||r.v){ last_mouse_activity=timer_read(); if(!mouse_layer_active){layer_on(_MOUSE);mouse_layer_active=true;}}
    return r;
}
void matrix_scan_user(void){
    if(mouse_layer_active&&timer_elapsed(last_mouse_activity)>MOUSE_TIMEOUT){
        layer_off(_MOUSE); mouse_layer_active=false;
    }
}