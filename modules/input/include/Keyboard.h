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
#ifndef __NYRA_INPUT_KEYBOARD_H__
#define __NYRA_INPUT_KEYBOARD_H__

#include <string>
#include <nyra/input/Buttons.h>

namespace nyra
{
namespace input
{
/*
 *  \type KeyCode
 *  \brief Key codes to represent the available keys as indexes into
 *         the button array.
 */
enum KeyCode
{
    KEY_1 = 0,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_SPACE,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_MINUS,
    KEY_EQUALS,
    KEY_LEFT_BRACKET,
    KEY_RIGHT_BRACKET,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_TILDE,
    KEY_BACKSLASH,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_FORWARD_SLASH,
    KEY_RIGHT_SHIFT,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_LEFT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_LEFT_ALT,
    KEY_RIGHT_SYSTEM,
    KEY_LEFT_SYSTEM,
    KEY_INSERT,
    KEY_DELETE,
    KEY_CAPS_LOCK,
    KEY_NUM_LOCK,
    KEY_SCROLL_LOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_NUMPAD_1,
    KEY_NUMPAD_2,
    KEY_NUMPAD_3,
    KEY_NUMPAD_4,
    KEY_NUMPAD_5,
    KEY_NUMPAD_6,
    KEY_NUMPAD_7,
    KEY_NUMPAD_8,
    KEY_NUMPAD_9,
    KEY_NUMPAD_0,
    KEY_NUMPAD_SUBTRACT,
    KEY_NUMPAD_ADD,
    KEY_NUMPAD_MULTIPLY,
    KEY_NUMPAD_DECIMAL,
    KEY_NUMPAD_ENTER,
    KEY_NUMPAD_COMMA,
    KEY_NUMPAD_DIVIDE,
    KEY_NUMPAD_EQUALS,
    KEY_PAUSE,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_MAX
};

/*
 *  \func keyCodeToString
 *  \brief Converts a KeyCode into a unique string.
 *
 *  \param code The KeyCode to convert
 *  \return The string representation.
 */
std::string keyCodeToString(KeyCode code);

/*
 *  \func stringToKeyCode
 *  \brief Converts a string into a KeyCode
 *
 *  \param code The string representation of the code.
 *  \return The KeyCode value.
 */
KeyCode stringToKeyCode(const std::string& code);

/*
 *  \class Keyboard
 *  \brief Class to represent user input from the Keyboard.
 */
class Keyboard : public Buttons<KEY_MAX>
{
public:
    /*
     *  \func update
     *  \brief Updates the button values for the keyboard.
     */
    virtual void update() = 0;
};
}
}

#endif
