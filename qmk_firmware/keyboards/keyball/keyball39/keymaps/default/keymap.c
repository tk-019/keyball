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


#ifdef COMBO_ENABLE

// 1) “K + J で Shift+Win+←” 用のコンボ定義
const uint16_t PROGMEM combo_kj_swl[] = { KC_K, KC_J, COMBO_END };

// 既存のコンボ定義もそのまま並べてください
const uint16_t PROGMEM combo_jk[]    = { KC_J, KC_K, COMBO_END };    // btn1
const uint16_t PROGMEM combo_kl[]    = { KC_K, KC_L, COMBO_END };    // btn2
const uint16_t PROGMEM combo_jl[]    = { KC_J, KC_L, COMBO_END };    // btn3
const uint16_t PROGMEM combo_qw[]    = { KC_Q, KC_W, COMBO_END };    // tab
const uint16_t PROGMEM combo_sd[]    = { KC_S, KC_D, COMBO_END };    // tab2
const uint16_t PROGMEM combo_io[]    = { KC_I, KC_O, COMBO_END };    // bs
const uint16_t PROGMEM combo_op[]    = { KC_O, KC_P, COMBO_END };    // ー／-
const uint16_t PROGMEM combo_qj[]    = { KC_Q, KC_J, COMBO_END };    // '
const uint16_t PROGMEM combo_wj[]    = { KC_W, KC_J, COMBO_END };    // "
const uint16_t PROGMEM combo_ej[]    = { KC_E, KC_J, COMBO_END };    // !
const uint16_t PROGMEM combo_rj[]    = { KC_R, KC_J, COMBO_END };    // :
const uint16_t PROGMEM combo_tj[]    = { KC_T, KC_J, COMBO_END };    // ;
const uint16_t PROGMEM combo_yf[]    = { KC_Y, KC_F, COMBO_END };    // ¥
const uint16_t PROGMEM combo_uf[]    = { KC_U, KC_F, COMBO_END };    // +
const uint16_t PROGMEM combo_if[]    = { KC_I, KC_F, COMBO_END };    // =
const uint16_t PROGMEM combo_of[]    = { KC_O, KC_F, COMBO_END };    // |
const uint16_t PROGMEM combo_fp[]    = { KC_P, KC_F, COMBO_END };    // %
const uint16_t PROGMEM combo_aj[]    = { KC_A, KC_J, COMBO_END };    // @
const uint16_t PROGMEM combo_sj[]    = { KC_S, KC_J, COMBO_END };    // /
const uint16_t PROGMEM combo_dj[]    = { KC_D, KC_J, COMBO_END };    // $
const uint16_t PROGMEM combo_fj[]    = { KC_F, KC_J, COMBO_END };    // ?
const uint16_t PROGMEM combo_gj[]    = { KC_G, KC_J, COMBO_END };    // `
const uint16_t PROGMEM combo_hf[]    = { KC_H, KC_F, COMBO_END };    // #
const uint16_t PROGMEM combo_kf[]    = { KC_K, KC_F, COMBO_END };    // [
const uint16_t PROGMEM combo_lf[]    = { KC_L, KC_F, COMBO_END };    // ]
const uint16_t PROGMEM combo_zj[]    = { KC_Z, KC_J, COMBO_END };    // ~
const uint16_t PROGMEM combo_xj[]    = { KC_X, KC_J, COMBO_END };    // *
const uint16_t PROGMEM combo_cj[]    = { KC_C, KC_J, COMBO_END };    // ^
const uint16_t PROGMEM combo_bj[]    = { KC_B, KC_J, COMBO_END };    // \
const uint16_t PROGMEM combo_nf[]    = { KC_N, KC_F, COMBO_END };    // &
const uint16_t PROGMEM combo_mf[]    = { KC_M, KC_F, COMBO_END };    // -
const uint16_t PROGMEM combo_zx[]    = { KC_Z, KC_X, COMBO_END };    // Shift+Z（例）
const uint16_t PROGMEM combo_commF[] = { KC_COMM, KC_F, COMBO_END }; // (
const uint16_t PROGMEM combo_dotF[]  = { KC_DOT, KC_F, COMBO_END };  // )

// 2) コンボのインデックスを列挙(enum)に追加
enum combo_index {
    C_JK,
    C_KL,
    C_JL,
    C_QW,
    C_SD,
    C_IO,
    C_OP,
    C_QJ,
    C_WJ,
    C_EJ,
    C_RJ,
    C_TJ,
    C_YF,
    C_UF,
    C_IF,
    C_OF,
    C_FP,
    C_AJ,
    C_SJ,
    C_DJ,
    C_FJ,
    C_GJ,
    C_HF,
    C_KF,
    C_LF,
    C_ZJ,
    C_XJ,
    C_CJ,
    C_BJ,
    C_NF,
    C_MF,
    C_ZX,
    C_COMM_F,
    C_DOT_F,
    // ────── ここに新規追加 ──────
    C_KJ_SWL,
    COMBO_COUNT
};

// 3) key_combos[] に COMBO_ACTION() で登録
combo_t key_combos[COMBO_COUNT] = {
    [C_JK]      = COMBO(combo_jk,    COMBO_ACTION(C_JK)),
    [C_KL]      = COMBO(combo_kl,    COMBO_ACTION(C_KL)),
    [C_JL]      = COMBO(combo_jl,    COMBO_ACTION(C_JL)),
    [C_QW]      = COMBO(combo_qw,    COMBO_ACTION(C_QW)),
    [C_SD]      = COMBO(combo_sd,    COMBO_ACTION(C_SD)),
    [C_IO]      = COMBO(combo_io,    COMBO_ACTION(C_IO)),
    [C_OP]      = COMBO(combo_op,    COMBO_ACTION(C_OP)),
    [C_QJ]      = COMBO(combo_qj,    COMBO_ACTION(C_QJ)),
    [C_WJ]      = COMBO(combo_wj,    COMBO_ACTION(C_WJ)),
    [C_EJ]      = COMBO(combo_ej,    COMBO_ACTION(C_EJ)),
    [C_RJ]      = COMBO(combo_rj,    COMBO_ACTION(C_RJ)),
    [C_TJ]      = COMBO(combo_tj,    COMBO_ACTION(C_TJ)),
    [C_YF]      = COMBO(combo_yf,    COMBO_ACTION(C_YF)),
    [C_UF]      = COMBO(combo_uf,    COMBO_ACTION(C_UF)),
    [C_IF]      = COMBO(combo_if,    COMBO_ACTION(C_IF)),
    [C_OF]      = COMBO(combo_of,    COMBO_ACTION(C_OF)),
    [C_FP]      = COMBO(combo_fp,    COMBO_ACTION(C_FP)),
    [C_AJ]      = COMBO(combo_aj,    COMBO_ACTION(C_AJ)),
    [C_SJ]      = COMBO(combo_sj,    COMBO_ACTION(C_SJ)),
    [C_DJ]      = COMBO(combo_dj,    COMBO_ACTION(C_DJ)),
    [C_FJ]      = COMBO(combo_fj,    COMBO_ACTION(C_FJ)),
    [C_GJ]      = COMBO(combo_gj,    COMBO_ACTION(C_GJ)),
    [C_HF]      = COMBO(combo_hf,    COMBO_ACTION(C_HF)),
    [C_KF]      = COMBO(combo_kf,    COMBO_ACTION(C_KF)),
    [C_LF]      = COMBO(combo_lf,    COMBO_ACTION(C_LF)),
    [C_ZJ]      = COMBO(combo_zj,    COMBO_ACTION(C_ZJ)),
    [C_XJ]      = COMBO(combo_xj,    COMBO_ACTION(C_XJ)),
    [C_CJ]      = COMBO(combo_cj,    COMBO_ACTION(C_CJ)),
    [C_BJ]      = COMBO(combo_bj,    COMBO_ACTION(C_BJ)),
    [C_NF]      = COMBO(combo_nf,    COMBO_ACTION(C_NF)),
    [C_MF]      = COMBO(combo_mf,    COMBO_ACTION(C_MF)),
    [C_ZX]      = COMBO(combo_zx,    COMBO_ACTION(C_ZX)),
    [C_COMM_F]  = COMBO(combo_commF, COMBO_ACTION(C_COMM_F)),
    [C_DOT_F]   = COMBO(combo_dotF,  COMBO_ACTION(C_DOT_F)),
    // ────── 新規追加 ──────
    [C_KJ_SWL]  = COMBO(combo_kj_swl, COMBO_ACTION(C_KJ_SWL)),
};

bool process_combo_event(uint16_t combo_index, bool pressed) {
    // “離したとき” は無視
    if (!pressed) return true;

    switch (combo_index) {
        // ──── 既存のコンボ動作 ────
        case C_JK:
            tap_code(KC_BTN1);
            break;
        case C_KL:
            tap_code(KC_BTN2);
            break;
        case C_JL:
            tap_code(KC_BTN3);
            break;
        case C_QW:
            tap_code(KC_TAB);
            break;
        case C_SD:
            tap_code(KC_TAB);
            break;
        case C_IO:
            tap_code(KC_BSPC);
            break;
        case C_OP:
            tap_code(KC_MINS);
            break;
        case C_QJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_7);
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_WJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_2);
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_EJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_1);
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_RJ:
            tap_code(KC_QUOT);
            break;
        case C_TJ:
            tap_code(KC_SCLN);
            break;
        case C_YF:
            tap_code(KC_INT3);  // “¥”
            break;
        case C_UF:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_SCLN);  // “＋”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_IF:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_MINS);  // “＝”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_OF:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_INT3);  // “｜”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_FP:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_5);     // “％”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_AJ:
            tap_code(KC_LBRC);   // “@” JIS では左角括弧キー
            break;
        case C_SJ:
            tap_code(KC_SLSH);   // “/”
            break;
        case C_DJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_4);     // “$”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_FJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_SLSH);  // “?”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_GJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_LBRC);  // “`” JIS では Shift+[ でバククォート
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_HF:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_3);     // “#”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_KF:
            tap_code(KC_RBRC);   // “[” JIS では右角括弧キー
            break;
        case C_LF:
            tap_code(KC_BSLS);   // “]” JIS ではバックスラッシュキー
            break;
        case C_ZJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_EQL);   // “~”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_XJ:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_QUOT);  // “*”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_CJ:
            tap_code(KC_EQL);    // “^”
            break;
        case C_BJ:
            tap_code(KC_INT1);   // “\” JIS では無変換キー
            break;
        case C_NF:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_6);      // “&”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_MF:
            tap_code(KC_MINS);   // “-”
            break;
        case C_ZX:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_Z);      // “Shift+Z”（用途例）
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_COMM_F:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_8);      // “(”
            unregister_mods(MOD_MASK_SHIFT);
            break;
        case C_DOT_F:
            register_mods(MOD_MASK_SHIFT);
            tap_code(KC_9);      // “)”
            unregister_mods(MOD_MASK_SHIFT);
            break;

        // ──── 新規: “Shift+Win+←” を送る ────
        case C_KJ_SWL:
            register_mods(MOD_MASK_SHIFT | MOD_MASK_GUI);
            tap_code(KC_LEFT);
            unregister_mods(MOD_MASK_SHIFT | MOD_MASK_GUI);
            break;

        default:
            break;
    }
    return true;
}

#endif // COMBO_ENABLE