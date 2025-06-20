/*
This is the c configuration file for the keymap

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

#pragma once

#define KEYBALL_MODEL 39
#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1
#define COMBO_HOLD_TERM  120    // コンボのホールド昇格時間
#define TAPPING_TERM 200        // デフォルト200 → 短くするとタップミスが多くなるので注意
#define COMBO_TERM  30          // デフォルト50ms

/* 毎レポートで NKRO を強制オンにする */
#define FORCE_NKRO
