/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <nyra/core/Path.h>
#include <boost/filesystem.hpp>

#ifdef NYRA_POSIX
#include <limits.h>
#include <unistd.h>
#endif

namespace
{
//! TODO: Implement this for other platforms
#ifdef NYRA_POSIX
std::string getApplicationPath()
{
    char buff[PATH_MAX];
    ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    std::string ret(buff);
    const size_t find = ret.find_last_of("/\\");
    return find != std::string::npos ? ret.substr(0, find + 1) : ret;
}
#else
std::string getApplicationPath()
{
    throw std::runtime_error(
        "Application path is not implemented on this platform.");
}
#endif

//===========================================================================//
std::string getInstallPath(const std::string& appPath)
{
    const std::vector<std::string> splits = nyra::core::path::split(appPath);
    std::string ret;
    for (const std::string& path : splits)
    {
        if (path == "tests" || path == "bin")
        {
            return ret;
        }
        ret = nyra::core::path::join(ret, path);
    }
    return ret;
}
}

namespace nyra
{
namespace core
{
//===========================================================================//
const std::string APPLICATION_PATH = getApplicationPath();
const std::string INSTALL_PATH = getInstallPath(APPLICATION_PATH);
const std::string DATA_PATH = path::join(INSTALL_PATH, "data");

namespace path
{
//===========================================================================//
std::vector<std::string> split(const std::string& input)
{
    std::vector<std::string> elements;
    for (const auto& curr : boost::filesystem::path(input))
    {
        elements.push_back(curr.filename().string());
    }
    return elements;
}

//===========================================================================//
std::string join(const std::string& start, const std::string& end)
{
    boost::filesystem::path path(start);
    path /= end;
    path.normalize();
    return path.string();
}

//===========================================================================//
bool exists(const std::string& pathname)
{
    return boost::filesystem::exists(pathname);
}
}
}
}
