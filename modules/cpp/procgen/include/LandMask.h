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
#ifndef __NYRA_PROCGEN_LAND_MASK_H__
#define __NYRA_PROCGEN_LAND_MASK_H__

#include <nyra/procgen/Module.h>
#include <nyra/algs/SimplexNoise.h>
#include <nyra/img/Image.h>
namespace nyra
{
namespace procgen
{
/*
 *  \class LandMask
 *  \brief Creates a mask where white is land and black is water.
 */
class LandMask : public Module<algs::SimplexNoise>
{
public:
    /*
     *  \func Constructor
     *  \brief Loads the LandMask
     *
     *  \param waterPercent The amount of water from 0-1. Where a 0 means
     *         no water, and a 1 is all water.
     *  \param seed The seed for creating the random number generator
     */
    LandMask(double waterPercent,
             size_t seed);

private:
    img::Color calcPixel(double value) override;

    const double mWaterValue;
};
}
}

#endif
