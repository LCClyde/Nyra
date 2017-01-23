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
#include <nyra/win/qt/Window.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace gui
{
namespace qt
{
TEST(Event, Call)
{
    // The position is offset so the window doesn't go into the title bar.
    win::qt::Window window("test_qt_label",
                           math::Vector2U(256, 64),
                           math::Vector2I(256, 128));

    Gui gui(window);
    Label* label = new Label("Hello World");
    gui["label"] = label;

    // We need to make sure the Window is fully updated and has time to
    // animate if need be.
    for (size_t ii = 0; ii < 10; ++ii)
    {
        window.update();
        core::sleep(100);
    }

    // TODO: This works on Linux, it will probably be different on
    //       other platforms.
    img::Image truth = core::read<img::Image>(core::path::join(
            core::DATA_PATH, "textures/test_qt_label.png"));
    EXPECT_EQ(truth, window.getPixels());

    EXPECT_NE(math::Vector2F(0.0f, 0.0f), label->getSize());
    EXPECT_NE(math::Vector2F(256.0f, 64.0f), label->getSize());
    EXPECT_EQ(math::Vector2F(0.0f, 0.0f), label->getPosition());
}
}
}
}

NYRA_TEST()
