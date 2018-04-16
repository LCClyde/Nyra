/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/gui/qt/Gui.h>
#include <nyra/test/Test.h>
#include <nyra/test/Image.h>
#include <nyra/win/qt/Window.h>
#include <nyra/gui/qt/Button.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace gui
{
namespace qt
{
//! The QT Window will delete all of its children. This test ensures that
//  when the window goes out of scope, the GUI object is not double
//  deleted.
TEST(Gui, Close)
{
    win::qt::Window window("test_qt_gui",
                           math::Vector2U(256, 64),
                           math::Vector2I(256, 128));
    Gui myGui(window);

    const math::Vector2F size(200, 50);
    const math::Vector2F position(32, 7);
    const std::string msg = "BUTTON";
    Button* button = new Button(size, position, msg);
    myGui["widget"] = button;

    for (size_t ii = 0; ii < 10; ++ii)
    {
        window.update();
    }

    window.close();
}
}
}
}

NYRA_TEST()
