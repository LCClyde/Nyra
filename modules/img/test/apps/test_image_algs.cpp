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
#include <nyra/test/Image.h>
#include <nyra/img/Algs.h>
#include <nyra/core/Path.h>
#include <nyra/math/Conversions.h>

namespace nyra
{
namespace img
{
Image getInput()
{
    return core::read<Image>(core::path::join(
            core::DATA_PATH, "textures/lenna.png"));
}

//===========================================================================//
TEST(Algs, Blur)
{
    const Image input = getInput();
    const Image output = gaussianBlur(input, 20);
    EXPECT_TRUE(test::compareImage(output, "test_gaussian_blur.png"));
}

//===========================================================================//
TEST(Algs, EdgeDetect)
{
    const Image input = getInput();
    const Image output = edgeDetect(input, 75.0);
    EXPECT_TRUE(test::compareImage(output, "test_edge_detect.png"));
}

//===========================================================================//
TEST(Algs, Invert)
{
    const Image input = getInput();
    const Image output = invert(input);
    EXPECT_TRUE(test::compareImage(output, "test_invert.png"));
}

//===========================================================================//
TEST(Algs, Threshold)
{
    const Image input = getInput();
    const Image output = threshold(input, 128);
    EXPECT_TRUE(test::compareImage(output, "test_threshold.png"));
}

//===========================================================================//
TEST(Algs, Dilate)
{
    const Image input = getInput();
    const Image output = dilate(input, 5);
    EXPECT_TRUE(test::compareImage(output, "test_dilate.png"));
}

//===========================================================================//
TEST(Algs, Resize)
{
    const Image input = getInput();
    const Image output = resize(input, math::Vector2U(100, 200));
    EXPECT_TRUE(test::compareImage(output, "test_img_resize.png"));
}

//===========================================================================//
TEST(Algs, Crop)
{
    const Image input = getInput();
    const math::Vector2U offset(210, 170);
    const math::Vector2U extents(190, 230);
    const Image output = crop(input, offset, extents);
    EXPECT_TRUE(test::compareImage(output, "test_img_crop.png"));
}

//===========================================================================//
class WarpX
{
public:
    double operator()(double x, double y) const
    {
        return std::sin(math::degreesToRadians(x)) * 10;
    }
};

class WarpY
{
public:
    double operator()(double x, double y) const
    {
        return std::sin(math::degreesToRadians(y)) * 10;
    }
};
TEST(Algs, Warp)
{
    const Image input = getInput();
    const WarpX warpX;
    const WarpY warpY;
    const Image output = warp(input, warpX, warpY);
    EXPECT_TRUE(test::compareImage(output, "test_warp.png"));
}
}
}

NYRA_TEST()
