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
#include <nyra/test/Test.h>
#include <nyra/map/LandMask.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace map
{
TEST(LandMask, Image)
{
    // Using a reduced size to speed up testing
    const math::Vector2U size(256, 256);
    for (double ii = 0.0; ii <= 1.0; ii += 0.25)
    {
        LandMask mask(ii, 0);
        const img::Image image = mask.getImage(size);

        size_t numBlack = 0;
        for (size_t pix = 0; pix < size.product(); ++pix)
        {
            if (image(pix) == img::Color::BLACK)
            {
                ++numBlack;
            }
        }

        EXPECT_NEAR(ii, static_cast<double>(numBlack) / size.product(), 0.05);
    }
}
}
}

NYRA_TEST()
