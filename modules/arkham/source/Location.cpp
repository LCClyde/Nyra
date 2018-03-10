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
#include <nyra/arkham/Location.h>

namespace nyra
{
namespace arkham
{
//===========================================================================//
Location::Location() :
    expansion(arkham::CORE),
    blue(false),
    green(false),
    red(false),
    yellow(false)
{
}

//===========================================================================//
Location::Location(const std::string& name,
                   const std::string& expansion) :
    name(name),
    expansion(stringToExpansion(expansion)),
    blue(false),
    green(false),
    red(false),
    yellow(false)
{
}

//===========================================================================//
Location::Location(const std::string& name,
                   const std::string& expansion,
                   bool blue,
                   bool green,
                   bool red,
                   bool yellow) :
    name(name),
    expansion(stringToExpansion(expansion)),
    blue(blue),
    green(green),
    red(red),
    yellow(yellow)
{
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << location.name;
    return os;
}
}
}
