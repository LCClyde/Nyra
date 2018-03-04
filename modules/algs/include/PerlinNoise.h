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
#ifndef __NYRA_ALGS_PERLIN_NOISE_H__
#define __NYRA_ALGS_PERLIN_NOISE_H__

#include <stdint.h>
#include <FastNoise.h>
#include <nyra/algs/NoiseConstants.h>

namespace nyra
{
namespace algs
{
/*
 *  \class PerlinNoise
 *  \brief Performs fractal perlin noise
 */
class PerlinNoise
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a random perlin noise
     *
     *  \param type The algorithm to create the fractal
     *  \param frequency The frequency of the coherent noise
     *  \param lacunarity The amount the frequency changes each octave
     *  \param gain How fast the amplitude grows
     */
    PerlinNoise(FractalType type,
                double frequency,
                double lacunarity,
                double gain,
                size_t octaves);

    /*
     *  \func Constructor
     *  \brief Sets up a perlin noise based on a see.
     *
     *  \param type The algorithm to create the fractal
     *  \param frequency The frequency of the coherent noise
     *  \param lacunarity The amount the frequency changes each octave
     *  \param gain How fast the amplitude grows
     *  \param seed The seed to use for randomization.
     */
    PerlinNoise(FractalType type,
                double frequency,
                double lacunarity,
                double gain,
                size_t octaves,
                size_t seed);

    /*
     *  \func Functor
     *  \brief Calculates the noise value at an (x, y) location.
     *
     *  \param x The x location
     *  \param y The y location
     *  \return The noise value at the x, y location.
     */
    double operator()(double x, double y) const;

private:
    mutable FastNoise mNoise;
};
}
}

#endif
