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
#ifndef __NYRA_POKE_SIMULATOR_H__
#define __NYRA_POKE_SIMULATOR_H__

#include <string>
#include <memory>
#include <nyra/win/native/Keyboard.h>
#include <nyra/win/native/Desktop.h>
#include <nyra/process/BackgroundSubprocess.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace poke
{
class Simulator
{
public:
    Simulator(const std::string& binaryPathname,
              const std::string& gamePathname);

    void pressStart() const;

    void pressA() const;

    void pressB() const;

    void saveAll() const;

    img::Image screenshot() const
    {
        return screenshot(math::Vector2U(0, 0), mScreenSize);
    }

    img::Image screenshot(const math::Vector2U& offset,
                          const math::Vector2U& size) const;

private:
    std::unique_ptr<process::BackgroundSubprocess> mProc;
    win::native::Keyboard mKeyboard;
    win::native::Desktop mDesktop;
    math::Vector2U mScreenSize;
};
}
}

#endif
