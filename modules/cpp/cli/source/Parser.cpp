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
#include <iostream>
#include <nyra/cli/Parser.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace cli
{
//===========================================================================//
Parser::Parser(const Options& options, int argc, char** argv) :
    mDescription(options.getDescription()),
    mPositional(options.getPositional())
{
    boost::program_options::store(boost::program_options::command_line_parser(
            argc, argv).options(mDescription).
            positional(mPositional).run(), mMap);
    boost::program_options::notify(mMap);

    if (get<bool>("help"))
    {
        std::cout << core::path::split(argv[0]).back() << ":\n";
        std::cout << (*this);
        std::exit(EXIT_SUCCESS);
    }
}

//===========================================================================//
std::string Parser::help() const
{
    std::stringstream ss;
    ss << mDescription;
    return ss.str();
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Parser& parser)
{
    os << parser.help();
    return os;
}
}
}
