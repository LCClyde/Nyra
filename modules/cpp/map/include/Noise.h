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
#ifndef __NYRA_MAP_NOISE_H__
#define __NYRA_MAP_NOISE_H__

#include <nyra/img/Image.h>
#include <nyra/map/Constants.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace map
{
typedef core::Event<img::Color(double value)> PixFunc;

/*
 *  \class Noise
 *  \brief Base class for image based procedural generation for maps
 *
 *  \tparam NoiseT The noise type
 */
template <typename NoiseT>
class Noise
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the noise object
     *
     *  \param noise The underlying noise object
     */
    Noise(NoiseT* noise) :
        mNoise(noise)
    {
    }

    /*
     *  \func getImage
     *  \brief Gets the land mask as an image
     *
     *  \param size The size of the image. This should match the aspect
     *         ratio of the DEFAULT_SIZE for best results.
     *  \return The image
     */
    img::Image getImage(const math::Vector2U& size,
                        const PixFunc& func) const
    {
        img::Image image(size);
        const math::Vector2F resolution =
                calculateResolution(size.x, size.y);

        for (size_t y = 0; y < size.y; ++y)
        {
            for (size_t x = 0; x < size.x; ++x)
            {
                const double value =
                        (*mNoise)(x * resolution.x, y * resolution.y);
                image(x, y) = func(value);
            }
        }
        return image;
    }

    /*
     *  \func getMinMax
     *  \brief Gets the min and max of a noise function. This is not guaranteed
     *         to be the actual min/max as the values could go beyond these
     *         numbers at different resolutions..
     *
     *  \param noise The noise to evaluate
     *  \return The min / max. First in min, second is max.
     */
    std::pair<double, double> getMinMax() const
    {
        std::pair<double, double> minMax(std::numeric_limits<double>::max(),
                                         -std::numeric_limits<double>::max());
        for (size_t y = 0; y < DEFAULT_SIZE.y; ++y)
        {
            for (size_t x = 0; x < DEFAULT_SIZE.x; ++x)
            {
                double value = (*mNoise)(x, y);
                minMax.first = std::min(value, minMax.first);
                minMax.second = std::max(value, minMax.second);
            }
        }
        return minMax;
    }

    /*
     *  \func getValueAtPercent
     *  \brief Gets the value that is x% between min / max
     *
     *  \param noise The noise to evaluate
     *  \param percent The desired percent from 0-1, 0 gives min, 1 gives max
     *  \return The value that represents the percent.
     */
    double getValueAtPercent(double percent) const
    {
        const double scale = 4.0;
        const math::Vector2U reducedSize = DEFAULT_SIZE / scale;
        const math::Vector2F resolution =
                calculateResolution(reducedSize.x, reducedSize.y);
        const size_t size = reducedSize.product();
        std::vector<double> values(size);

        for (size_t y = 0; y < reducedSize.y; ++y)
        {
            for (size_t x = 0; x < reducedSize.x; ++x)
            {
                values[y * reducedSize.x + x] =
                        (*mNoise)(x * resolution.x, y * resolution.y);
            }
        }
        std::sort(values.begin(), values.end());
        return values[static_cast<size_t>((size - 1) * percent)];
    }

private:
    math::Vector2F calculateResolution(double x, double y) const
    {
        return math::Vector2F(
                static_cast<double>(DEFAULT_SIZE.x - 1) / (x - 1),
                static_cast<double>(DEFAULT_SIZE.y - 1) / (y - 1));
    }

    std::unique_ptr<NoiseT> mNoise;
};
}
}

#endif
