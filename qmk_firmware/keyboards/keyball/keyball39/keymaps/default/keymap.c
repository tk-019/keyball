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
//
// 1. まずは「生の判定用コンボ配列」を並べる
//
const uint16_t PROGMEM combo_jk[]      = { KC_J,    KC_K,    COMBO_END };  // btn1
const uint16_t PROGMEM combo_kl[]      = { KC_K,    KC_L,    COMBO_END };  // btn2
const uint16_t PROGMEM combo_jl[]      = { KC_J,    KC_L,    COMBO_END };  // btn3
const uint16_t PROGMEM combo_qw[]      = { KC_Q,    KC_W,    COMBO_END };  // Tab
const uint16_t PROGMEM combo_sd[]      = { KC_S,    KC_D,    COMBO_END };  // Tab2
const uint16_t PROGMEM combo_io[]      = { KC_I,    KC_O,    COMBO_END };  // Backspace
const uint16_t PROGMEM combo_op[]      = { KC_O,    KC_P,    COMBO_END };  // -
const uint16_t PROGMEM combo_qj[]      = { KC_Q,    KC_J,    COMBO_END };  // '
const uint16_t PROGMEM combo_wj[]      = { KC_W,    KC_J,    COMBO_END };  // "
const uint16_t PROGMEM combo_ej[]      = { KC_E,    KC_J,    COMBO_END };  // !
const uint16_t PROGMEM combo_rj[]      = { KC_R,    KC_J,    COMBO_END };  // :
const uint16_t PROGMEM combo_tj[]      = { KC_T,    KC_J,    COMBO_END };  // ;
const uint16_t PROGMEM combo_yf[]      = { KC_Y,    KC_F,    COMBO_END };  // ¥
const uint16_t PROGMEM combo_uf[]      = { KC_U,    KC_F,    COMBO_END };  // +
const uint16_t PROGMEM combo_if[]      = { KC_I,    KC_F,    COMBO_END };  // =
const uint16_t PROGMEM combo_of[]      = { KC_O,    KC_F,    COMBO_END };  // |
const uint16_t PROGMEM combo_fp[]      = { KC_P,    KC_F,    COMBO_END };  // %
const uint16_t PROGMEM combo_aj[]      = { KC_A,    KC_J,    COMBO_END };  // @
const uint16_t PROGMEM combo_sj[]      = { KC_S,    KC_J,    COMBO_END };  // /
const uint16_t PROGMEM combo_dj[]      = { KC_D,    KC_J,    COMBO_END };  // $
const uint16_t PROGMEM combo_fj[]      = { KC_F,    KC_J,    COMBO_END };  // ?
const uint16_t PROGMEM combo_gj[]      = { KC_G,    KC_J,    COMBO_END };  // `(バッククォート)
const uint16_t PROGMEM combo_hf[]      = { KC_H,    KC_F,    COMBO_END };  // #
const uint16_t PROGMEM combo_kf[]      = { KC_K,    KC_F,    COMBO_END };  // [
const uint16_t PROGMEM combo_lf[]      = { KC_L,    KC_F,    COMBO_END };  // ]
const uint16_t PROGMEM combo_zj[]      = { KC_Z,    KC_J,    COMBO_END };  // ~
const uint16_t PROGMEM combo_xj[]      = { KC_X,    KC_J,    COMBO_END };  // *
const uint16_t PROGMEM combo_cj[]      = { KC_C,    KC_J,    COMBO_END };  // ^
const uint16_t PROGMEM combo_bj[]      = { KC_B,    KC_J,    COMBO_END };  // \  （Int1）
const uint16_t PROGMEM combo_nf[]      = { KC_N,    KC_F,    COMBO_END };  // &
const uint16_t PROGMEM combo_mf[]      = { KC_M,    KC_F,    COMBO_END };  // -
const uint16_t PROGMEM combo_zx[]      = { KC_Z,    KC_X,    COMBO_END };  // Z+X→ Shift+Z
const uint16_t PROGMEM combo_commF[]   = { KC_COMM, KC_F,    COMBO_END };  // (
const uint16_t PROGMEM combo_dotF[]    = { KC_DOT,  KC_F,    COMBO_END };  // )

//
// 2. 「コンボの数」を列挙型で定義する
//
enum combo_index {
    C_JK,      // combo_jk (J+K → BTN1)
    C_KL,      // combo_kl (K+L → BTN2)
    C_JL,      // combo_jl (J+L → BTN3)
    C_QW,      // combo_qw (Q+W → Tab)
    C_SD,      // combo_sd (S+D → Tab2)
    C_IO,      // combo_io (I+O → Backspace)
    C_OP,      // combo_op (O+P → -)
    C_QJ,      // combo_qj (Q+J → '  (Shift+7))
    C_WJ,      // combo_wj (W+J → "  (Shift+2))
    C_EJ,      // combo_ej (E+J → !  (Shift+1))
    C_RJ,      // combo_rj (R+J → :  (単体 QUOT))
    C_TJ,      // combo_tj (T+J → ;  (単体 SCLN))
    C_YF,      // combo_yf (Y+F → ¥  (INT3))
    C_UF,      // combo_uf (U+F → +  (Shift+SCLN))
    C_IF,      // combo_if (I+F → =  (Shift+MINS))
    C_OF,      // combo_of (O+F → |  (Shift+INT3))
    C_FP,      // combo_fp (F+P → %  (Shift+5))
    C_AJ,      // combo_aj (A+J → @  (単体 LBRC))
    C_SJ,      // combo_sj (S+J → /  (単体 SLSH))
    C_DJ,      // combo_dj (D+J → $  (Shift+4))
    C_FJ,      // combo_fj (F+J → ?  (Shift+SLSH))
    C_GJ,      // combo_gj (G+J → `  (Shift+LBRC))
    C_HF,      // combo_hf (H+F → #  (Shift+3))
    C_KF,      // combo_kf (K+F → [  (単体 RBRC))
    C_LF,      // combo_lf (L+F → ]  (単体 BSLS))
    C_ZJ,      // combo_zj (Z+J → ~  (Shift+EQL))
    C_XJ,      // combo_xj (X+J → *  (Shift+QUOT))
    C_CJ,      // combo_cj (C+J → ^  (単体 EQL))
    C_BJ,      // combo_bj (B+J → \  (Int1))
    C_NF,      // combo_nf (N+F → &  (Shift+6))
    C_MF,      // combo_mf (M+F → -  (単体 MINS))
    C_ZX,      // combo_zx (Z+X → Shift+Z)
    C_COMMF,   // combo_commF (COMMA+F → (  (Shift+8))
    C_DOTF,    // combo_dotF  (DOT+F   → )  (Shift+9))
    C_NUM      // コンボ数のダミー
};

//
// 3. 「発火判定だけ」を行う key_combos[] を列挙型に合わせて作成する
//
const combo_t key_combos[C_NUM] = {
    [C_JK]     = COMBO( combo_jk,    NO_SEND ),
    [C_KL]     = COMBO( combo_kl,    NO_SEND ),
    [C_JL]     = COMBO( combo_jl,    NO_SEND ),
    [C_QW]     = COMBO( combo_qw,    NO_SEND ),
    [C_SD]     = COMBO( combo_sd,    NO_SEND ),
    [C_IO]     = COMBO( combo_io,    NO_SEND ),
    [C_OP]     = COMBO( combo_op,    NO_SEND ),
    [C_QJ]     = COMBO( combo_qj,    NO_SEND ),
    [C_WJ]     = COMBO( combo_wj,    NO_SEND ),
    [C_EJ]     = COMBO( combo_ej,    NO_SEND ),
    [C_RJ]     = COMBO( combo_rj,    NO_SEND ),
    [C_TJ]     = COMBO( combo_tj,    NO_SEND ),
    [C_YF]     = COMBO( combo_yf,    NO_SEND ),
    [C_UF]     = COMBO( combo_uf,    NO_SEND ),
    [C_IF]     = COMBO( combo_if,    NO_SEND ),
    [C_OF]     = COMBO( combo_of,    NO_SEND ),
    [C_FP]     = COMBO( combo_fp,    NO_SEND ),
    [C_AJ]     = COMBO( combo_aj,    NO_SEND ),
    [C_SJ]     = COMBO( combo_sj,    NO_SEND ),
    [C_DJ]     = COMBO( combo_dj,    NO_SEND ),
    [C_FJ]     = COMBO( combo_fj,    NO_SEND ),
    [C_GJ]     = COMBO( combo_gj,    NO_SEND ),
    [C_HF]     = COMBO( combo_hf,    NO_SEND ),
    [C_KF]     = COMBO( combo_kf,    NO_SEND ),
    [C_LF]     = COMBO( combo_lf,    NO_SEND ),
    [C_ZJ]     = COMBO( combo_zj,    NO_SEND ),
    [C_XJ]     = COMBO( combo_xj,    NO_SEND ),
    [C_CJ]     = COMBO( combo_cj,    NO_SEND ),
    [C_BJ]     = COMBO( combo_bj,    NO_SEND ),
    [C_NF]     = COMBO( combo_nf,    NO_SEND ),
    [C_MF]     = COMBO( combo_mf,    NO_SEND ),
    [C_ZX]     = COMBO( combo_zx,    NO_SEND ),
    [C_COMMF]  = COMBO( combo_commF, NO_SEND ),
    [C_DOTF]   = COMBO( combo_dotF,  NO_SEND ),
};

//
// 4. 「コンボインデックスに対応して、何を送出するか」を定義するテーブル
//    （keycode と 修飾ビットをまとめておく）
//
typedef struct {
    uint16_t keycode;  // tap_code16() で送るキーコード
    uint8_t  mods;     // 修飾ビット (MOD_BIT(…) で指定)
} combo_output_t;

static const combo_output_t combo_output_table[C_NUM] = {
    [C_JK]    = { KC_BTN1,    0                    }, // J+K → 左ボタン
    [C_KL]    = { KC_BTN2,    0                    }, // K+L → 中ボタン
    [C_JL]    = { KC_BTN3,    0                    }, // J+L → 右ボタン
    [C_QW]    = { KC_TAB,     0                    }, // Q+W → Tab
    [C_SD]    = { KC_TAB,     0                    }, // S+D → Tab2
    [C_IO]    = { KC_BSPC,    0                    }, // I+O → Backspace
    [C_OP]    = { KC_MINS,    0                    }, // O+P → -
    [C_QJ]    = { KC_7,       MOD_BIT(KC_LSFT)     }, // Q+J → Shift+7 (' in JIS)
    [C_WJ]    = { KC_2,       MOD_BIT(KC_LSFT)     }, // W+J → Shift+2 (" in JIS)
    [C_EJ]    = { KC_1,       MOD_BIT(KC_LSFT)     }, // E+J → Shift+1 (! in JIS)
    [C_RJ]    = { KC_QUOT,    0                    }, // R+J → QUOT (: in JIS)
    [C_TJ]    = { KC_SCLN,    0                    }, // T+J → SCLN (; in JIS)
    [C_YF]    = { KC_INT3,    0                    }, // Y+F → INT3 (¥)
    [C_UF]    = { KC_SCLN,    MOD_BIT(KC_LSFT)     }, // U+F → Shift+SCLN (+ in JIS)
    [C_IF]    = { KC_MINS,    MOD_BIT(KC_LSFT)     }, // I+F → Shift+MINS (= in JIS)
    [C_OF]    = { KC_INT3,    MOD_BIT(KC_LSFT)     }, // O+F → Shift+INT3 (| in JIS)
    [C_FP]    = { KC_5,       MOD_BIT(KC_LSFT)     }, // F+P → Shift+5 (% in JIS)
    [C_AJ]    = { KC_LBRC,    0                    }, // A+J → LBRC (@ in JIS)
    [C_SJ]    = { KC_SLSH,    0                    }, // S+J → SLSH (/)
    [C_DJ]    = { KC_4,       MOD_BIT(KC_LSFT)     }, // D+J → Shift+4 ($ in JIS)
    [C_FJ]    = { KC_SLSH,    MOD_BIT(KC_LSFT)     }, // F+J → Shift+SLSH (? in JIS)
    [C_GJ]    = { KC_LBRC,    MOD_BIT(KC_LSFT)     }, // G+J → Shift+LBRC (` in JIS)
    [C_HF]    = { KC_3,       MOD_BIT(KC_LSFT)     }, // H+F → Shift+3 (# in JIS)
    [C_KF]    = { KC_RBRC,    0                    }, // K+F → RBRC ([ in JIS)
    [C_LF]    = { KC_BSLS,    0                    }, // L+F → BSLS (] in JIS)
    [C_ZJ]    = { KC_EQL,     MOD_BIT(KC_LSFT)     }, // Z+J → Shift+EQL (~ in JIS)
    [C_XJ]    = { KC_QUOT,    MOD_BIT(KC_LSFT)     }, // X+J → Shift+QUOT (* in JIS)
    [C_CJ]    = { KC_EQL,     0                    }, // C+J → EQL (^ in JIS)
    [C_BJ]    = { KC_INT1,    0                    }, // B+J → INT1 (\ in JIS)
    [C_NF]    = { KC_6,       MOD_BIT(KC_LSFT)     }, // N+F → Shift+6 (& in JIS)
    [C_MF]    = { KC_MINS,    0                    }, // M+F → MINS (-)
    [C_ZX]    = { KC_Z,       MOD_BIT(KC_LSFT)     }, // Z+X → Shift+Z
    [C_COMMF] = { KC_8,       MOD_BIT(KC_LSFT)     }, // COMMA+F → Shift+8 ( ( )
    [C_DOTF]  = { KC_9,       MOD_BIT(KC_LSFT)     }, // DOT+F   → Shift+9 ( ) )
};

//
// 5. process_combo_event() をテーブル参照だけに書き換える
//
bool process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        // 放したタイミングでは何もしない
        return false;
    }
    // 送出すべきキーコード＋修飾ビットをテーブルから取り出す
    combo_output_t out = combo_output_table[combo_index];

    // 修飾ビットがあれば先に hold
    if (out.mods) {
        register_mods(out.mods);
    }
    // メインのキーをタップ送信
    tap_code16(out.keycode);
    // hold していた修飾を戻す
    if (out.mods) {
        unregister_mods(out.mods);
    }
    return false;
}

#endif  // COMBO_ENABLE