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
#include <nyra/poke/Simulator.h>
#include <nyra/process/Hijack.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace poke
{
//===========================================================================//
Simulator::Simulator(const std::string& binaryPathname,
                     const std::string& gamePathname) :
    mScreenSize(240, 160)
{
    std::cout << "Started VBA\n";
    core::sleep(500);

    // Load the game
    // Spam start
    img::Color expectedPixel(72, 72, 104);
    std::cout << "Loading save game\n";

    bool gameLaunched = false;

    while (!gameLaunched)
    {
        mProc.reset(new process::BackgroundSubprocess(
                binaryPathname, {gamePathname, "-1"}));

        // Try at most 20 times
        for (size_t ii = 0; ii < 20; ++ii)
        {
            pressStart();

            if (screenshot()(80, 220) == expectedPixel)
            {
                pressA();
                std::cout << "Save game is loaded\n";
                gameLaunched = true;
                break;
            }
            core::sleep(1000);
        }
    }

    core::sleep(1000);
    pressA();
    std::cout << "Skipped cutscene\n";
}

//===========================================================================//
void Simulator::pressStart() const
{
    mKeyboard.press(input::KEY_ENTER);
}

//===========================================================================//
void Simulator::pressA() const
{
    mKeyboard.press(input::KEY_Z);
}

//===========================================================================//
void Simulator::pressB() const
{
    mKeyboard.press(input::KEY_X);
}

//===========================================================================//
void Simulator::saveAll() const
{
    mKeyboard.setKeyDown(input::KEY_LEFT_SHIFT);
    core::sleep(200);
    mKeyboard.press(input::KEY_F1);
    core::sleep(200);
    mKeyboard.press(input::KEY_F2);
    core::sleep(200);
    mKeyboard.press(input::KEY_F3);
    core::sleep(200);
    mKeyboard.press(input::KEY_F4);
    core::sleep(200);
    mKeyboard.press(input::KEY_F5);
    core::sleep(200);
    mKeyboard.press(input::KEY_F6);
    core::sleep(200);
    mKeyboard.setKeyReleased(input::KEY_LEFT_SHIFT);
}

//===========================================================================//
img::Image Simulator::screenshot(const math::Vector2U& offset,
                                 const math::Vector2U& size) const
{
    return mDesktop.getPixels(
            math::Vector2I(95 + offset.x(),
                           103 + offset.y()),
            size);
}
}
}
