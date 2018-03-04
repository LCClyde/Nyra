/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_INPUT_SFML_KEYBOARD_H__
#define __NYRA_INPUT_SFML_KEYBOARD_H__

#include <nyra/win/Window.h>
#include <nyra/input/Keyboard.h>

namespace nyra
{
namespace input
{
namespace sfml
{
/*
 *  \class Keyboard
 *  \brief Class to represent user input from the Keyboard. The SFML Keyboard
 *         does not support as many keys as the OIS keyboard, but it does
 *         not require a focused window to function.
 */
class Keyboard : public input::Keyboard
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the Keyboard.
     */
    Keyboard() = default;

    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the Keyboard. The window
     *         is not used for SFML. It is only needed to satisfy the interface
     *
     *  \param window An SFML window.
     */
    Keyboard(const win::Window& window);
    /*
     *  \func update
     *  \brief Updates the button values for the keyboard.
     */
    void update() override;

private:
    std::bitset<input::KEY_MAX> mKeyBits;
};
}
}
}

#endif
