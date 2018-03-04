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
#ifndef __NYRA_CLI_OPTIONS_H__
#define __NYRA_CLI_OPTIONS_H__

#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <nyra/cli/Option.h>

namespace nyra
{
namespace cli
{
/*
 *  \class Options
 *  \brief Allows easy creation of Options in a single container.
 */
class Options
{
public:
    /*
     *  \func Options
     *  \brief Sets up the Options. Option("help,h") will be added by default.
     *
     *  \param description The description of the application. This will show
     *         up with --help.
     */
    Options(const std::string& description);

    /*
     *  \func add
     *  \brief Adds a new option.
     *
     *  \param flags The flags for the option. You can comma separate flags
     *         to allow multiple options.
     *  \param description The description of the option.
     *  \return The newly added Option.
     */
    Option& add(const std::string& flags,
                const std::string& description);

    /*
     *  \func getDescription
     *  \brief For internal use.
     *
     *  \return The boost options description.
     */
    boost::program_options::options_description
    getDescription() const;

    /*
     *  \func getPositional
     *  \brief For internal use.
     *
     *  \return The boost positional description.
     */
    boost::program_options::positional_options_description
    getPositional() const;

private:
    const std::string mDescription;
    std::vector<Option> mOptions;
};
}
}

#endif
