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
#ifndef __NYRA_SCRIPT_OBJECT_H__
#define __NYRA_SCRIPT_OBJECT_H__

#include <string>
#include <nyra/script/Variable.h>
#include <nyra/script/Function.h>

namespace nyra
{
namespace script
{
/*
 *  \class Object
 *  \brief Abstract instance of a script class.
 */
class Object
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~Object() = default;

    /*
     *  \func variable
     *  \brief Gets a variable from the object
     *
     *  \param name The name of the variable
     *  \return The variable
     */
    virtual VariablePtr variable(const std::string& name) = 0;

    /*
     *  \func function
     *  \brief Gets a function from the object
     *
     *  \param name The name of the function
     *  \return The function
     */
    virtual FunctionPtr function(const std::string& name) = 0;
};
}
}

#endif
