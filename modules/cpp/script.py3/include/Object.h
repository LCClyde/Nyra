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
#ifndef __NYRA_SCRIPT_PY3_OBJECT_H__
#define __NYRA_SCRIPT_PY3_OBJECT_H__

#include <nyra/script/Object.h>
#include <nyra/script/Include.h>
#include <nyra/script/py3/AutoPy.h>

namespace nyra
{
namespace script
{
namespace py3
{
/*
 *  \class Object
 *  \brief Represents a python object
 */
class Object : public script::Object
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a python object
     *
     *  \param The module that includes the class
     *  \param name The name of the class
     */
    Object(const script::Include& include,
           const std::string& name);

    /*
     *  \func Constructor
     *  \brief Creates a python object from a PyObject
     *
     *  \param object The pyObject
     */
    Object(AutoPy object);

    /*
     *  \func variable
     *  \brief Gets a variable from the object
     *
     *  \param name The name of the variable
     *  \return The variable
     */
    VariablePtr variable(const std::string& name) override;

    /*
     *  \func function
     *  \brief Gets a function from the object
     *
     *  \param name The name of the function
     *  \return The function
     */
    FunctionPtr function(const std::string& name) override;
    /*
     *  \func getNative
     *  \brief Gets the underlying PyObject
     *
     *  \return The PyObject
     */
    const AutoPy& getNative() const
    {
        return mObject;
    }

private:
    AutoPy mObject;
};
}
}
}

#endif
