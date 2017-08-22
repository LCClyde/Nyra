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
#include <nyra/script/py3/Function.h>
#include <nyra/script/py3/Include.h>
#include <nyra/script/py3/Variable.h>
#include <iostream>

namespace nyra
{
namespace script
{
namespace py3
{
//===========================================================================//
Function::Function(const script::Include& include,
                   const std::string& name)
{
    const Include& pyInclude = dynamic_cast<const Include&>(include);
    mFunction.reset(PyObject_GetAttrString(
            pyInclude.getNative(), name.c_str()));
}

//===========================================================================//
VariablePtr Function::operator()(const VariableList& variables)
{
    AutoPy args(PyTuple_New(variables.size()));

    size_t idx = 0;
    for(script::Variable* var : variables )
    {
        // This steal a reference
        PyTuple_SetItem(args.get(), idx++, dynamic_cast<Variable*>(var)->getAutoPy().steal());
    }
    VariablePtr ret(new Variable());
    dynamic_cast<Variable*>(ret.get())->setNative(
            PyObject_CallObject(mFunction.get(), args.get()));
    return ret;
}
}
}
}
