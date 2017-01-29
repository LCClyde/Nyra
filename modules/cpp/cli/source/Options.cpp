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
#include <nyra/cli/Options.h>

namespace nyra
{
namespace cli
{
//===========================================================================//
Options::Options(const std::string& description) :
    mDescription(description)
{
    // Add help by default
    add("help,h", "Produces this help message").setIsFlag();
}

//===========================================================================//
Option& Options::add(const std::string& flags,
                     const std::string& description)
{
    mOptions.push_back(Option(flags, description));
    return mOptions.back();
}

//===========================================================================//
boost::program_options::options_description
Options::getDescription() const
{
    boost::program_options::options_description description(mDescription);

    for (const Option& option : mOptions)
    {
        if (option.isFlag())
        {
            description.add_options()(
                    option.getFlags().c_str(),
                    boost::program_options::bool_switch()->default_value(false),
                    option.getDescription().c_str());
        }
        else
        {
            auto value = boost::program_options::value<std::string>();

            if (option.hasDefault())
            {
                value = value->default_value(option.getDefault());
            }

            description.add_options()(
                    option.getFlags().c_str(),
                    value,
                    option.getDescription().c_str());
        }
    }

    return description;
}

//===========================================================================//
boost::program_options::positional_options_description
Options::getPositional() const
{
    boost::program_options::positional_options_description positional;

    for (const Option& option: mOptions)
    {
        if (option.isPositional())
        {
            positional.add(option.getFlags().c_str(), 1);
        }
    }

    return positional;
}
}
}
