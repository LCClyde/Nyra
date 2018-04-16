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
#include <nyra/gui/qt/Spinner.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace gui
{
namespace qt
{
TEST(Spinner, Render)
{
    // The position is offset so the window doesn't go into the title bar.
    win::qt::Window window("test_qt_spinner_int",
                           math::Vector2U(256, 256),
                           math::Vector2I(256, 128));

    Gui gui(window);

    const math::Vector2F size(150, 50);
    const math::Vector2F pos1(20, 10);
    const math::Vector2F pos2(20, 100);

    double val1 = 100.0;
    double val2 = -5.25;
    Spinner* spinint = new Spinner(
            size, pos1, Spinner::INTEGER, val1, -25, 150, 5);
    gui["widget_int"] = spinint;

    Spinner* spindouble = new Spinner(
            size, pos2, Spinner::DOUBLE, val2, -10.0, 3.5, 0.25);
    gui["widget_double"] = spindouble;

    // We need to make sure the Window is fully updated and has time to
    // animate if need be.
    for (size_t ii = 0; ii < 10; ++ii)
    {
        window.update();
        core::sleep(100);
    }

    EXPECT_TRUE(test::compareImage(window.getPixels(),
                                   "test_qt_spinner.png"));
    EXPECT_EQ(spinint->getValue(), val1);
    EXPECT_EQ(spinint->getPosition(), pos1);
    EXPECT_EQ(spinint->getSize(), size);
    spinint->setValue(-10);
    EXPECT_EQ(spinint->getValue(), -10);
    spinint->setValue(-100);
    EXPECT_EQ(spinint->getValue(), -25);
    spinint->setValue(200);
    EXPECT_EQ(spinint->getValue(), 150);

    EXPECT_EQ(spindouble->getValue(), val2);
    EXPECT_EQ(spindouble->getPosition(), pos2);
    EXPECT_EQ(spindouble->getSize(), size);
    spindouble->setValue(1.45);
    EXPECT_EQ(spindouble->getValue(), 1.45);
    spindouble->setValue(-100);
    EXPECT_EQ(spindouble->getValue(), -10);
    spindouble->setValue(200);
    EXPECT_EQ(spindouble->getValue(), 3.5);
}
}
}
}

NYRA_TEST()
