/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_CORE_REGEX_H__
#define __NYRA_CORE_REGEX_H__

#include <string>
#include <vector>
#include <regex>

namespace nyra
{
namespace core
{
/*
 *  \func regexMatches
 *  \brief Gets all regex matches.
 *
 *  \input The string to check against. This is purposely non-const
 *         as it modifies the string under the hood.
 *  \regex The pattern to match
 *  \return All matches.
 */
std::vector<std::string> regexMatches(std::string input,
                                      const std::regex& regex);

/*
 *  \func regexMatches
 *  \brief Gets all regex matches.
 *
 *  \input The string to check against.
 *  \regex The pattern to match
 *  \return All matches.
 */
inline std::vector<std::string> regexMatches(const std::string& input,
                                             const std::string& regex)
{
    return regexMatches(input, std::regex(regex));
}
}
}

#endif
