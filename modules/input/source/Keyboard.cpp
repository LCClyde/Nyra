/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <boost/bimap.hpp>
#include <nyra/input/Keyboard.h>

namespace
{
typedef boost::bimap<nyra::input::KeyCode, std::string> KeyMapT;
typedef KeyMapT::value_type KeyMapValue;
static KeyMapT keyMap;

const KeyMapT& getKeyMap()
{
    // If the key map is empty we need to fill it out before first use.
    if (keyMap.empty())
    {
        keyMap.insert(KeyMapValue(nyra::input::KEY_1, "1"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_2, "2"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_3, "3"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_4, "4"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_5, "5"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_6, "6"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_7, "7"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_8, "8"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_9, "9"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_0, "0"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_Q, "Q"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_W, "W"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_E, "E"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_R, "R"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_T, "T"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_Y, "Y"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_U, "U"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_I, "I"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_O, "O"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_P, "P"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_A, "A"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_S, "S"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_D, "D"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F, "F"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_G, "G"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_H, "H"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_J, "J"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_K, "K"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_L, "L"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_Z, "Z"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_X, "X"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_C, "C"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_V, "V"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_B, "B"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_N, "N"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_M, "M"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_SPACE, "Space"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_ENTER, "Enter"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_ESCAPE, "Escape"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_BACKSPACE, "Backspace"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_TAB, "Tab"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_MINUS, "-"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_EQUALS, "="));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT_BRACKET, "["));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT_BRACKET, "]"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_SEMICOLON, ";"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_APOSTROPHE, "'"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_TILDE, "~"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_BACKSLASH, "\\"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_COMMA, ","));
        keyMap.insert(KeyMapValue(nyra::input::KEY_PERIOD, "."));
        keyMap.insert(KeyMapValue(nyra::input::KEY_FORWARD_SLASH, "/"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT_SHIFT, "Right Shift"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT_SHIFT, "Left Shift"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT_CONTROL, "Right Ctrl"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT_CONTROL, "Left Ctrl"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT_ALT, "Right Alt"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT_ALT, "Left Alt"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT_SYSTEM, "Right Sys"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT_SYSTEM, "Left Sys"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_INSERT, "Insert"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_DELETE, "Delete"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_CAPS_LOCK, "Caps Lock"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUM_LOCK, "Num Lock"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_SCROLL_LOCK, "Scroll Lock"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F1, "F1"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F2, "F2"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F3, "F3"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F4, "F4"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F5, "F5"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F6, "F6"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F7, "F7"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F8, "F8"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F9, "F9"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F10, "F10"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F11, "F11"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F12, "F12"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F13, "F13"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F14, "F14"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_F15, "F15"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_1, "Numpad 1"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_2, "Numpad 2"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_3, "Numpad 3"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_4, "Numpad 4"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_5, "Numpad 5"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_6, "Numpad 6"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_7, "Numpad 7"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_8, "Numpad 8"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_9, "Numpad 9"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_0, "Numpad 0"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_SUBTRACT, "Numpad -"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_ADD, "Numpad +"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_MULTIPLY, "Numpad *"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_DECIMAL, "Numpad ."));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_ENTER, "Numpad Enter"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_COMMA, "Numpad ,"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_DIVIDE, "Numpad /"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_NUMPAD_EQUALS, "Numpad ="));
        keyMap.insert(KeyMapValue(nyra::input::KEY_PAUSE, "Pause"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_HOME, "Home"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_END, "End"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_PAGE_UP, "Page Up"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_PAGE_DOWN, "Page Down"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_UP, "Up"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_LEFT, "Left"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_RIGHT, "Right"));
        keyMap.insert(KeyMapValue(nyra::input::KEY_DOWN, "Down"));
    }
    return keyMap;
}
}

namespace nyra
{
namespace input
{
//===========================================================================//
std::string keyCodeToString(KeyCode code)
{
    const auto results = getKeyMap().left.find(code);
    if (results == getKeyMap().left.end())
    {
        throw std::runtime_error("Invalid KeyCode: " +
                                 std::to_string(static_cast<uint32_t>(code)));
    }
    return results->second;
}

//===========================================================================//
KeyCode stringToKeyCode(const std::string& code)
{
    const auto results = getKeyMap().right.find(code);
    if (results == getKeyMap().right.end())
    {
        throw std::runtime_error("Invalid KeyCode: " + code);
    }
    return results->second;
}
}
}
