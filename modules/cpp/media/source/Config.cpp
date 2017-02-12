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
#include <nyra/media/Config.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace media
{
//===========================================================================//
const math::Vector2U Config::DEFAULT_SIZE(1920, 1080);

//===========================================================================//
Config::Config() :
    dataPath(core::DATA_PATH),
    windowSize(DEFAULT_SIZE)
{
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Config& config)
{
    os << "Data Path:    " << config.dataPath << "\n"
       << "Window Size:  " << config.windowSize;
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<media::Config>(const media::Config& config,
                          const std::string& pathname,
                          core::ArchiveType type)
{
    json::JSON tree;
    tree["data_path"] = config.dataPath;
    tree["window_width"] = core::str::toString(config.windowSize.x());
    tree["window_height"] = core::str::toString(config.windowSize.y());
    core::write<json::JSON>(tree, pathname);
}

//===========================================================================//
template <>
void read<media::Config>(const std::string& pathname,
                         media::Config& config,
                         core::ArchiveType type)
{
    json::JSON tree = core::read<json::JSON>(pathname);

    config.dataPath = tree["data_path"].get();
    config.windowSize.x() =
            core::str::toType<size_t>(tree["window_width"].get());
    config.windowSize.y() =
            core::str::toType<size_t>(tree["window_height"].get());
}
}
}
