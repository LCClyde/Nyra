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
#include <limits>
#include <boost/algorithm/string.hpp>
#include <nyra/core/String.h>

namespace nyra
{
namespace core
{
namespace str
{
//===========================================================================//
std::string findAndReplace(std::string input,
                           const std::string& find,
                           const std::string& replace)
{
    size_t pos = 0;
    while ((pos = input.find(find, pos)) != std::string::npos)
    {
         input.replace(pos, find.length(), replace);
         pos += replace.length();
    }
    return input;
}

//===========================================================================//
template<> std::string toType<std::string>(const std::string& s)
{
    return s;
}

//===========================================================================//
template<> bool toType<bool>(const std::string& s)
{
    if (s == "true" || s == "True" || s == "1")
    {
        return true;
    }
    else if (s == "false" || s == "False" || s == "0")
    {
        return false;
    }

    throw std::runtime_error(
            "Unable to convert string to bool for string: " + s);
}

//===========================================================================//
template<> size_t getPrecision(const float& )
{
    return std::numeric_limits<float>::digits10 + 1;
}

//===========================================================================//
template<> size_t getPrecision(const double& )
{
    return std::numeric_limits<double>::digits10 + 1;
}

//===========================================================================//
template<> size_t getPrecision(const long double& )
{
    return std::numeric_limits<long double>::digits10 + 1;
}

//===========================================================================//
std::vector<std::string> split(const std::string& string,
                               const std::string& delim)
{
    std::vector<std::string> ret;

    using namespace boost::algorithm;
    typedef split_iterator<std::string::const_iterator> Iter;

    for(Iter iter=make_split_iterator(string, first_finder(delim, is_equal()));
        iter != Iter(); ++iter)
    {
        ret.push_back(boost::copy_range<std::string>(*iter));
    }

    return ret;
}

//===========================================================================//
bool endsWith(const std::string& input,
              const std::string& end)
{
    if (end.size() > input.size())
    {
        return false;
    }

    return std::equal(end.rbegin(), end.rend(), input.rbegin());
}
}
}
}


