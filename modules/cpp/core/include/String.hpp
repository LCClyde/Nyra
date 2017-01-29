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
#ifndef __NYRA_CORE_STRING_HPP__
#define __NYRA_CORE_STRING_HPP__

#include <sstream>

namespace nyra
{
namespace core
{
//===========================================================================//
template<typename T>
size_t getPrecision(const T& )
{
    return 0;
}

//===========================================================================//
template<typename T>
std::string toString(const T& value)
{
    std::ostringstream buf;
    buf.precision(getPrecision(value));
    buf << std::boolalpha << value;
    return buf.str();
}

//===========================================================================//
template<typename T> T toType(const std::string& s)
{
    if (s.empty())
    {
        throw std::runtime_error("Cannot convert empty string");
    }

    T value;

    std::stringstream buf(s);
    buf.precision(getPrecision(value));
    buf >> value;

    if (buf.fail())
    {
        throw std::runtime_error("Unable to covert string: " + s);
    }

    return value;
}

//===========================================================================//
template<> bool toType<bool> (const std::string& s);
template<> std::string toType<std::string> (const std::string& s);

//===========================================================================//
template<> size_t getPrecision(const float& type);
template<> size_t getPrecision(const double& type);
template<> size_t getPrecision(const long double& type);
}
}

#endif
