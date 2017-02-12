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
struct Config
{
public:
    Config();

    std::string dataPath;
    math::Vector2U windowSize;

    const static math::Vector2U DEFAULT_SIZE;

private:
    friend std::ostream& operator<<(std::ostream& os, const Config& config);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param image The image to save
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
 *  \brief Reads an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param pathname The location to save to.
 *  \param image The image to load
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
