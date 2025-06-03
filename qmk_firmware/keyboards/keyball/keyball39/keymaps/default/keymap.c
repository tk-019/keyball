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
    LSFT_T(KC_Z)  , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , LT(3,KC_M)     , KC_COMM  , LT(2, KC_DOT)   , RSFT_T(LSFT(KC_SLSH))  ,
    KC_ESC  , KC_LALT  , KC_LGUI
    // 左親指
    ,KC_LCTL, LT(1,KC_LNG2),LT(2,KC_SPC)
    // 右親指
    ,LT(1,KC_SPC),LT(2,KC_LNG1)
    // 右下端
    , LT(3,LSFT(KC_INT1))
  ),
  // 左移動とファンクション
  [1] = LAYOUT(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_LCTL    , LCTL(LGUI(KC_LEFT))  , LGUI(KC_TAB)  ,LCTL(LGUI(KC_RGHT)), LSFT(KC_8)  ,                           LSFT(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_ENT  ,
    KC_LSFT, LALT(KC_LEFT),LALT(KC_TAB)   , LALT(KC_RGHT)  ,LSFT(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , RSFT_T(KC_F11)   ,
    KC_ESC  , KC_LALT  , KC_LGUI  , KC_LCTL  , _______  , _______  ,      TO(2)    , TO(0) ,                                              KC_F12
  ),
  // 右移動＋マウスと左数字
  [2] = LAYOUT(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_PGUP  , KC_HOME  , KC_UP  , KC_END  , KC_PGDN  ,
    KC_LCTL, KC_4     , KC_5     , KC_6     ,LSFT(KC_SCLN),                            LSFT(KC_9)  , KC_LEFT  , KC_DOWN    , KC_RGHT  , KC_ENT  ,
    KC_LSFT , KC_1     , KC_2     , KC_3     ,LSFT(KC_MINS),                           KC_BTN3, KC_BTN1  , KC_BTN2  ,  _______ , KC_RSFT  ,
    KC_ESC   , LALT_T(KC_0)     , ALT_T(KC_DOT)   , KC_LCTL   , KC_ENT   , KC_BSPC  ,      _______  , _______,                                   _______
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
// ① カスタムキーコードを名前で定義
enum custom_keycodes {
    CA_IO = SAFE_RANGE,   // 元々 COMBO(combo_io) がトリガー → バックスペース
    CA_OP,                // COMBO(combo_op) → 「ー」
    CA_JK,                // COMBO(combo_jk) → BTN1
    CA_KL,                // COMBO(combo_kl) → BTN2
    CA_JL,                // COMBO(combo_jl) → BTN3
    CA_QW,                // COMBO(combo_qw) → TAB
    CA_SD,                // COMBO(combo_sd) → TAB
    CA_QJ,                // COMBO(combo_qj) → "'"
    CA_WJ,                // COMBO(combo_wj) → '"'
    CA_EJ,                // COMBO(combo_ej) → "!"
    CA_RJ,                // COMBO(combo_rj) → ":"
    CA_TJ,                // COMBO(combo_tj) → ";"
    CA_YF,                // COMBO(combo_yf) → "¥"
    CA_UF,                // COMBO(combo_uf) → "+"
    CA_IF,                // COMBO(combo_if) → "="
    CA_OF,                // COMBO(combo_of) → "|"
    CA_FP,                // COMBO(combo_fp) → "%"
    CA_AJ,                // COMBO(combo_aj) → "@"
    CA_SJ,                // COMBO(combo_sj) → "/"
    CA_DJ,                // COMBO(combo_dj) → "$"
    CA_FJ,                // COMBO(combo_fj) → "?"
    CA_GJ,                // COMBO(combo_gj) → "`"
    CA_HF,                // COMBO(combo_hf) → "#"
    CA_KF,                // COMBO(combo_kf) → "["
    CA_LF,                // COMBO(combo_lf) → "]"
    CA_ZJ,                // COMBO(combo_zj) → "~"
    CA_XJ,                // COMBO(combo_xj) → "*"
    CA_CJ,                // COMBO(combo_cj) → "^"
    CA_BJ,                // COMBO(combo_bj) → "\"（バックスラッシュ）
    CA_NF,                // COMBO(combo_nf) → "&"
    CA_MF,                // COMBO(combo_mf) → "-"
    CA_ZX,                // COMBO(combo_zx) → Shift+Z
    CA_COMM_F,            // COMBO(combo_commF) → "("
    CA_DOT_F,             // COMBO(combo_dotF) → ")"
};

// ② マップ用テーブルを作る
static const combo_action_t combo_actions[] = {
    // trigger,           mods,                           keycode,       delay
    { CA_IO,       0,                               KC_BSPC,        0   },
    { CA_OP,       0,                               KC_MHEN,        0   },  // 「ー」が無ければ KC_MINS
    { CA_JK,       0,                               KC_BTN1,        0   },
    { CA_KL,       0,                               KC_BTN2,        0   },
    { CA_JL,       0,                               KC_BTN3,        0   },
    { CA_QW,       0,                               KC_TAB,         0   },
    { CA_SD,       0,                               KC_TAB,         0   },
    { CA_QJ,       0,                               KC_QUOT,        0   },
    { CA_WJ,       MOD_BIT(KC_LSFT),               KC_QUOT,        5   },
    { CA_EJ,       MOD_BIT(KC_LSFT),               KC_1,           5   },
    { CA_RJ,       MOD_BIT(KC_LSFT),               KC_SCLN,        5   },
    { CA_TJ,       0,                               KC_SCLN,        0   },
    { CA_YF,       0,                               KC_INT3,        0   },
    { CA_UF,       MOD_BIT(KC_LSFT),               KC_SCLN,        5   },
    { CA_IF,       MOD_BIT(KC_LSFT),               KC_MINS,        5   },
    { CA_OF,       MOD_BIT(KC_LSFT),               KC_INT3,        5   },
    { CA_FP,       MOD_BIT(KC_LSFT),               KC_5,           5   },
    { CA_AJ,       0,                               KC_LBRC,        0   },
    { CA_SJ,       0,                               KC_SLSH,        0   },
    { CA_DJ,       MOD_BIT(KC_LSFT),               KC_4,           5   },
    { CA_FJ,       MOD_BIT(KC_LSFT),               KC_SLSH,        5   },
    { CA_GJ,       0,                               KC_GRV,         0   },
    { CA_HF,       MOD_BIT(KC_LSFT),               KC_3,           5   },
    { CA_KF,       MOD_BIT(KC_LSFT),               KC_LBRC,        5   },
    { CA_LF,       0,                               KC_RBRC,        0   },
    { CA_ZJ,       MOD_BIT(KC_LSFT),               KC_EQL,         5   },
    { CA_XJ,       MOD_BIT(KC_LSFT),               KC_8,           5   },
    { CA_CJ,       0,                               KC_EQL,         0   },
    { CA_BJ,       0,                               KC_INT1,        0   },
    { CA_NF,       MOD_BIT(KC_LSFT),               KC_6,           5   },
    { CA_MF,       0,                               KC_MINS,        0   },
    { CA_ZX,       MOD_BIT(KC_LSFT),               KC_Z,           5   },
    { CA_COMM_F,   MOD_BIT(KC_LSFT),               KC_8,           5   },
    { CA_DOT_F,    MOD_BIT(KC_LSFT),               KC_9,           5   },
};
static const uint16_t combo_actions_count = sizeof(combo_actions) / sizeof(combo_actions[0]);

// ③ key_combos を名前に合わせて書き換え
combo_t key_combos[] = {
    COMBO(combo_io,    CA_IO),
    COMBO(combo_op,    CA_OP),
    COMBO(combo_jk,    CA_JK),
    COMBO(combo_kl,    CA_KL),
    COMBO(combo_jl,    CA_JL),
    COMBO(combo_qw,    CA_QW),
    COMBO(combo_sd,    CA_SD),
    COMBO(combo_qj,    CA_QJ),
    COMBO(combo_wj,    CA_WJ),
    COMBO(combo_ej,    CA_EJ),
    COMBO(combo_rj,    CA_RJ),
    COMBO(combo_tj,    CA_TJ),
    COMBO(combo_yf,    CA_YF),
    COMBO(combo_uf,    CA_UF),
    COMBO(combo_if,    CA_IF),
    COMBO(combo_of,    CA_OF),
    COMBO(combo_fp,    CA_FP),
    COMBO(combo_aj,    CA_AJ),
    COMBO(combo_sj,    CA_SJ),
    COMBO(combo_dj,    CA_DJ),
    COMBO(combo_fj,    CA_FJ),
    COMBO(combo_gj,    CA_GJ),
    COMBO(combo_hf,    CA_HF),
    COMBO(combo_kf,    CA_KF),
    COMBO(combo_lf,    CA_LF),
    COMBO(combo_zj,    CA_ZJ),
    COMBO(combo_xj,    CA_XJ),
    COMBO(combo_cj,    CA_CJ),
    COMBO(combo_bj,    CA_BJ),
    COMBO(combo_nf,    CA_NF),
    COMBO(combo_mf,    CA_MF),
    COMBO(combo_zx,    CA_ZX),
    COMBO(combo_commF, CA_COMM_F),
    COMBO(combo_dotF,  CA_DOT_F),
};
uint8_t COMBO_COUNT = sizeof(key_combos) / sizeof(key_combos[0]);

// ① カスタムキーコードを名前で定義
enum custom_keycodes {
    CA_IO = SAFE_RANGE,   // 元々 COMBO(combo_io) がトリガー → バックスペース
    CA_OP,                // COMBO(combo_op) → 「ー」
    CA_JK,                // COMBO(combo_jk) → BTN1
    CA_KL,                // COMBO(combo_kl) → BTN2
    CA_JL,                // COMBO(combo_jl) → BTN3
    CA_QW,                // COMBO(combo_qw) → TAB
    CA_SD,                // COMBO(combo_sd) → TAB
    CA_QJ,                // COMBO(combo_qj) → "'"
    CA_WJ,                // COMBO(combo_wj) → '"'
    CA_EJ,                // COMBO(combo_ej) → "!"
    CA_RJ,                // COMBO(combo_rj) → ":"
    CA_TJ,                // COMBO(combo_tj) → ";"
    CA_YF,                // COMBO(combo_yf) → "¥"
    CA_UF,                // COMBO(combo_uf) → "+"
    CA_IF,                // COMBO(combo_if) → "="
    CA_OF,                // COMBO(combo_of) → "|"
    CA_FP,                // COMBO(combo_fp) → "%"
    CA_AJ,                // COMBO(combo_aj) → "@"
    CA_SJ,                // COMBO(combo_sj) → "/"
    CA_DJ,                // COMBO(combo_dj) → "$"
    CA_FJ,                // COMBO(combo_fj) → "?"
    CA_GJ,                // COMBO(combo_gj) → "`"
    CA_HF,                // COMBO(combo_hf) → "#"
    CA_KF,                // COMBO(combo_kf) → "["
    CA_LF,                // COMBO(combo_lf) → "]"
    CA_ZJ,                // COMBO(combo_zj) → "~"
    CA_XJ,                // COMBO(combo_xj) → "*"
    CA_CJ,                // COMBO(combo_cj) → "^"
    CA_BJ,                // COMBO(combo_bj) → "\"（バックスラッシュ）
    CA_NF,                // COMBO(combo_nf) → "&"
    CA_MF,                // COMBO(combo_mf) → "-"
    CA_ZX,                // COMBO(combo_zx) → Shift+Z
    CA_COMM_F,            // COMBO(combo_commF) → "("
    CA_DOT_F,             // COMBO(combo_dotF) → ")"
};

// ② マップ用テーブルを作る
static const combo_action_t combo_actions[] = {
    // trigger,           mods,                           keycode,       delay
    { CA_IO,       0,                               KC_BSPC,        0   },
    { CA_OP,       0,                               KC_MINS,        0   },  // 「ー」が無ければ KC_MINS
    { CA_JK,       0,                               KC_BTN1,        0   },
    { CA_KL,       0,                               KC_BTN2,        0   },
    { CA_JL,       0,                               KC_BTN3,        0   },
    { CA_QW,       0,                               KC_TAB,         0   },
    { CA_SD,       0,                               KC_TAB,         0   },
    { CA_QJ,       0,                               KC_QUOT,        0   },
    { CA_WJ,       MOD_BIT(KC_LSFT),               KC_QUOT,        5   },
    { CA_EJ,       MOD_BIT(KC_LSFT),               KC_1,           5   },
    { CA_RJ,       MOD_BIT(KC_LSFT),               KC_SCLN,        5   },
    { CA_TJ,       0,                               KC_SCLN,        0   },
    { CA_YF,       0,                               KC_INT3,        0   },
    { CA_UF,       MOD_BIT(KC_LSFT),               KC_SCLN,        5   },
    { CA_IF,       MOD_BIT(KC_LSFT),               KC_MINS,        5   },
    { CA_OF,       MOD_BIT(KC_LSFT),               KC_INT3,        5   },
    { CA_FP,       MOD_BIT(KC_LSFT),               KC_5,           5   },
    { CA_AJ,       0,                               KC_LBRC,        0   },
    { CA_SJ,       0,                               KC_SLSH,        0   },
    { CA_DJ,       MOD_BIT(KC_LSFT),               KC_4,           5   },
    { CA_FJ,       MOD_BIT(KC_LSFT),               KC_SLSH,        5   },
    { CA_GJ,       0,                               KC_GRV,         0   },
    { CA_HF,       MOD_BIT(KC_LSFT),               KC_3,           5   },
    { CA_KF,       MOD_BIT(KC_LSFT),               KC_LBRC,        5   },
    { CA_LF,       0,                               KC_RBRC,        0   },
    { CA_ZJ,       MOD_BIT(KC_LSFT),               KC_EQL,         5   },
    { CA_XJ,       MOD_BIT(KC_LSFT),               KC_8,           5   },
    { CA_CJ,       0,                               KC_EQL,         0   },
    { CA_BJ,       0,                               KC_INT1,        0   },
    { CA_NF,       MOD_BIT(KC_LSFT),               KC_6,           5   },
    { CA_MF,       0,                               KC_MINS,        0   },
    { CA_ZX,       MOD_BIT(KC_LSFT),               KC_Z,           5   },
    { CA_COMM_F,   MOD_BIT(KC_LSFT),               KC_8,           5   },
    { CA_DOT_F,    MOD_BIT(KC_LSFT),               KC_9,           5   },
};
static const uint16_t combo_actions_count = sizeof(combo_actions) / sizeof(combo_actions[0]);

// ③ key_combos を名前に合わせて書き換え
combo_t key_combos[] = {
    COMBO(combo_io,    CA_IO),
    COMBO(combo_op,    CA_OP),
    COMBO(combo_jk,    CA_JK),
    COMBO(combo_kl,    CA_KL),
    COMBO(combo_jl,    CA_JL),
    COMBO(combo_qw,    CA_QW),
    COMBO(combo_sd,    CA_SD),
    COMBO(combo_qj,    CA_QJ),
    COMBO(combo_wj,    CA_WJ),
    COMBO(combo_ej,    CA_EJ),
    COMBO(combo_rj,    CA_RJ),
    COMBO(combo_tj,    CA_TJ),
    COMBO(combo_yf,    CA_YF),
    COMBO(combo_uf,    CA_UF),
    COMBO(combo_if,    CA_IF),
    COMBO(combo_of,    CA_OF),
    COMBO(combo_fp,    CA_FP),
    COMBO(combo_aj,    CA_AJ),
    COMBO(combo_sj,    CA_SJ),
    COMBO(combo_dj,    CA_DJ),
    COMBO(combo_fj,    CA_FJ),
    COMBO(combo_gj,    CA_GJ),
    COMBO(combo_hf,    CA_HF),
    COMBO(combo_kf,    CA_KF),
    COMBO(combo_lf,    CA_LF),
    COMBO(combo_zj,    CA_ZJ),
    COMBO(combo_xj,    CA_XJ),
    COMBO(combo_cj,    CA_CJ),
    COMBO(combo_bj,    CA_BJ),
    COMBO(combo_nf,    CA_NF),
    COMBO(combo_mf,    CA_MF),
    COMBO(combo_zx,    CA_ZX),
    COMBO(combo_commF, CA_COMM_F),
    COMBO(combo_dotF,  CA_DOT_F),
};
uint8_t COMBO_COUNT = sizeof(key_combos) / sizeof(key_combos[0]);

bool process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return true;

    // combo_index に対応するアクションをテーブルから探す
    for (uint16_t i = 0; i < combo_actions_count; i++) {
        if (combo_actions[i].trigger == combo_index) {
            uint16_t mods    = combo_actions[i].mods;
            uint16_t keycode = combo_actions[i].keycode;
            uint8_t  delay   = combo_actions[i].delay;

            // 修飾キーを register → 少し待つ → 本キーを tap → 修飾キーを解除
            if (mods) register_code16(mods);
            if (delay) wait_ms(delay);
            tap_code(keycode);
            if (mods) unregister_code16(mods);
            return false;
        }
    }
    return true;
}
typedef struct {
    uint16_t trigger;   // カスタムキーコード（CA_XXX）
    uint16_t mods;      // 押しっぱなしにする修飾キー（MOD_BIT(KC_LSFT) など）
    uint16_t keycode;   // 実際に tap_code() で送るキー
    uint8_t  delay;     // register→tap の間に挟むウェイト(ms)
} combo_action_t;

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};      // bs
const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};      // ー
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
