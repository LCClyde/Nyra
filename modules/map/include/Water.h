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
#ifndef __NYRA_MAP_WATER_H__
#define __NYRA_MAP_WATER_H__

#include <nyra/img/Image.h>
#include <nyra/algs/SimplexNoise.h>
#include <nyra/map/Noise.h>

namespace nyra
{
namespace map
{
class Water
{
public:
    Water(size_t seed);

    img::Image getImage(const img::Image& landMask) const;

private:
    img::Image buildCoastEdgeMask(
            const img::Image& landMask) const;

    img::Image addColor(const img::Image& input) const;

    const Noise<algs::SimplexNoise> mNoise;
    const uint8_t mHalfNoise;
};
}
}

#endif
