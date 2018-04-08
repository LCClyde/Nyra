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
#include <nyra/gui/qt/Gui.h>
#include <nyra/test/Test.h>
#include <nyra/test/Image.h>
#include <nyra/win/qt/Window.h>
#include <nyra/gui/qt/Button.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace
{
void pressed()
{
    std::cout << "Pressed\n";
}
}

namespace nyra
{
namespace gui
{
namespace qt
{
TEST(EditBox, Render)
{
    // The position is offset so the window doesn't go into the title bar.
    win::qt::Window window("test_qt_edit_box",
                           math::Vector2U(256, 64),
                           math::Vector2I(256, 128));

    Gui gui(window);

    const math::Vector2F size(200, 50);
    const math::Vector2F position(32, 7);
    const std::string msg = "BUTTON";
    Button* button = new Button(size, position, msg);

    // The activation is not tested here, but you can update the for loop
    // to repeat to test it.
    button->activated = pressed;
    gui["widget"] = button;

    // We need to make sure the Window is fully updated and has time to
    // animate if need be.
    for (size_t ii = 0; ii < 10; ++ii)
    {
        window.update();
        core::sleep(100);
    }

    EXPECT_TRUE(test::compareImage(window.getPixels(),
                                   "test_qt_button.png"));
    EXPECT_EQ(button->getText(), msg);
    EXPECT_EQ(button->getPosition(), position);
    EXPECT_EQ(button->getSize(), size);
}
}
}
}

NYRA_TEST()
