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
#ifndef __NYRA_MEDIA_CONFIG_H__
#define __NYRA_MEDIA_CONFIG_H__

#include <string>
#include <nyra/json/JSON.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace media
{
/*
 *  \class Config
 *  \brief Class that defines top level media center config options.
 */
struct Config
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a default config.
     */
    Config();

    /*
     *  \var dataPath
     *  \brief The location of the data directory
     */
    std::string dataPath;

    /*
     *  \var windowSize
     *  \brief The size of the window client area
     */
    math::Vector2U windowSize;

    /*
     *  \var DEFAULT_SIZE
     *  \brief The default window size.
     */
    const static math::Vector2U DEFAULT_SIZE;

    /*
     *  \func getScreenScale
     *  \brief Gets the screen scale compared to the DEFAULT SIZE
     *
     *  \return The screen scale in each dimension
     */
    math::Vector2F getScreenScale() const
    {
        return math::Vector2F(
                static_cast<float>(windowSize.x) / DEFAULT_SIZE.x,
                static_cast<float>(windowSize.y) / DEFAULT_SIZE.y);
    }

    /*
     *  \func getMinScreenScale
     *  \brief Gets the min screen scale between each dimension
     *
     *  \return The min screen scale
     */
    double getMinScreenScale() const
    {
        const math::Vector2F scale = getScreenScale();
        return std::min(scale.x, scale.y);
    }

    /*
     *  \func getMaxScreenScale
     *  \brief Gets the max screen scale between each dimension
     *
     *  \return The max screen scale
     */
    double getMaxScreenScale() const
    {
        const math::Vector2F scale = getScreenScale();
        return std::max(scale.x, scale.y);
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Config& config);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes a Config to file.
 *
 *  \param config The config to save
 *  \param pathname The location to save to.
 *  \param type This will only write binary, even if you select something
 *         else
 */
template <>
void write<media::Config>(const media::Config& config,
                          const std::string& pathname,
                          core::ArchiveType type);

/*
 *  \func read
 *  \brief Reads a Config from file.
 *
 *  \param pathname The location to save to.
 *  \param config The config to load
 *  \param type This will only read binary, even if you select something
 *         else
 */
template <>
void read<media::Config>(const std::string& pathname,
                         media::Config& config,
                         core::ArchiveType type);
}
}

#endif
