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
#include <nyra/gui/qt/GroupBox.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace gui
{
namespace qt
{
TEST(GroupBox, Render)
{
    // The position is offset so the window doesn't go into the title bar.
    win::qt::Window window("test_qt_panel",
                           math::Vector2U(800, 600),
                           math::Vector2I(256, 128));

    Gui gui(window);

    const math::Vector2F size(512, 256);
    const math::Vector2F position(100, 100);
    const std::string msg = "Test Panel!";
    GroupBox* edit = new GroupBox(size, position, msg);
    gui["widget"] = edit;

    // We need to make sure the Window is fully updated and has time to
    // animate if need be.
    for (size_t ii = 0; ii < 10; ++ii)
    {
        window.update();
        core::sleep(100);
    }

    EXPECT_TRUE(test::compareImage(window.getPixels(),
                                   "test_qt_group_box.png"));
    EXPECT_EQ(edit->getText(), msg);
    EXPECT_EQ(edit->getPosition(), position);
    EXPECT_EQ(edit->getSize(), size);
}
}
}
}

NYRA_TEST()
