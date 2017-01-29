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
#ifndef __NYRA_CLI_OPTION_H__
#define __NYRA_CLI_OPTION_H__

#include <string>
#include <memory>
#include <nyra/core/String.h>

namespace nyra
{
namespace cli
{
/*
 *  \class Option
 *  \brief Class that stores information about a command line option.
 */
class Option
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the Option
     *
     *  \param flags The flags used to set this option. The dashes should not
     *         be included.
     *  \param description The description of the option. This is used when
     *         --help is called.
     */
    Option(const std::string& flags,
           const std::string& description);

    /*
     *  \func setDefault
     *  \brief Sets the default value for an option. This flag is ignored for
     *         flags (flags always default to "false").
     *
     *  \tparam The type to store. The type must serialize and deserialze to
     *          string.
     *  \param default_ The default value (note: default is a c++ keyword).
     *  \return The Option object. Allows chaining methods.
     */
    template <typename T>
    Option& setDefault(const T& default_)
    {
        mDefault.reset(new std::string(core::toString(default_)));
        return *this;
    }

    /*
     *  \func setIsFlag
     *  \brief If called the option is considered a true/false flag. If the
     *         flag is sent in, the value will be true. Otherwise it will
     *         be false.
     *
     *  \return The Option object. Allows chaining methods.
     */
    Option& setIsFlag()
    {
        mIsFlag = true;
        return *this;
    }

    /*
     *  \func setPositional
     *  \brief If called the option can be used without using the --flag
     *         prefix.
     *
     *  \return The Option object. Allows chaining methods.
     */
    Option& setPositional()
    {
        mPositional = true;
        return *this;
    }

    /*
     *  \func getDescription
     *  \brief Gets the description of the option
     *
     *  \return The description
     */
    const std::string& getDescription() const
    {
        return mDescription;
    }

    /*
     *  \func getFlags
     *  \brief Gets the flags for the option
     *
     *  \return The flags
     */
    const std::string& getFlags() const
    {
        return mFlags;
    }

    /*
     *  \func isFlag
     *  \brief Is the option a true/false flag?
     *
     *  \return true if the option is a simple flag.
     */
    bool isFlag() const
    {
        return mIsFlag;
    }

    /*
     *  \func isPositional
     *  \brief Is the option positional?
     *
     *  \return true if the option is positional.
     */
    bool isPositional() const
    {
        return mPositional;
    }

    /*
     *  \func hasDefault
     *  \brief Does the option have a default value set?
     *
     *  \return true If the option has a default value. This is not meaningful
     *          if isFlag set to true.
     */
    bool hasDefault() const
    {
        return mDefault.get();
    }

    /*
     *  \func getDefault
     *  \brief Gets the default value of the option. This is not meaningful if
     *         isFlag set to true.
     *
     *  \return The default value.
     */
    const std::string& getDefault() const
    {
        return *mDefault;
    }

private:
    std::string mFlags;
    std::string mDescription;
    std::unique_ptr<std::string> mDefault;
    bool mIsFlag;
    bool mPositional;
};
}
}

#endif
