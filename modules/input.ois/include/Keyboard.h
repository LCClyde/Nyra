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
#ifndef __NYRA_INPUT_OIS_KEYBOARD_H__
#define __NYRA_INPUT_OIS_KEYBOARD_H__

#include <OIS/OISKeyboard.h>
#include <nyra/input/Keyboard.h>
#include <nyra/win/Window.h>
#include <nyra/input/ois/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace input
{
namespace ois
{
/*
 *  \class Keyboard
 *  \brief Class to represent user input from the Keyboard.
 */
class Keyboard : public input::Keyboard,
        private mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the Keyboard.
     */
    Keyboard(const win::Window& window);

    /*
     *  \func Destructor
     *  \brief Destroys the OIS device object.
     */
    ~Keyboard();

    /*
     *  \func update
     *  \brief Updates the button values for the keyboard.
     */
    void update() override;

private:
    std::bitset<input::KEY_MAX> mKeyBits;
    const size_t mWinID;
    OIS::Keyboard& mKeyboard;
};
}
}
}

#endif
