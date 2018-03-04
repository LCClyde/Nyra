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
#include <nyra/mem/Buffer2D.h>

namespace nyra
{
namespace mem
{
TEST(Buffer2D, Buffer2D)
{
    math::Vector2U size(128, 256);
    mem::Buffer2D<size_t> buf1(size);
    EXPECT_EQ(size, buf1.getSize());

    for (size_t ii = 0; ii < size.product(); ++ii)
    {
        EXPECT_EQ(static_cast<size_t>(0), buf1(ii));
    }

    for (size_t ii = 0; ii < size.product(); ++ii)
    {
        buf1(ii) = ii;
        EXPECT_EQ(ii, buf1(ii));
    }

    for (size_t x = 0; x < size.x; ++x)
    {
        for (size_t y = 0; y < size.y; ++y)
        {
            EXPECT_EQ(y * size.x + x, buf1(x, y));
        }
    }

    for (size_t x = 0; x < size.x; ++x)
    {
        for (size_t y = 0; y < size.y; ++y)
        {
            buf1(x, y) = x * y;
            EXPECT_EQ(x * y, buf1(x, y));
        }
    }

    mem::Buffer2D<size_t> buf2(
            {{1, 2, 3, 4, 5, 6},
             {7, 8, 9, 10, 11, 12},
             {13, 14, 15, 16, 17, 18}});

    size.x = 6;
    size.y = 3;
    EXPECT_EQ(size, buf2.getSize());
    EXPECT_EQ(size.y, buf2.getNumRows());
    EXPECT_EQ(size.x, buf2.getNumCols());

    for (size_t ii = 0; ii < size.product(); ++ii)
    {
        EXPECT_EQ(ii + 1, buf2(ii));
    }

    for (size_t x = 0; x < size.x; ++x)
    {
        for (size_t y = 0; y < size.y; ++y)
        {
            EXPECT_EQ(y * size.x + x + 1, buf2(x, y));
        }
    }
}
}
}

NYRA_TEST()
