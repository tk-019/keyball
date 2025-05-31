/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LCTL_T(KC_A)     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_ENT  ,
    LSFT_T(KC_Z)  , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , LT(1,KC_M)     , KC_COMM  , KC_DOT   , KC_RSFT  ,
    KC_ESC  , KC_LALT  , KC_LGUI
    // 左親指
    ,KC_LCTL, LT(1,KC_LNG2),LT(2,KC_SPC)
    // 右親指
    ,LT(1,KC_ENT),LT(2,KC_LNG1)
    // 右下端
    , KC_LNG3
  ),

  [1] = LAYOUT(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , LGUI(KC_LEFT)  , S(KC_6)  ,LGUI(KC_RGHT), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),LALT(KC_LEFT),S(KC_7)   , LALT(KC_RGHT)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0) ,                                              KC_F12
  ),

  [2] = LAYOUT(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , KC_HOME  , KC_UP  , KC_END  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_LEFT  , KC_DOWN    , KC_RGHT  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_PGUP  , KC_PGDN  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______,                                   _______
  ),
  [3] = LAYOUT(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______ , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 2);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};      // tab
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};      // bs
const uint16_t PROGMEM combo_aj[] = {KC_A, KC_J, COMBO_END};      // @
const uint16_t PROGMEM combo_sj[] = {KC_S, KC_J, COMBO_END};      // #
const uint16_t PROGMEM combo_dj[] = {KC_D, KC_J, COMBO_END};      // $
const uint16_t PROGMEM combo_pj[] = {KC_P, KC_J, COMBO_END};      // %
const uint16_t PROGMEM combo_cj[] = {KC_C, KC_J, COMBO_END};      // ^
const uint16_t PROGMEM combo_ej[] = {KC_E, KC_J, COMBO_END};      // !
const uint16_t PROGMEM combo_kf[] = {KC_K, KC_F, COMBO_END};      // *
const uint16_t PROGMEM combo_jf[] = {KC_J, KC_F, COMBO_END};      // +
const uint16_t PROGMEM combo_lf[] = {KC_L, KC_F, COMBO_END};      // -
const uint16_t PROGMEM combo_uf[] = {KC_U, KC_F, COMBO_END};      // _
const uint16_t PROGMEM combo_qf[] = {KC_Q, KC_F, COMBO_END};      // '
const uint16_t PROGMEM combo_wf[] = {KC_W, KC_F, COMBO_END};      // "
const uint16_t PROGMEM combo_bf[] = {KC_B, KC_F, COMBO_END};      /* \ */
const uint16_t PROGMEM combo_if[] = {KC_I, KC_F, COMBO_END};      // [
const uint16_t PROGMEM combo_of[] = {KC_O, KC_F, COMBO_END};      // ]
const uint16_t PROGMEM combo_tf[] = {KC_T, KC_F, COMBO_END};      // :
const uint16_t PROGMEM combo_yf[] = {KC_Y, KC_F, COMBO_END};      // ;
const uint16_t PROGMEM combo_fj[] = {KC_F, KC_J, COMBO_END};      // ?

combo_t key_combos[] = {
    COMBO(combo_qw, KC_TAB),
    COMBO(combo_op, KC_BSPC),
    COMBO(combo_aj,  LSFT(KC_2)),          // @
    COMBO(combo_sj,  LSFT(KC_3)),          // #
    COMBO(combo_dj,  LSFT(KC_4)),          // $
    COMBO(combo_pj,  LSFT(KC_5)),          // %
    COMBO(combo_cj,  LSFT(KC_6)),          // ^
    COMBO(combo_ej,  LSFT(KC_1)),          // !
    COMBO(combo_kf,  LSFT(KC_8)),          // *
    COMBO(combo_jf,  LSFT(KC_EQL)),        // +
    COMBO(combo_lf,  KC_MINS),             // -
    COMBO(combo_uf,  S(KC_INT1)),       // _
    COMBO(combo_qf, KC_QUOT),              // '
    COMBO(combo_wf,  LSFT(KC_QUOT)),       // "
    COMBO(combo_bf,  KC_BSLS),             /* \ */
    COMBO(combo_if,  KC_LBRC),             // [
    COMBO(combo_of,  KC_RBRC),             // ]
    COMBO(combo_tf,  LSFT(KC_SCLN)),       // :
    COMBO(combo_yf,  KC_SCLN),             // ;
    COMBO(combo_fj,  LSFT(KC_SLSH)),       // /
};
#endif