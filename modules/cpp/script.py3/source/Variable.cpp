/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/script/py3/Variable.h>

namespace nyra
{
namespace script
{
namespace py3
{
//===========================================================================//
void Variable::setInt(int64_t value)
{
    mData.reset(PyLong_FromLong(value));
}

//===========================================================================//
void Variable::setFloat(double value)
{
    mData.reset(PyFloat_FromDouble(value));
}

//===========================================================================//
void Variable::setString(const std::string& value)
{
    mData.reset(PyBytes_FromStringAndSize(value.c_str(), value.size()));
}

//===========================================================================//
int64_t Variable::getInt() const
{
    return PyLong_AsLong(mData.get());
}

//===========================================================================//
double Variable::getFloat() const
{
    return PyFloat_AsDouble(mData.get());
}

//===========================================================================//
std::string Variable::getString() const
{
    return std::string(PyBytes_AsString(mData.get()),
                       PyBytes_Size(mData.get()));
}

//===========================================================================//
std::string Variable::toString() const
{
    AutoPy function(PyObject_GetAttrString(mData.get(), "__str__"));
    AutoPy call(PyObject_CallObject(function.get(), nullptr));
    return std::string(PyBytes_AsString(call.get()),
                       PyBytes_Size(call.get()));
}
}
}
}
