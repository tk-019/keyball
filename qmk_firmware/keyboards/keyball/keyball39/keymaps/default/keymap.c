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

// 1. 生の「キー２つだけの組み合わせ」配列を定義（PROGMEM や const は外す）
//    → COMBO_ACTION() を使うためには key_combos 全体を RAM に置く必要があるため
//    → ただし「combo_jk[] など」は PROGMEM で構わない
//
static const uint16_t PROGMEM combo_jk[]    = { KC_J,    KC_K,    COMBO_END };  // BTN1
static const uint16_t PROGMEM combo_kl[]    = { KC_K,    KC_L,    COMBO_END };  // BTN2
static const uint16_t PROGMEM combo_jl[]    = { KC_J,    KC_L,    COMBO_END };  // BTN3
static const uint16_t PROGMEM combo_qw[]    = { KC_Q,    KC_W,    COMBO_END };  // TAB
static const uint16_t PROGMEM combo_sd[]    = { KC_S,    KC_D,    COMBO_END };  // TAB2
static const uint16_t PROGMEM combo_io[]    = { KC_I,    KC_O,    COMBO_END };  // BACKSPACE
static const uint16_t PROGMEM combo_op[]    = { KC_O,    KC_P,    COMBO_END };  // “-”
static const uint16_t PROGMEM combo_qj[]    = { KC_Q,    KC_J,    COMBO_END };  // “‘” (Shift+7)
static const uint16_t PROGMEM combo_wj[]    = { KC_W,    KC_J,    COMBO_END };  // “"” (Shift+2)
static const uint16_t PROGMEM combo_ej[]    = { KC_E,    KC_J,    COMBO_END };  // “!” (Shift+1)
static const uint16_t PROGMEM combo_rj[]    = { KC_R,    KC_J,    COMBO_END };  // “:” (QUOT)
static const uint16_t PROGMEM combo_tj[]    = { KC_T,    KC_J,    COMBO_END };  // “;” (SCLN)
static const uint16_t PROGMEM combo_yf[]    = { KC_Y,    KC_F,    COMBO_END };  // “¥” (INT3)
static const uint16_t PROGMEM combo_uf[]    = { KC_U,    KC_F,    COMBO_END };  // “+” (Shift+SCLN)
static const uint16_t PROGMEM combo_if[]    = { KC_I,    KC_F,    COMBO_END };  // “=” (Shift+MINS)
static const uint16_t PROGMEM combo_of[]    = { KC_O,    KC_F,    COMBO_END };  // “|” (Shift+INT3)
static const uint16_t PROGMEM combo_fp[]    = { KC_P,    KC_F,    COMBO_END };  // “%” (Shift+5)
static const uint16_t PROGMEM combo_aj[]    = { KC_A,    KC_J,    COMBO_END };  // “@” (LBRC)
static const uint16_t PROGMEM combo_sj[]    = { KC_S,    KC_J,    COMBO_END };  // “/” (SLSH)
static const uint16_t PROGMEM combo_dj[]    = { KC_D,    KC_J,    COMBO_END };  // “$” (Shift+4)
static const uint16_t PROGMEM combo_fj[]    = { KC_F,    KC_J,    COMBO_END };  // “?” (Shift+SLSH)
static const uint16_t PROGMEM combo_gj[]    = { KC_G,    KC_J,    COMBO_END };  // “`” (Shift+LBRC)
static const uint16_t PROGMEM combo_hf[]    = { KC_H,    KC_F,    COMBO_END };  // “#” (Shift+3)
static const uint16_t PROGMEM combo_kf[]    = { KC_K,    KC_F,    COMBO_END };  // “[” (RBRC)
static const uint16_t PROGMEM combo_lf[]    = { KC_L,    KC_F,    COMBO_END };  // “]” (BSLS)
static const uint16_t PROGMEM combo_zj[]    = { KC_Z,    KC_J,    COMBO_END };  // “~” (Shift+EQL)
static const uint16_t PROGMEM combo_xj[]    = { KC_X,    KC_J,    COMBO_END };  // “*” (Shift+QUOT)
static const uint16_t PROGMEM combo_cj[]    = { KC_C,    KC_J,    COMBO_END };  // “^” (EQL)
static const uint16_t PROGMEM combo_bj[]    = { KC_B,    KC_J,    COMBO_END };  // “\” (INT1)
static const uint16_t PROGMEM combo_nf[]    = { KC_N,    KC_F,    COMBO_END };  // “&” (Shift+6)
static const uint16_t PROGMEM combo_mf[]    = { KC_M,    KC_F,    COMBO_END };  // “-” (MINS)
static const uint16_t PROGMEM combo_zx[]    = { KC_Z,    KC_X,    COMBO_END };  // Shift+Z
static const uint16_t PROGMEM combo_commF[] = { KC_COMM, KC_F,    COMBO_END };  // “(” (Shift+8)
static const uint16_t PROGMEM combo_dotF[]  = { KC_DOT,  KC_F,    COMBO_END };  // “)” (Shift+9)


//
// 2. インデックスを列挙型で定義
//
enum combo_index {
    C_JK,      // combo_jk
    C_KL,      // combo_kl
    C_JL,      // combo_jl
    C_QW,      // combo_qw
    C_SD,      // combo_sd
    C_IO,      // combo_io
    C_OP,      // combo_op
    C_QJ,      // combo_qj
    C_WJ,      // combo_wj
    C_EJ,      // combo_ej
    C_RJ,      // combo_rj
    C_TJ,      // combo_tj
    C_YF,      // combo_yf
    C_UF,      // combo_uf
    C_IF,      // combo_if
    C_OF,      // combo_of
    C_FP,      // combo_fp
    C_AJ,      // combo_aj
    C_SJ,      // combo_sj
    C_DJ,      // combo_dj
    C_FJ,      // combo_fj
    C_GJ,      // combo_gj
    C_HF,      // combo_hf
    C_KF,      // combo_kf
    C_LF,      // combo_lf
    C_ZJ,      // combo_zj
    C_XJ,      // combo_xj
    C_CJ,      // combo_cj
    C_BJ,      // combo_bj
    C_NF,      // combo_nf
    C_MF,      // combo_mf
    C_ZX,      // combo_zx
    C_COMMF,   // combo_commF
    C_DOTF,    // combo_dotF
    C_NUM      // 合計数（必ず最後）
};

//
// 3.「発火判定だけ」を行う key_combos[] を列挙型に合わせて作成
//    → PROGMEM や const は外し、「RAM 上」に置くこと
//
combo_t key_combos[C_NUM] = {
    [C_JK]     = COMBO( combo_jk,    COMBO_ACTION(C_JK) ),
    [C_KL]     = COMBO( combo_kl,    COMBO_ACTION(C_KL) ),
    [C_JL]     = COMBO( combo_jl,    COMBO_ACTION(C_JL) ),
    [C_QW]     = COMBO( combo_qw,    COMBO_ACTION(C_QW) ),
    [C_SD]     = COMBO( combo_sd,    COMBO_ACTION(C_SD) ),
    [C_IO]     = COMBO( combo_io,    COMBO_ACTION(C_IO) ),
    [C_OP]     = COMBO( combo_op,    COMBO_ACTION(C_OP) ),
    [C_QJ]     = COMBO( combo_qj,    COMBO_ACTION(C_QJ) ),
    [C_WJ]     = COMBO( combo_wj,    COMBO_ACTION(C_WJ) ),
    [C_EJ]     = COMBO( combo_ej,    COMBO_ACTION(C_EJ) ),
    [C_RJ]     = COMBO( combo_rj,    COMBO_ACTION(C_RJ) ),
    [C_TJ]     = COMBO( combo_tj,    COMBO_ACTION(C_TJ) ),
    [C_YF]     = COMBO( combo_yf,    COMBO_ACTION(C_YF) ),
    [C_UF]     = COMBO( combo_uf,    COMBO_ACTION(C_UF) ),
    [C_IF]     = COMBO( combo_if,    COMBO_ACTION(C_IF) ),
    [C_OF]     = COMBO( combo_of,    COMBO_ACTION(C_OF) ),
    [C_FP]     = COMBO( combo_fp,    COMBO_ACTION(C_FP) ),
    [C_AJ]     = COMBO( combo_aj,    COMBO_ACTION(C_AJ) ),
    [C_SJ]     = COMBO( combo_sj,    COMBO_ACTION(C_SJ) ),
    [C_DJ]     = COMBO( combo_dj,    COMBO_ACTION(C_DJ) ),
    [C_FJ]     = COMBO( combo_fj,    COMBO_ACTION(C_FJ) ),
    [C_GJ]     = COMBO( combo_gj,    COMBO_ACTION(C_GJ) ),
    [C_HF]     = COMBO( combo_hf,    COMBO_ACTION(C_HF) ),
    [C_KF]     = COMBO( combo_kf,    COMBO_ACTION(C_KF) ),
    [C_LF]     = COMBO( combo_lf,    COMBO_ACTION(C_LF) ),
    [C_ZJ]     = COMBO( combo_zj,    COMBO_ACTION(C_ZJ) ),
    [C_XJ]     = COMBO( combo_xj,    COMBO_ACTION(C_XJ) ),
    [C_CJ]     = COMBO( combo_cj,    COMBO_ACTION(C_CJ) ),
    [C_BJ]     = COMBO( combo_bj,    COMBO_ACTION(C_BJ) ),
    [C_NF]     = COMBO( combo_nf,    COMBO_ACTION(C_NF) ),
    [C_MF]     = COMBO( combo_mf,    COMBO_ACTION(C_MF) ),
    [C_ZX]     = COMBO( combo_zx,    COMBO_ACTION(C_ZX) ),
    [C_COMMF]  = COMBO( combo_commF, COMBO_ACTION(C_COMMF) ),
    [C_DOTF]   = COMBO( combo_dotF,  COMBO_ACTION(C_DOTF) ),
};


//
// 4. 「コンボインデックス → 送出すべきキーコード＋修飾ビット」をテーブル化
//
typedef struct {
    uint16_t keycode;  // tap_code16() で送信するメインのキーコード
    uint8_t  mods;     // 先に登録すべき修飾ビット (MOD_BIT(…) で指定)
} combo_output_t;

static const combo_output_t combo_output_table[C_NUM] = {
    [C_JK]    = { KC_BTN1,    0                    }, // J+K → 左ボタン
    [C_KL]    = { KC_BTN2,    0                    }, // K+L → 中ボタン
    [C_JL]    = { KC_BTN3,    0                    }, // J+L → 右ボタン
    [C_QW]    = { KC_TAB,     0                    }, // Q+W → Tab
    [C_SD]    = { KC_TAB,     0                    }, // S+D → Tab2
    [C_IO]    = { KC_BSPC,    0                    }, // I+O → Backspace
    [C_OP]    = { KC_MINS,    0                    }, // O+P → –
    [C_QJ]    = { KC_7,       MOD_BIT(KC_LSFT)     }, // Q+J → Shift+7 (’)
    [C_WJ]    = { KC_2,       MOD_BIT(KC_LSFT)     }, // W+J → Shift+2 (”)
    [C_EJ]    = { KC_1,       MOD_BIT(KC_LSFT)     }, // E+J → Shift+1 (!)
    [C_RJ]    = { KC_QUOT,    0                    }, // R+J → QUOT (:)
    [C_TJ]    = { KC_SCLN,    0                    }, // T+J → SCLN (;)
    [C_YF]    = { KC_INT3,    0                    }, // Y+F → INT3 (¥)
    [C_UF]    = { KC_SCLN,    MOD_BIT(KC_LSFT)     }, // U+F → Shift+SCLN (+)
    [C_IF]    = { KC_MINS,    MOD_BIT(KC_LSFT)     }, // I+F → Shift+MINS (=)
    [C_OF]    = { KC_INT3,    MOD_BIT(KC_LSFT)     }, // O+F → Shift+INT3 (|)
    [C_FP]    = { KC_5,       MOD_BIT(KC_LSFT)     }, // F+P → Shift+5 (%)
    [C_AJ]    = { KC_LBRC,    0                    }, // A+J → LBRC (@)
    [C_SJ]    = { KC_SLSH,    0                    }, // S+J → SLSH (/)
    [C_DJ]    = { KC_4,       MOD_BIT(KC_LSFT)     }, // D+J → Shift+4 ($)
    [C_FJ]    = { KC_SLSH,    MOD_BIT(KC_LSFT)     }, // F+J → Shift+SLSH (?)
    [C_GJ]    = { KC_LBRC,    MOD_BIT(KC_LSFT)     }, // G+J → Shift+LBRC (`)
    [C_HF]    = { KC_3,       MOD_BIT(KC_LSFT)     }, // H+F → Shift+3 (#)
    [C_KF]    = { KC_RBRC,    0                    }, // K+F → RBRC ([)
    [C_LF]    = { KC_BSLS,    0                    }, // L+F → BSLS (])
    [C_ZJ]    = { KC_EQL,     MOD_BIT(KC_LSFT)     }, // Z+J → Shift+EQL (~)
    [C_XJ]    = { KC_QUOT,    MOD_BIT(KC_LSFT)     }, // X+J → Shift+QUOT (*)
    [C_CJ]    = { KC_EQL,     0                    }, // C+J → EQL (^)
    [C_BJ]    = { KC_INT1,    0                    }, // B+J → INT1 (\)
    [C_NF]    = { KC_6,       MOD_BIT(KC_LSFT)     }, // N+F → Shift+6 (&)
    [C_MF]    = { KC_MINS,    0                    }, // M+F → MINS (–)
    [C_ZX]    = { KC_Z,       MOD_BIT(KC_LSFT)     }, // Z+X → Shift+Z
    [C_COMMF] = { KC_8,       MOD_BIT(KC_LSFT)     }, // COMMA+F → Shift+8 (()
    [C_DOTF]  = { KC_9,       MOD_BIT(KC_LSFT)     }, // DOT+F   → Shift+9 ())
};


//
// 5. process_combo_event() を QMK のシグネチャ に合わせて定義
//
void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        // 離したタイミングでは何もしない
        return;
    }
    // 送出すべきキー＋修飾をテーブルから取り出す
    combo_output_t out = combo_output_table[combo_index];

    // もし修飾ビットが指定されていれば、先に hold
    if (out.mods) {
        register_mods(out.mods);
    }
    // メインのキーを tap
    tap_code16(out.keycode);
    // hold していた修飾を戻す
    if (out.mods) {
        unregister_mods(out.mods);
    }
}

#endif  // COMBO_ENABLE
