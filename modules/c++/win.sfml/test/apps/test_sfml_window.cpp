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
#include <nyra/win.sfml/Window.h>
#include <nyra/test/Test.h>
#include <nyra/test/TestWindow.h>

namespace nyra
{
namespace win
{
namespace sfml
{
class TestSFMLWindow : public test::TestWindow<Window>
{
};

TEST_F(TestSFMLWindow, GetSet)
{
    EXPECT_EQ(testName(), expectedName);
    EXPECT_EQ(testSize(), expectedSize);
#ifndef NYRA_POSIX
    EXPECT_EQ(testPosition(), expectedPosition);
#else
    // SFML get position is wrong on Linux
    std::cout << "\nWARNING: SFML Window position is incorrect on Linux\n";
    std::cout << "Expected Position: " << expectedPosition << "\n";
    std::cout << "Actual Position: " << testPosition() << "\n\n";
#endif
}

TEST_F(TestSFMLWindow, Close)
{
    EXPECT_NE(testID(), previousID);
    EXPECT_TRUE(testClose());
}

TEST_F(TestSFMLWindow, Archive)
{
    Window window = testArchiveOpen();
    EXPECT_EQ(window.getName(), expectedName);
    EXPECT_EQ(window.getSize(), expectedSize);
#ifndef NYRA_POSIX
    EXPECT_EQ(testPosition(), expectedPosition);
#else
    // SFML get position is wrong on Linux
    std::cout << "\nWARNING: SFML Window position is incorrect on Linux\n";
    std::cout << "Expected Position: " << expectedPosition << "\n";
    std::cout << "Actual Position: " << testPosition() << "\n\n";
#endif

    EXPECT_FALSE(testArchiveClosed().isOpen());
}

TEST_F(TestSFMLWindow, Stdout)
{
#ifndef NYRA_POSIX
    EXPECT_EQ(testStdoutOpen(), expectedStdoutOpen);
#else
    const std::string actualStdout = testStdoutOpen();

    // SFML get position is wrong on Linux
    std::cout << "\nWARNING: SFML Window position is incorrect on Linux\n";
    std::cout << "\nExpected Stdout:\n" << expectedStdoutOpen << "\n";
    std::cout << "\nActual Stdout:\n" << actualStdout << "\n\n";

    EXPECT_EQ(testStdoutOpen().substr(0, 37), expectedStdoutOpen.substr(0, 37));
#endif
    EXPECT_EQ(testStdoutClosed(), expectedStdoutClosed);
}
}
}
}

NYRA_TEST()
