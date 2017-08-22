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
#ifndef __NYRA_SCRIPT_PY3_FUNCTION_H__
#define __NYRA_SCRIPT_PY3_FUNCTION_H__

#include <nyra/script/Function.h>
#include <nyra/script/Include.h>
#include <nyra/script/py3/AutoPy.h>

namespace nyra
{
namespace script
{
namespace py3
{
/*
 *  \class Function
 *  \brief Class to call script based functions.
 */
class Function : public script::Function
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a function object
     *
     *  \param include The python module for the function
     *  \param name The name of the function
     */
    Function(const script::Include& include,
             const std::string& name);

    /*
     *  \func Functor
     *  \brief Calls the function
     *
     *  \param variables The arguments.
     *  \return The return value of the function.
     */
    VariablePtr operator()(const VariableList& variables) override;

    using script::Function::operator();

private:
    AutoPy mModule;
    AutoPy mFunction;
};
}
}
}

#endif
