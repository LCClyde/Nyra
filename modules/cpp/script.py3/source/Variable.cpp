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
#include <nyra/script/py3/Include.h>
#include <nyra/script/py3/Object.h>
#include <iostream>

namespace nyra
{
namespace script
{
namespace py3
{
//===========================================================================//
Variable::Variable(const script::Include& include,
                   const std::string& name) :
    Variable(dynamic_cast<const Include&>(include).getNative(), name)
{
}

//===========================================================================//
Variable::Variable(const AutoPy& pyObject,
                   const std::string& name) :
    mName(name),
    mParent(pyObject)
{
}

//===========================================================================//
void Variable::setInt(int64_t value)
{
    mData.reset(PyLong_FromLong(value));
    setVar();
}

//===========================================================================//
void Variable::setFloat(double value)
{
    mData.reset(PyFloat_FromDouble(value));
    setVar();
}

//===========================================================================//
void Variable::setString(const std::string& value)
{
    mData.reset(PyUnicode_FromStringAndSize(value.c_str(), value.size()));
    setVar();
}

//===========================================================================//
void Variable::setObject(const script::Object& object)
{
    mData = dynamic_cast<const Object&>(object).getNative();
    setVar();
}

//===========================================================================//
int64_t Variable::getInt() const
{
    return PyLong_AsLong(getVar().get());
}

//===========================================================================//
double Variable::getFloat() const
{
    return PyFloat_AsDouble(getVar().get());
}

//===========================================================================//
std::string Variable::getString() const
{
    AutoPy data(getVar());
    AutoPy string(PyUnicode_AsASCIIString(data.get()));
    return std::string(PyBytes_AsString(string.get()),
                       PyBytes_Size(string.get()));
}

//===========================================================================//
std::unique_ptr<script::Object> Variable::getObject() const
{
    return std::unique_ptr<script::Object>(new Object(getVar()));
}

//===========================================================================//
void Variable::setVar()
{
    if (!mName.empty())
    {
        PyObject_SetAttrString(mParent.get(), mName.c_str(), mData.get());
    }
}

//===========================================================================//
AutoPy Variable::getVar() const
{
    if (!mName.empty())
    {
        return AutoPy(PyObject_GetAttrString(mParent.get(), mName.c_str()));
    }
    return mData;
}

//===========================================================================//
std::string Variable::toString() const
{
    return mData.toString();
}
}
}
}
