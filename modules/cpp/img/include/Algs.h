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
#ifndef __NYRA_IMG_BLUR_H__
#define __NYRA_IMG_BLUR_H__

#include <nyra/img/Image.h>

namespace nyra
{
namespace img
{
/*
 *  \func gaussianBlur
 *  \brief Performs a 2D gaussian blur over an image.
 *         The sigma value is calculated based on the strength.
 *
 *  \param input The image to blur
 *  \param strength The blur strength in one direction. The kernal will
 *         be created from this as 2 * strength + 1.
 *  \return The blurred image.
 */
Image gaussianBlur(const Image& input, size_t strength);

/*
 *  \func edgeDetect
 *  \brief Performs a 2D edge detection. Edges are white in the output and
 *         non-edges are black.
 *
 *  \param input The image to detect
 *  \param threshold A threshold to determine what should be an edge. A
 *         smaller number will result in more edges.
 *  \return The edge detection mask
 */
Image edgeDetect(const Image& input, double threshold);

/*
 *  \func invert
 *  \brief inverts The input image
 *
 *  \param input
 *  \return The inverted image
 */
Image invert(const Image& input);
}
}

#endif
