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
#include <nyra/input/sfml/Keyboard.h>
#include <nyra/core/Time.h>

using namespace nyra;

// TODO: This prints the console from both the user and the application
//       At the same time. This should be fixed, but does demonstrate
//       functionality as is.
int main()
{
    try
    {
        input::sfml::Keyboard keyboard;

        while (true)
        {
            keyboard.update();

            for (size_t ii = 0; ii < input::KEY_MAX; ++ii)
            {
                if (keyboard.getButtonPressed(ii))
                {
                    std::cout << input::keyCodeToString(
                            static_cast<input::KeyCode>(ii)) << "\n";
                }
            }

            // Fake 30 FPS, just to slow down the updates.
            core::sleep(33);
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
    }

    return 0;
}
