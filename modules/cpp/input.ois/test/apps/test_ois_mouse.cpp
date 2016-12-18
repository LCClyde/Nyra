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
#include <nyra/test/Test.h>
#include <nyra/input/ois/Mouse.h>
#include <nyra/win/ogre/Window.h>

namespace nyra
{
namespace input
{
namespace ois
{
TEST(Mouse, Update)
{
    // Because all the values are user input, there is nothing to test here
    // except that the functions do not throw / segfault.
    std::cout << "=================================================\n";
    std::cout << "WARNING: test_ois_mouse does not test any values.\n";
    std::cout << "WARNING: Run dump_ois_mouse_values to manually\n";
    std::cout << "WARNING: test actual values.\n";
    std::cout << "=================================================\n";
    win::ogre::Window window("Test Mouse",
                             math::Vector2U(1280, 720),
                             math::Vector2I(450, 200));
    input::ois::Mouse mouse(window);

    window.update();
    mouse.update();
    mouse.getPosition();
    mouse.getDelta();
    mouse.getScroll();
    mouse.getButtonDown(input::Mouse::MOUSE_LEFT);
    mouse.getButtonPressed(input::Mouse::MOUSE_LEFT);
    mouse.getButtonReleased(input::Mouse::MOUSE_LEFT);
    mouse.getButtonDown(input::Mouse::MOUSE_RIGHT);
    mouse.getButtonPressed(input::Mouse::MOUSE_RIGHT);
    mouse.getButtonReleased(input::Mouse::MOUSE_RIGHT);
    mouse.getButtonDown(input::Mouse::MOUSE_MIDDLE);
    mouse.getButtonPressed(input::Mouse::MOUSE_MIDDLE);
    mouse.getButtonReleased(input::Mouse::MOUSE_MIDDLE);
}
}
}
}

NYRA_TEST()
