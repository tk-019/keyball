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
    LSFT_T(KC_Z)  , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , LT(3,KC_M)     , KC_COMM  , LT(2, KC_DOT)   , RSFT_T(S(KC_INT1))  ,
    KC_ESC  , KC_LALT  , KC_LGUI
    // 左親指
    ,KC_LCTL, LT(1,KC_LNG2),LT(2,KC_SPC)
    // 右親指
    ,LT(1,KC_SPC),LT(2,KC_LNG1)
    // 右下端
    , KC_LNG3
  ),
  // 左移動とファンクション
  [1] = LAYOUT(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_LCTL    , C(G(KC_LEFT))  , A(KC_TAB)  ,C(G(KC_RGHT)), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_ENT  ,
    KC_LSFT, LALT(KC_LEFT),A(S(KC_TAB))   , LALT(KC_RGHT)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , RSFT_T(KC_F11)   ,
    KC_ESC  , KC_LALT  , KC_LGUI  , KC_LCTL  , _______  , _______  ,      TO(2)    , TO(0) ,                                              KC_F12
  ),
  // 右移動＋マウスと左数字
  [2] = LAYOUT(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_PGUP  , KC_HOME  , KC_UP  , KC_END  , KC_PGDN  ,
    LCTL_T(S(KC_QUOT)), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_LEFT  , KC_DOWN    , KC_RGHT  , KC_ENT  ,
    LSFT_T(KC_SLSH)  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           KC_BTN3, KC_BTN1  , KC_BTN2  ,  _______ , KC_RSFT  ,
    KC_ESC   , LALT_T(KC_0)     , LGUI_T(KC_DOT)   , KC_LCTL   , KC_ENT   , KC_BSPC  ,      _______  , _______,                                   _______
  ),
  [3] = LAYOUT(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______                                   , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
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
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};      // bs
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};      // del
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};      // btn1
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};      // btn2
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};      // btn3
const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};      // tab
const uint16_t PROGMEM combo_sd[] = {KC_S, KC_D, COMBO_END};      // tab2
const uint16_t PROGMEM combo_qj[] = {KC_Q, KC_J, COMBO_END};      // '
const uint16_t PROGMEM combo_wj[] = {KC_W, KC_J, COMBO_END};      // "
const uint16_t PROGMEM combo_ej[] = {KC_E, KC_J, COMBO_END};      // !
const uint16_t PROGMEM combo_rj[] = {KC_R, KC_J, COMBO_END};      // :
const uint16_t PROGMEM combo_tj[] = {KC_T, KC_J, COMBO_END};      // ;
const uint16_t PROGMEM combo_yf[] = {KC_Y, KC_F, COMBO_END};      // ¥
const uint16_t PROGMEM combo_uf[] = {KC_U, KC_F, COMBO_END};      // +
const uint16_t PROGMEM combo_if[] = {KC_I, KC_F, COMBO_END};      // =
const uint16_t PROGMEM combo_of[] = {KC_O, KC_F, COMBO_END};      // |
const uint16_t PROGMEM combo_fp[] = {KC_P, KC_F, COMBO_END};      // %
const uint16_t PROGMEM combo_aj[] = {LCTL_T(KC_A), KC_J, COMBO_END};      // @
const uint16_t PROGMEM combo_sj[] = {KC_S, KC_J, COMBO_END};      // /
const uint16_t PROGMEM combo_dj[] = {KC_D, KC_J, COMBO_END};      // $
const uint16_t PROGMEM combo_fj[] = {KC_F, KC_J, COMBO_END};      // ?
const uint16_t PROGMEM combo_gj[] = {KC_G, KC_J, COMBO_END};      // `(バッククォート)`
const uint16_t PROGMEM combo_hf[] = {KC_H, KC_F, COMBO_END};      // #
const uint16_t PROGMEM combo_kf[] = {KC_K, KC_F, COMBO_END};      // [
const uint16_t PROGMEM combo_lf[] = {KC_L, KC_F, COMBO_END};      // ]
const uint16_t PROGMEM combo_zj[] = {LSFT_T(KC_Z), KC_J, COMBO_END};      // ~
const uint16_t PROGMEM combo_xj[] = {KC_X, KC_J, COMBO_END};      // *
const uint16_t PROGMEM combo_cj[] = {KC_C, KC_J, COMBO_END};      // ^^
const uint16_t PROGMEM combo_bj[] = {KC_B, KC_J, COMBO_END};      /* \___ */
const uint16_t PROGMEM combo_nf[] = {KC_N, KC_F, COMBO_END};      // &
const uint16_t PROGMEM combo_mf[] = {LT(3,KC_M), KC_F , COMBO_END};      // -
const uint16_t PROGMEM combo_zx[] = {LSFT_T(KC_Z), KC_X , COMBO_END};      // shift z
const uint16_t PROGMEM combo_commF[] = {KC_COMM, KC_F, COMBO_END};   // (
const uint16_t PROGMEM combo_dotF[] = {KC_DOT, KC_F, COMBO_END};    // )

combo_t key_combos[] = {
    COMBO(combo_jk, KC_BTN1), // btn1
    COMBO(combo_kl, KC_BTN2), // btn2
    COMBO(combo_jl, KC_BTN3), // btn3
    COMBO(combo_qw, KC_TAB), // tab
    COMBO(combo_sd, KC_TAB), // tab2
    COMBO(combo_io, KC_BSPC), // bs
    COMBO(combo_op, KC_DEL), // del
    COMBO(combo_qj, S(KC_7)), // '
    COMBO(combo_wj, S(KC_2)), // "
    COMBO(combo_ej, LSFT(KC_1)), // !
    COMBO(combo_rj, KC_QUOT), // :
    COMBO(combo_tj, KC_SCLN), // ;
    COMBO(combo_yf, KC_INT3), // ¥
    COMBO(combo_uf, S(KC_SCLN)), // +
    COMBO(combo_if, S(KC_MINS)), // =
    COMBO(combo_of, S(KC_INT3)), // |
    COMBO(combo_fp, S(KC_5)), // %
    COMBO(combo_aj, KC_LBRC), // @
    COMBO(combo_sj, KC_SLSH), // /
    COMBO(combo_dj, LSFT(KC_4)), // $
    COMBO(combo_fj, S(KC_SLSH)), // ?
    COMBO(combo_gj, LSFT(KC_LBRC)), // `(バッククォート)
    COMBO(combo_hf, S(KC_3)), // #
    COMBO(combo_kf, KC_RBRC), // [
    COMBO(combo_lf, KC_BSLS), // ]
    COMBO(combo_zj, S(KC_EQL)), // ~
    COMBO(combo_xj, S(KC_QUOT)), // *
    COMBO(combo_cj, KC_EQL), // ^
    COMBO(combo_bj, KC_INT1), /* \ */
    COMBO(combo_nf, S(KC_6)), // &
    COMBO(combo_mf, KC_MINS), // -
    COMBO(combo_zx, S(KC_Z)), // shift z
    COMBO(combo_commF, S(KC_8)), // (
    COMBO(combo_dotF, S(KC_9)), // )
};
#endif