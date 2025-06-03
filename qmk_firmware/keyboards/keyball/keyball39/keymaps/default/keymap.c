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

// ---------------------------------------------
// 1) まず「コンボ用のキー配列」を定義しておく
//    （後ろで COMBO() するときに使う配列）
//
//    例）combo_io は〈I と O を同時押し〉でトリガー
// ---------------------------------------------
#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_io[]    = { KC_I,  KC_O,  COMBO_END };   // Backspace
const uint16_t PROGMEM combo_op[]    = { KC_O,  KC_P,  COMBO_END };   // 「ー」（JIS だと長音記号）
// ... 以下、必要な combo_xxx[] をすべて同様に定義 ...
const uint16_t PROGMEM combo_jk[]    = { KC_J,  KC_K,  COMBO_END };   // BTN1
const uint16_t PROGMEM combo_kl[]    = { KC_K,  KC_L,  COMBO_END };   // BTN2
const uint16_t PROGMEM combo_jl[]    = { KC_J,  KC_L,  COMBO_END };   // BTN3
const uint16_t PROGMEM combo_qw[]    = { KC_Q,  KC_W,  COMBO_END };   // TAB
const uint16_t PROGMEM combo_sd[]    = { KC_S,  KC_D,  COMBO_END };   // TAB (別パターン)
/* 省略: “combo_qj, combo_wj, … combo_dotF” など、必要なものをすべて */
#endif

// ---------------------------------------------
// 2) カスタムキーコードを「名前付き enum」で定義する
//    SAFE_RANGE 以降を使って重複しないようにする
// ---------------------------------------------
enum custom_keycodes {
    CA_IO = SAFE_RANGE,   // combo_io のトリガー → Backspace
    CA_OP,                // combo_op → 「ー」
    CA_JK,                // combo_jk → BTN1
    CA_KL,                // combo_kl → BTN2
    CA_JL,                // combo_jl → BTN3
    CA_QW,                // combo_qw → TAB
    CA_SD,                // combo_sd → TAB
    CA_QJ,                // combo_qj → "'"
    CA_WJ,                // combo_wj → '"'
    CA_EJ,                // combo_ej → "!"
    CA_RJ,                // combo_rj → ":"
    CA_TJ,                // combo_tj → ";"
    CA_YF,                // combo_yf → "¥"
    CA_UF,                // combo_uf → "+"
    CA_IF,                // combo_if → "="
    CA_OF,                // combo_of → "|"
    CA_FP,                // combo_fp → "%"
    CA_AJ,                // combo_aj → "@"
    CA_SJ,                // combo_sj → "/"
    CA_DJ,                // combo_dj → "$"
    CA_FJ,                // combo_fj → "?"
    CA_GJ,                // combo_gj → "`"
    CA_HF,                // combo_hf → "#"
    CA_KF,                // combo_kf → "["
    CA_LF,                // combo_lf → "]"
    CA_ZJ,                // combo_zj → "~"
    CA_XJ,                // combo_xj → "*"
    CA_CJ,                // combo_cj → "^"
    CA_BJ,                // combo_bj → "\"（バックスラッシュ）
    CA_NF,                // combo_nf → "&"
    CA_MF,                // combo_mf → "-"
    CA_ZX,                // combo_zx → Shift + Z
    CA_COMM_F,            // combo_commF → "("
    CA_DOT_F,             // combo_dotF → ")"
};

// ---------------------------------------------
// 3) 「combo_action_t の typedef」を使う前に必ず先に宣言する
//    （これがないと unknown type name 'combo_action_t' エラーになる）
// ---------------------------------------------
typedef struct {
    uint16_t trigger;   // カスタムキーコード（enum custom_keycodes の値）
    uint16_t mods;      // 押しっぱなしにする修飾キー (MOD_BIT(KC_LSFT) など)
    uint16_t keycode;   // 実際に tap_code() で送るキー
    uint8_t  delay;     // register→tap の間に挟むウェイト(ms)
} combo_action_t;

// ---------------------------------------------
// 4) combo_actions 配列を定義する
//    （trigger に一致したときに mods を register してから keycode を tap する）
// ---------------------------------------------
static const combo_action_t combo_actions[] = {
    // 触発キー      修飾キー    実際に送るキー   ディレイ(ms)
    { CA_IO,       0,                     KC_BSPC,      0 },   // I+O → Backspace
    { CA_OP,       0,                     KC_MINS,      0 },   // O+P → 「ー」（JIS 環境で長音記号がなければ MINS）
    { CA_JK,       0,                     KC_BTN1,      0 },   // J+K → 鼠標左クリック
    { CA_KL,       0,                     KC_BTN2,      0 },   // K+L → 鼠標中クリック
    { CA_JL,       0,                     KC_BTN3,      0 },   // J+L → 鼠標右クリック
    { CA_QW,       0,                     KC_TAB,       0 },   // Q+W → Tab
    { CA_SD,       0,                     KC_TAB,       0 },   // S+D → Tab（別パターン）
    { CA_QJ,       0,                     KC_QUOT,      0 },   // Q+J → '
    { CA_WJ,       MOD_BIT(KC_LSFT),      KC_QUOT,      5 },   // W+J → "  （Shift+ '）
    { CA_EJ,       MOD_BIT(KC_LSFT),      KC_1,         5 },   // E+J → !  （Shift+1）
    { CA_RJ,       MOD_BIT(KC_LSFT),      KC_SCLN,      5 },   // R+J → :  （Shift+;）
    { CA_TJ,       0,                     KC_SCLN,      0 },   // T+J → ;  
    { CA_YF,       0,                     KC_INT3,      0 },   // Y+F → ¥
    { CA_UF,       MOD_BIT(KC_LSFT),      KC_SCLN,      5 },   // U+F → +  (Shift+;)
    { CA_IF,       MOD_BIT(KC_LSFT),      KC_MINS,      5 },   // I+F → =  (Shift+-)
    { CA_OF,       MOD_BIT(KC_LSFT),      KC_INT3,      5 },   // O+F → |  (Shift+¥)
    { CA_FP,       MOD_BIT(KC_LSFT),      KC_5,         5 },   // F+P → %  (Shift+5)
    { CA_AJ,       0,                     KC_LBRC,      0 },   // A+J → @  (JIS 配列の場合: '[' キーが @ に相当)
    { CA_SJ,       0,                     KC_SLSH,      0 },   // S+J → /  (スラッシュ)
    { CA_DJ,       MOD_BIT(KC_LSFT),      KC_4,         5 },   // D+J → $  (Shift+4)
    { CA_FJ,       MOD_BIT(KC_LSFT),      KC_SLSH,      5 },   // F+J → ?  (Shift+/)
    { CA_GJ,       0,                     KC_GRV,       0 },   // G+J → `(バッククォート)
    { CA_HF,       MOD_BIT(KC_LSFT),      KC_3,         5 },   // H+F → #  (Shift+3)
    { CA_KF,       MOD_BIT(KC_LSFT),      KC_LBRC,      5 },   // K+F → [  (Shift+[)
    { CA_LF,       0,                     KC_RBRC,      0 },   // L+F → ]  
    { CA_ZJ,       MOD_BIT(KC_LSFT),      KC_EQL,       5 },   // Z+J → ~  (Shift+=)
    { CA_XJ,       MOD_BIT(KC_LSFT),      KC_8,         5 },   // X+J → *  (Shift+8)
    { CA_CJ,       0,                     KC_EQL,       0 },   // C+J → ^  (JIS 配列で = キーが ^ に相当)
    { CA_BJ,       0,                     KC_INT1,      0 },   // B+J → "\"(バックスラッシュ) -> INT1=円マーク としてもよい
    { CA_NF,       MOD_BIT(KC_LSFT),      KC_6,         5 },   // N+F → &  (Shift+6)
    { CA_MF,       0,                     KC_MINS,      0 },   // M+F → -  
    { CA_ZX,       MOD_BIT(KC_LSFT),      KC_Z,         5 },   // Z+X → Shift+Z （例として）
    { CA_COMM_F,   MOD_BIT(KC_LSFT),      KC_8,         5 },   // ,+F → (  （Shift+8）
    { CA_DOT_F,    MOD_BIT(KC_LSFT),      KC_9,         5 },   // .+F → )  （Shift+9）
};
static const uint16_t combo_actions_count = sizeof(combo_actions) / sizeof(combo_actions[0]);

// ---------------------------------------------
// 5) key_combos[] で “どの配列がどのカスタムキーコードを呼ぶか” を指定
// ---------------------------------------------
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

// ---------------------------------------------
// 6) process_combo_event() を実装する
//    「どの combo_index (= key_combos[] のインデックス) が押されたか」を見て
//    combo_actions[] 配列から実際のキー出力を行う
// ---------------------------------------------
bool process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return true;  // 押下解除は無視

    // combo_actions[] からトリガーを検索
    for (uint16_t i = 0; i < combo_actions_count; i++) {
        if (combo_actions[i].trigger == combo_index) {
            uint16_t mods    = combo_actions[i].mods;
            uint16_t keycode = combo_actions[i].keycode;
            uint8_t  delay   = combo_actions[i].delay;

            if (mods) {
                register_code16(mods);
                wait_ms(delay);
                tap_code(keycode);
                unregister_code16(mods);
            } else {
                tap_code(keycode);
            }
            return false;  // QMK標準の“キーを処理済み”として扱う
        }
    }
    return true;  // 該当する trigger がなければ標準処理へ
}

// ---------------------------------------------
// 7) 通常のレイヤー定義など
// ---------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                   KC_Y    , KC_U    , KC_I    , KC_O    , KC_P,
        LCTL_T(KC_A), KC_S, KC_D,  KC_F,    KC_G,                        KC_H,   KC_J,   KC_K,   KC_L,   KC_ENT,
        LSFT_T(KC_Z), KC_X, KC_C,  KC_V,    KC_B,                        KC_N,   LT(3,KC_M), KC_COMM, LT(2,KC_DOT), RSFT_T(KC_SLSH),
        KC_ESC ,KC_LALT,KC_LGUI ,    KC_LCTL, LT(1, KC_LNG2), LT(2, KC_SPC), LT(1, KC_SPC), LT(2, KC_LNG1), _______, _______, KC_LNG3
    ),
    [1] = LAYOUT(
        KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                   KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10,
        KC_LCTL, LCTL(LGUI(KC_LEFT)), LGUI(KC_TAB), LCTL(LGUI(KC_RGHT)), LSFT(KC_8),        LSFT(KC_INT1), KC_BTN1, KC_PGUP, KC_BTN2, KC_ENT,
        KC_LSFT, LALT(KC_LEFT), LALT(KC_TAB), LALT(KC_RGHT), LSFT(KC_RBRC),           KC_LBRC, KC_DLR, KC_PGDN, KC_BTN3, RSFT_T(KC_F11),
        KC_ESC, KC_LALT, KC_LGUI, KC_LCTL, _______, _______, TO(2), TO(0), _______, _______, KC_F12
    ),
    [2] = LAYOUT(
        KC_TAB , KC_7,   KC_8,    KC_9,    KC_MINS,                       KC_PGUP,KC_HOME, KC_UP, KC_END, KC_PGDN,
        KC_LCTL, KC_4,   KC_5,    KC_6,    LSFT(KC_SCLN),                  LSFT(KC_9),KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT,
        KC_LSFT, KC_1,   KC_2,    KC_3,    LSFT(KC_MINS),                  KC_BTN3, KC_BTN1,KC_BTN2, ______, KC_RSFT,
        KC_ESC, LALT_T(KC_0), ALT_T(KC_DOT), KC_LCTL, KC_ENT, KC_BSPC, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        RGB_TOG, AML_TO,  AML_I50, AML_D50, _______,                       _______,  _______, SSNP_HOR, SSNP_VRT, SSNP_FRE,
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, SCRL_DVI,                       _______,  _______, ________, _______, _______,
        RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, SCRL_DVD,                      CPI_D1K,  CPI_D100, CPI_I100, CPI_I1K,  KBC_SAVE,
        QK_BOOT, KBC_RST, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT
    ),
};

// レイヤー状態が変わったら自動でスクロールモードを切り替え
layer_state_t layer_state_set_user(layer_state_t state) {
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