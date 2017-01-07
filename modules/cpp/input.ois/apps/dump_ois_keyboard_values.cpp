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
#include <nyra/win/ogre/Window.h>
#include <nyra/input/ois/Keyboard.h>
#include <nyra/core/Time.h>

using namespace nyra;

int main()
{
    // TODO: This does not work with a QT window. I only want to use it
    //       with Ogre windows at the moment so I am not tracking it down
    //       right now.
    win::ogre::Window window("Test Keyboard / Ogre Window",
                             math::Vector2U(1280, 720),
                             math::Vector2I(450, 50));

    input::ois::Keyboard keyboard(window);

    while (window.isOpen())
    {
        window.update();
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
