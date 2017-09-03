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
#include <nyra/game/InputValues.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace game
{
InputValue::InputValue(const std::vector<std::string>& keys) :
    mIsPressed(false),
    mIsDown(false),
    mIsReleased(false)
{
    for (std::string key : keys)
    {
        if (core::str::startsWith(key, "key_"))
        {
            const std::string code = key.substr(4, std::string::npos);
            mKeyCodes.push_back(input::stringToKeyCode(code));
        }
        else if (core::str::startsWith(key, "mouse_"))
        {
            const std::string code = key.substr(6, std::string::npos);
            mMouseCodes.push_back(core::str::toType<size_t>(code));
        }
    }
}

void InputValue::update(const input::Mouse& mouse,
                        const input::Keyboard& keyboard)
{
    mIsPressed = false;
    mIsDown = false;
    mIsReleased = false;

    for (auto code : mKeyCodes)
    {
        if (keyboard.getButtonPressed(code))
        {
            mIsPressed = true;
        }
        if (keyboard.getButtonDown(code))
        {
            mIsDown = true;
        }
        if (keyboard.getButtonReleased(code))
        {
            mIsReleased = true;
        }
    }

    for (auto code : mMouseCodes)
    {
        if (mouse.getButtonPressed(code))
        {
            mIsPressed = true;
        }
        if (mouse.getButtonDown(code))
        {
            mIsDown = true;
        }
        if (mouse.getButtonReleased(code))
        {
            mIsReleased = true;
        }
    }
}
}
}

