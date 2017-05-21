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
#include <iostream>
#include <vector>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <nyra/win/native/KeyboardPosix.h>

namespace
{
//===========================================================================//
static std::vector<KeyCode> KEY_CODES;
static const uint8_t UNKNOWN_CODE = 204;

//===========================================================================//
void setKeyPosixKeyCodes(Display* display)
{
    if (KEY_CODES.empty())
    {
        KEY_CODES.resize(nyra::input::KEY_MAX);

        // Auto populate as many keys as possible
        for (size_t code = nyra::input::KEY_1;
             code < nyra::input::KEY_MAX;
             ++code)
        {
            const std::string key = nyra::input::keyCodeToString(
                    static_cast<nyra::input::KeyCode>(code));
            KEY_CODES[static_cast<size_t>(code)] =
                    XKeysymToKeycode(display, XStringToKeysym(key.c_str()));
        }

        // Add in some missing stuff
        KEY_CODES[static_cast<size_t>(nyra::input::KEY_SPACE)] =
                XKeysymToKeycode(display, XStringToKeysym("space"));
        KEY_CODES[static_cast<size_t>(nyra::input::KEY_ENTER)] =
                XKeysymToKeycode(display, XK_Return);
    }
}
}

namespace nyra
{
namespace win
{
namespace native
{
//===========================================================================//
void KeyboardPosix::setKeyDown(input::KeyCode code)
{
    setKey(code, true);
}

//===========================================================================//
void KeyboardPosix::setKeyReleased(input::KeyCode code)
{
    setKey(code, false);
}

//===========================================================================//
void KeyboardPosix::press(input::KeyCode code)
{
    setKeyReleased(code);
    setKeyDown(code);
    setKeyReleased(code);
}

//===========================================================================//
void KeyboardPosix::setKey(input::KeyCode code, bool set)
{
    Display* display = getGlobalInstance().get();
    setKeyPosixKeyCodes(display);
    KeyCode modcode = KEY_CODES[static_cast<size_t>(code)];

    if (modcode == UNKNOWN_CODE)
    {
        throw std::runtime_error("KeyCode: " +
                input::keyCodeToString(code) + " is not implemented");
    }

    XTestFakeKeyEvent(display, modcode, set, 0);
}
}
}
}
