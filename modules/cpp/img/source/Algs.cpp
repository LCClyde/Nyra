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
#include <nyra/img/Algs.h>
#include <opencv2/opencv.hpp>

namespace nyra
{
namespace img
{
//===========================================================================//
Image gaussianBlur(const Image& input, size_t strength)
{
    Image output(input.getSize());
    const size_t kernalSize = strength * 2 + 1;
    cv::GaussianBlur(input.getNative(),
                     output.getNative(),
                     cv::Size(kernalSize, kernalSize),
                     0.0,
                     0.0,
                     cv::BORDER_DEFAULT);
    return output;
}

//===========================================================================//
Image edgeDetect(const Image& input, double threshold)
{
    Image output(input.getSize());
    cv::Canny(input.getNative(),
              output.getNative(),
              threshold,
              threshold * 3,
              3, false);
    return output;
}

//===========================================================================//
Image invert(const Image& input)
{
    Image output(input.getSize());
    cv::bitwise_not(input.getNative(), output.getNative());
    return output;
}
}
}
