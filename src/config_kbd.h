/*
 * config_kbd.h - This header file provides compilation-time configuration
 *                  for the keyboard_api and <keyboard>_adapter
 *
 * Copyright (C) 2025 Dygma Lab S.L. www.dygma.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __CONFIG_KBD_H_
#define __CONFIG_KBD_H_

/*
 * Kaleidoscope Adapter Default Keymap specification (mandatory)
 */

enum
{
    KEYMAP_ID_QWERTY = 0,
    KEYMAP_ID_NUMPAD,
};

#define KALEIDOSCOPE_ADAPTER_KEYMAP_DEFAULT                                                                 __NL__ \
    [KEYMAP_ID_QWERTY] = KEYMAP_STACKED                                                                     __NL__ \
    (                                                                                                       __NL__ \
        /* Left Side */                                                                                     __NL__ \
        Key_Escape, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6,                                               __NL__ \
        Key_Tab, Key_Q, Key_W, Key_E, Key_R, Key_T, Consumer_VolumeIncrement,                               __NL__ \
        Key_CapsLock, Key_A, Key_S, Key_D, Key_F, Key_G, Consumer_VolumeDecrement,                          __NL__ \
        Key_Backslash, Key_Z, Key_X, Key_C, Key_V, Key_B,                                                   __NL__ \
        Key_LeftControl, Key_LeftGui, Key_Backspace, Key_Delete,                                            __NL__ \
        Key_LeftShift, Key_LeftAlt, Key_Enter, Key_Space,                                                   __NL__ \
                                                                                                            __NL__ \
        /* Right Side */                                                                                    __NL__ \
        Key_7, Key_8, Key_9, Key_0, Key_Minus, Key_Equals, Key_Backspace,                                   __NL__ \
        Key_Y, Key_U, Key_I, Key_O, Key_P, Key_LeftBracket, Key_RightBracket,                               __NL__ \
        Key_H, Key_J, Key_K, Key_L, Key_Semicolon, Key_Quote, Key_RightShift,                               __NL__ \
        Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_RightShift,                                     __NL__ \
        Key_LEDEffectNext, Key_Home, Key_UpArrow, Key_End,                                                  __NL__ \
        Key_RightArrow, Key_DownArrow, Key_LeftArrow, Key_Enter                                             __NL__ \
    ),                                                                                                      __NL__ \
                                                                                                            __NL__ \
    [KEYMAP_ID_NUMPAD] = KEYMAP_STACKED                                                                     __NL__ \
    (                                                                                                       __NL__ \
        /* Left Side */                                                                                     __NL__ \
        Key_Escape, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6,                                         __NL__ \
        Key_Tab, Key_NoKey, Key_UpArrow, Key_NoKey, Key_NoKey, Key_NoKey, Key_NoKey,                        __NL__ \
        Key_CapsLock, Key_LeftArrow, Key_DownArrow, Key_RightArrow, Key_NoKey, Key_NoKey, Key_NoKey,        __NL__ \
        Key_LeftShift, Key_Backslash, Key_NoKey, Key_NoKey, Key_NoKey, Key_NoKey,                           __NL__ \
        Key_LeftControl, Key_LeftGui, Key_LeftAlt, Key_Space,                                               __NL__ \
        Key_Space, Key_Backspace, Key_Enter, Key_Delete,                                                    __NL__ \
                                                                                                            __NL__ \
        /* Right Side */                                                                                    __NL__ \
        Key_F7, Key_F8, Key_F9, Key_F10, Key_F11, Key_F12, Key_Backspace,                                   __NL__ \
        Key_KeypadSubtract, Key_7, Key_8, Key_9, Key_KeypadDivide, Key_NoKey, Key_Enter,                    __NL__ \
        Key_KeypadAdd, Key_4, Key_5, Key_6, Key_KeypadMultiply, Key_NoKey, Key_Backslash,                   __NL__ \
        Key_KeypadDot, Key_1, Key_2, Key_3, Key_UpArrow, Key_RightShift,                                    __NL__ \
        Key_0, Key_Space, Key_LeftArrow, Key_DownArrow,                                                     __NL__ \
        Key_RightArrow, Key_RightControl, Key_Delete, MoveToLayer(KEYMAP_ID_QWERTY)                         __NL__ \
    )

#endif /* __CONFIG_KBD_H_ */
