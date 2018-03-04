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
#include <thread>
#include <nyra/test/Test.h>
#include <nyra/win/native/Keyboard.h>

namespace nyra
{
namespace win
{
namespace native
{
void sendKeyPresses()
{
    Keyboard keyboard;
    keyboard.press(input::KEY_H);
    keyboard.press(input::KEY_E);
    keyboard.press(input::KEY_L);
    keyboard.press(input::KEY_L);
    keyboard.press(input::KEY_O);
    keyboard.press(input::KEY_SPACE);
    keyboard.press(input::KEY_W);
    keyboard.press(input::KEY_O);
    keyboard.press(input::KEY_R);
    keyboard.press(input::KEY_L);
    keyboard.press(input::KEY_D);
    keyboard.press(input::KEY_ENTER);
}

static std::string cinInput;

void enterInput()
{
    std::string hello;
    std::string world;
    std::cin >> hello >> world;
    cinInput = hello + " " + world;
}

TEST(Keyboard, Simulate)
{
    std::thread cin(enterInput);
    std::thread sim(sendKeyPresses);

    sim.join();
    cin.join();
    EXPECT_EQ("hello world", cinInput);
}
}
}
}

NYRA_TEST()
