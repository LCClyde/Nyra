/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <nyra/win/qt/Window.h>
#include <nyra/test/Test.h>
#include <nyra/test/TestWindow.h>

namespace nyra
{
namespace win
{
namespace qt
{
class TestQtWindow : public test::TestWindow<Window>
{
};

TEST_F(TestQtWindow, GetSet)
{
    EXPECT_EQ(testName(), expectedName);
    EXPECT_EQ(testSize(), expectedSize);
    EXPECT_EQ(testPosition(), expectedPosition);
}

TEST_F(TestQtWindow, Close)
{
    // TODO: It looks like Qt will use the same window ID even though
    //       I destroy the object. This needs to be verified on other
    //       platforms.
    EXPECT_EQ(testID(), previousID);
    EXPECT_TRUE(testClose());
}

TEST_F(TestQtWindow, Archive)
{
    Window window = testArchiveOpen();
    EXPECT_EQ(window.getName(), expectedName);
    EXPECT_EQ(window.getSize(), expectedSize);
    EXPECT_EQ(testPosition(), expectedPosition);

    EXPECT_FALSE(testArchiveClosed().isOpen());
}

TEST_F(TestQtWindow, Stdout)
{
    EXPECT_EQ(testStdoutOpen(), expectedStdoutOpen);
    EXPECT_EQ(testStdoutClosed(), expectedStdoutClosed);
}
}
}
}

NYRA_TEST()
