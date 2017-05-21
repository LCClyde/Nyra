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
#include <nyra/test/Test.h>
#include <nyra/win/native/Desktop.h>

namespace nyra
{
namespace win
{
namespace native
{
TEST(Desktop, Size)
{
    Desktop desktop;
    const math::Vector2U size = desktop.getSize();

    // Just make sure we get non zero
    EXPECT_NE(static_cast<size_t>(0), size.x());
    EXPECT_NE(static_cast<size_t>(0), size.y());
}

TEST(Desktop, Screenshot)
{
    Desktop desktop;
    const math::Vector2U size = desktop.getSize();
    const img::Image screenshot = desktop.getPixels();

    EXPECT_EQ(size, screenshot.getSize());

    size_t numZero = 0;
    for (size_t ii = 0; ii < size.product(); ++ii)
    {
        const img::Color& color = screenshot(ii);
        if (color.r == 0 && color.g == 0 && color.b == 0)
        {
            ++numZero;
        }
    }

    // Make sure we got some content back
    EXPECT_NE(size.product(), numZero);
}

TEST(Desktop, ParitalScreenshot)
{
    Desktop desktop;
    const math::Vector2I offset(200, 100);
    const math::Vector2U size(256, 128);
    const img::Image screenshot = desktop.getPixels(offset, size);

    EXPECT_EQ(size, screenshot.getSize());

    size_t numZero = 0;
    for (size_t ii = 0; ii < size.product(); ++ii)
    {
        const img::Color& color = screenshot(ii);
        if (color.r == 0 && color.g == 0 && color.b == 0)
        {
            ++numZero;
        }
    }

    // Make sure we got some content back
    EXPECT_NE(size.product(), numZero);
}
}
}
}

NYRA_TEST()
