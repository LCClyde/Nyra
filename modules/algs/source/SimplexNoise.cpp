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
#include <time.h>
#include <nyra/algs/SimplexNoise.h>

namespace nyra
{
namespace algs
{
//===========================================================================//
SimplexNoise::SimplexNoise(FractalType type,
                           double frequency,
                           double lacunarity,
                           double gain,
                           size_t octaves,
                           size_t seed)
{
    mNoise.SetNoiseType(FastNoise::SimplexFractal);
    mNoise.SetFrequency(frequency);
    mNoise.SetFractalType(static_cast<FastNoise::FractalType>(type));
    mNoise.SetFractalOctaves(octaves);
    mNoise.SetFractalLacunarity(lacunarity);
    mNoise.SetSeed(seed);
}

//===========================================================================//
SimplexNoise::SimplexNoise(FractalType type,
                           double frequency,
                           double lacunarity,
                           double gain,
                           size_t octaves) :
    SimplexNoise(type,
                 frequency,
                 lacunarity,
                 gain,
                 octaves,
                 time(nullptr))
{
}

//===========================================================================//
double SimplexNoise::operator()(double x, double y) const
{
    return mNoise.GetNoise(x, y);
}
}
}
