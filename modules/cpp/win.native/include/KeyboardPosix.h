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
#ifndef __NYRA_WIN_NATIVE_KEYBOARD_POSIX_H__
#define __NYRA_WIN_NATIVE_KEYBOARD_POSIX_H__

#include <nyra/input/Keyboard.h>
#include <nyra/win/native/PosixGlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace win
{
namespace native
{
/*
 *  \class KeyboardPosix
 *  \brief Handles simulating input for a Posix keyboard.
 */
class KeyboardPosix :
        private mem::GlobalDependency<PosixGlobalHandler>
{
public:
    /*
     *  \func setKeyDown
     *  \brief Sets the key to the down state
     *
     *  \param code The keycode
     */
    void setKeyDown(input::KeyCode code);

    /*
     *  \func setKeyReleased
     *  \brief Sets the key to the up state
     *
     *  \param code The keycode
     */
    void setKeyReleased(input::KeyCode code);

    /*
     *  \func press
     *  \brief Simulates a key press
     *
     *  \param code The keycode
     */
    void press(input::KeyCode code);

private:
    void setKey(input::KeyCode code, bool set);
};
}
}
}

#endif
