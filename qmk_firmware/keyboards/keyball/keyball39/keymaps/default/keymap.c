#include QMK_KEYBOARD_H

#include "quantum.h"
#include "keymap_japanese.h"


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LCTL_T(KC_A)     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_ENT  ,
    LSFT_T(KC_Z)  , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , LT(3,KC_M)     , KC_COMM  , KC_DOT   , RSFT_T(LSFT(KC_SLSH))  ,
    KC_ESC  ,  KC_LGUI  ,KC_LALT
    // 左親指
    ,KC_LCTL,LT(1,KC_LNG2),KC_LSFT
    // 右親指
    ,LT(2,KC_SPC),LT(1,KC_LNG1)
    // 右下端
    , KC_INT1
    //, LT(3,LSFT(KC_INT1))
  ),
  // 左右移動と数字
  [1] = LAYOUT(
    _______   , KC_F2     , _______     , _______     , _______  ,                            KC_PGUP  , KC_HOME  , KC_UP  , KC_END  , KC_DOWN  ,
    KC_LCTL    , LCTL(LGUI(KC_LEFT))  , _______  ,LCTL(LGUI(KC_RGHT)), LSFT(KC_8)  ,                           _______  , KC_LEFT  , KC_DOWN    , KC_RGHT  , _______  ,
    KC_LSFT, _______,_______   , _______  ,_______,                            _______, _______  , _______  ,  _______ , KC_RSFT  ,
    KC_ESC  ,  KC_LGUI  ,KC_LALT  ,KC_LCTL,  _______    , _______  ,      _______    , _______ ,                                              _______
  ),
  // ファンクションと記号
  [2] = LAYOUT(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5   ,                            KC_6  , KC_7  , KC_8    , KC_9  , KC_0  ,
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    _______ , _______     , _______     , _______     ,_______,                           _______, _______  , _______  ,  _______ , KC_F11  ,
    _______   , _______     , _______      ,_______,  _______, _______     ,      _______  , _______,                                   KC_F12
  ),
  [3] = LAYOUT(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    KC_LCTL  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_LSFT , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KC_RSFT ,
    KC_ESC  , KC_LGUI  , KC_LALT  , _______  , _______  , _______  ,      _______  , _______                                   , QK_BOOT
  ),
  // [4] = LAYOUT(
  //   KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_LNG1  , KC_7     , KC_8     , KC_9     , KC_BSPC  ,
  //   KC_LCTL  , KC_F6    , KC_F7    , KC_F8    , KC_F9    ,                            KC_LNG2  , KC_4     , KC_5     , KC_6     , KC_ENT   ,
  //   KC_LSFT  , KC_F10   , KC_F11   , KC_F12   , _______  ,                            KC_0     , KC_1     , KC_2     , KC_3     , KC_RSFT  ,
  //   KC_ESC   , KC_LGUI  , KC_LALT  , _______  , _______  , _______  ,      _______     , _______                                    , _______
  // ),
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
const uint16_t PROGMEM combo_commDot[] = {KC_COMM, KC_DOT, COMBO_END};      // _
const uint16_t PROGMEM combo_xc[] = {KC_X, KC_C, COMBO_END};      // win
const uint16_t PROGMEM combo_89[] = {KC_8, KC_9, COMBO_END};      // bs
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};      // bs
const uint16_t PROGMEM combo_ui[] = {KC_U, KC_I, COMBO_END};      // del
const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};      // f2
const uint16_t PROGMEM combo_sd[] = {KC_S, KC_D, COMBO_END};      // tab
const uint16_t PROGMEM combo_df[] = {KC_D, KC_F, COMBO_END};      // Space
const uint16_t PROGMEM combo_zx[] = {LSFT_T(KC_Z), KC_X, COMBO_END};      // shift
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};      // ー
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};      // btn1
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};      // btn2
const uint16_t PROGMEM combo_jl[] = {KC_J, KC_L, COMBO_END};      // btn3
const uint16_t PROGMEM combo_qj[] = {KC_Q, KC_J, COMBO_END};      // !
const uint16_t PROGMEM combo_wj[] = {KC_W, KC_J, COMBO_END};      // "
const uint16_t PROGMEM combo_ej[] = {KC_E, KC_J, COMBO_END};      // #
const uint16_t PROGMEM combo_rj[] = {KC_R, KC_J, COMBO_END};      // $
const uint16_t PROGMEM combo_tj[] = {KC_T, KC_J, COMBO_END};      // %
const uint16_t PROGMEM combo_yf[] = {KC_Y, KC_F, COMBO_END};      // &
const uint16_t PROGMEM combo_uf[] = {KC_U, KC_F, COMBO_END};      // '
const uint16_t PROGMEM combo_if[] = {KC_I, KC_F, COMBO_END};      // (
const uint16_t PROGMEM combo_of[] = {KC_O, KC_F, COMBO_END};      // )
const uint16_t PROGMEM combo_fp[] = {KC_P, KC_F, COMBO_END};      // =
const uint16_t PROGMEM combo_aj[] = {LCTL_T(KC_A), KC_J, COMBO_END};      // @
const uint16_t PROGMEM combo_dj[] = {KC_D, KC_J, COMBO_END};      // |
const uint16_t PROGMEM combo_fj[] = {KC_F, KC_J, COMBO_END};      // +
const uint16_t PROGMEM combo_gj[] = {KC_G, KC_J, COMBO_END};      // `(バッククォート)`
const uint16_t PROGMEM combo_kf[] = {KC_K, KC_F, COMBO_END};      // *
const uint16_t PROGMEM combo_lf[] = {KC_L, KC_F, COMBO_END};      // ;
const uint16_t PROGMEM combo_entf[] = {KC_ENT, KC_F, COMBO_END};      // ;
const uint16_t PROGMEM combo_cj[] = {KC_C, KC_J, COMBO_END};      // ^
const uint16_t PROGMEM combo_bj[] = {KC_B, KC_J, COMBO_END};      /* \___ */
const uint16_t PROGMEM combo_nf[] = {KC_N, KC_F, COMBO_END};      // ~
const uint16_t PROGMEM combo_commF[] = {KC_COMM, KC_F, COMBO_END};   // [
const uint16_t PROGMEM combo_dotF[] = {KC_DOT, KC_F, COMBO_END};    // ]

combo_t key_combos[] = {
    COMBO(combo_commDot, JP_UNDS), // _
    COMBO(combo_xc, KC_LWIN), // win
    COMBO(combo_89, KC_BSPC), // bs
    COMBO(combo_io, KC_BSPC), // bs
    COMBO(combo_ui, KC_DELETE), // del
    COMBO(combo_we, KC_F2), // f2
    COMBO(combo_sd, KC_TAB), // tab2
    COMBO(combo_df, KC_SPC),  // Space
    COMBO(combo_zx, KC_LSFT), // shift
    COMBO(combo_jk, KC_BTN1), // btn1
    COMBO(combo_kl, KC_BTN2), // btn2
    COMBO(combo_jl, KC_BTN3), // btn3
    COMBO(combo_op, JP_MINS), // -
    COMBO(combo_qj, JP_EXLM), // !
    COMBO(combo_wj, JP_DQUO), // "
    COMBO(combo_ej, JP_HASH), // #
    COMBO(combo_rj, JP_DLR), // $
    COMBO(combo_tj, JP_PERC), // %
    COMBO(combo_yf, JP_AMPR), // &
    COMBO(combo_uf, JP_QUOT), // '
    COMBO(combo_if, JP_LPRN), // (
    COMBO(combo_of, JP_RPRN), // )
    COMBO(combo_fp, JP_PIPE), // |
    COMBO(combo_aj, JP_AT), // @
    // COMBO(combo_dj, JP_PIPE), // |
    COMBO(combo_fj, JP_PLUS), // +
    COMBO(combo_gj, JP_GRV), // `(バッククォート)
    COMBO(combo_kf, JP_ASTR), // *
    COMBO(combo_lf, JP_COLN), // :
    COMBO(combo_entf, JP_SCLN), // ;
    COMBO(combo_cj, JP_CIRC), // ^
    COMBO(combo_bj, JP_BSLS), // ¥
    COMBO(combo_nf, JP_TILD), // ~
    COMBO(combo_commF, JP_LBRC), // [
    COMBO(combo_dotF, JP_RBRC), // ]
};
#endif