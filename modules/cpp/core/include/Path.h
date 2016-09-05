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
#ifndef __NYRA_CORE_PATH_H__
#define __NYRA_CORE_PATH_H__

#include <string>
#include <vector>

namespace nyra
{
namespace core
{
/*
 *  \var APPLICATION_PATH
 *  \brief The absolute path to the executable.
 *
 *  \throw If the definition of the application path is not supported on
 *         your platform.
 */
extern const std::string APPLICATION_PATH;

extern const std::string INSTALL_PATH;

extern const std::string DATA_PATH;

/*
 *  \namespace path
 *  \brief An extra namespace to help keep common functions outside of the
 *         nyra::core:: namespace. Other common modules such as str might
 *         have the functions with the same name.
 */
namespace path
{
/*
 *  \func split
 *  \brief Splits a path into it's parts.
 *
 *  \param input The path to split
 *  \return The parts of the path.
 */
std::vector<std::string> split(const std::string& input);

/*
 *  \func join
 *  \brief Joins to paths together and normalizes the result.
 *
 *  \param start The beginning of the path.
 *  \param end The desired end of the path.
 *  \return The joined path.
 */
std::string join(const std::string& start, const std::string& end);
}
}
}

#endif
