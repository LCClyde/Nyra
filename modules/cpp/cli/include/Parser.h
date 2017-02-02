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
#ifndef __NYRA_CLI_PARSER_H__
#define __NYRA_CLI_PARSER_H__

#include <string>
#include <boost/program_options.hpp>
#include <nyra/cli/Options.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace cli
{
/*
 *  \class Parser
 *  \brief Parses the command line options.
 */
class Parser
{
public:
    /*
     *  \func Constructor
     *  \brief Parses the command line.
     *
     *  \param options The filled out options
     *  \param argc The argc argument from main
     *  \param argv The argv arguments from main
     */
    Parser(const Options& options, int argc, char** argv);

    /*
     *  \func get
     *  \brief Gets the command line option
     *
     *  \tparam T The desired type for the option.
     *  \param index The command line option
     *  \return The value
     *  \throw If the value was not set.
     */
    template <typename T = std::string>
    T get(const std::string& index) const
    {
        if (!isSet(index))
        {
            throw std::runtime_error("Command line parameter, " +
                    index + ", is has not been set.");
        }

        if (boost::any_cast<std::string>(&mMap[index].value()))
        {
            return core::str::toType<T>(mMap[index].as<std::string>());
        }
        else
        {
            return mMap[index].as<T>();
        }
    }

    /*
     *  \func isSet
     *  \brief Was the option set?
     *
     *  \return true if the option is set.
     */
    bool isSet(const std::string& index) const
    {
        return mMap.count(index) > 0;
    }

    /*
     *  \func help
     *  \brief Gets the help string. The help string can also be obtained
     *         through an ostream << operation.
     *
     *  \return The help string.
     */
    std::string help() const;

private:
    friend std::ostream& operator<<(std::ostream& os, const Parser& parser);

    boost::program_options::options_description mDescription;
    boost::program_options::positional_options_description mPositional;
    boost::program_options::variables_map mMap;
};
}
}

#endif
