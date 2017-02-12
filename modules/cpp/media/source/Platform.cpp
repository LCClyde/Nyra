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
#include <nyra/media/Platform.h>
#include <nyra/core/String.h>
#include <nyra/json/JSON.h>

namespace
{
//===========================================================================//
std::string extensionsToString(const std::vector<std::string>& extensions)
{
    if (extensions.empty())
    {
        return "";
    }

    std::string ret(extensions[0]);

    for (size_t ii = 1; ii < extensions.size(); ++ii)
    {
        ret += "," + extensions[ii];
    }

    return ret;
}
}

namespace nyra
{
namespace media
{
//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Platform& platform)
{
    std::string extensions = extensionsToString(platform.extensions);
    os << "Name:        " << platform.name << "\n"
       << "Extensions:  " << extensions << "\n"
       << "GoodTool:    " << platform.goodTool << "\n"
       << "GoodMerge:   " << platform.goodMerge;
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<media::Platform>(const media::Platform& platform,
                            const std::string& pathname,
                            core::ArchiveType type)
{
    json::JSON tree;
    tree["name"] = platform.name;
    tree["extensions"] = extensionsToString(platform.extensions);
    tree["good_tool"] = platform.goodTool;
    tree["good_merge"] = platform.goodMerge;
    write<json::JSON>(tree, pathname);
}

//===========================================================================//
template <>
void read<media::Platform>(const std::string& pathname,
                           media::Platform& platform,
                           core::ArchiveType type)
{
    const json::JSON tree = read<json::JSON>(pathname);
    platform.name = tree["name"].get();
    platform.extensions = core::str::split(tree["extensions"].get(), ",");
    platform.goodTool = tree["good_tool"].get();
    platform.goodMerge = tree["good_merge"].get();
}
}
}
