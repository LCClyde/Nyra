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
#ifndef __NYRA_SCRIPT_PY3_AUTO_PY_H__
#define __NYRA_SCRIPT_PY3_AUTO_PY_H__

#include <nyra/mem/GlobalDependency.h>
#include <nyra/script/py3/GlobalHandler.h>

// Slots is a keyword in QT.
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

namespace nyra
{
namespace script
{
namespace py3
{
/*
 *  \class AutoPy
 *  \brief A wrapper class around a PyObject that allows it to be used
 *         similar to an std::unique_ptr. It offers copy and move
 *         semantics.
 */
class AutoPy : private nyra::mem::GlobalDependency<
        nyra::script::py3::GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an AutoPy from a PyObject.
     *
     *  \param object The PyObject to be managed.
     */
    explicit AutoPy(PyObject* object = nullptr);

    /*
     *  \func Constructor
     *  \brief Copy constructs an AutoPy from another AutoPy.
     *
     *  \param other The AutoPy to copy from.
     */
    AutoPy(const AutoPy& other);

    /*
     *  \func Constructor
     *  \brief Moves an AutoPy from one source to another. This steals the
     *         PyObject.
     *
     *  \param other The AutoPy to move from.
     */
    AutoPy(AutoPy&& other);

    /*
     *  \func Assignment
     *  \brief Assigns an AutoPy from another AutoPy object.
     *
     *  \param other The AutoPy to assign from.
     *  \return The copied AutoPy object.
     */
    AutoPy& operator=(const AutoPy& other);

    /*
     *  \func Assignment
     *  \brief Assign an AutoPy from rvalue. This steals the PyObject.
     *
     *  \param other The AutoPy to move.
     *  \return The AutoPy object with the managed PyObject.
     */
    AutoPy& operator=(AutoPy&& other);

    /*
     *  \func Destructor
     *  \brief Decrements the PyObject if it exists.
     */
    ~AutoPy();

    /*
     *  \func reset
     *  \brief Updates the underlying PyObject. This will decrement the
     *         current PyObject and it will no longer be managed here.
     *
     *  \param object The new PyObject to be managed. It is valid to pass
     *         in nullptr.
     */
    void reset(PyObject* object = nullptr);

    /*
     *  \func get
     *  \brief Returns the underlying PyObject. It is not recommended that
     *         you do anything to adjust the reference count manually.
     *
     *  \return The managed PyObject.
     */
    PyObject* get() const
    {
        return mObject;
    }

    /*
     *  \func steal
     *  \brief Takes ownership of the PyObject from the AutoPy.
     *
     *  \return The PyObject. You are now responsible for DEC'n it.
     */
    PyObject* steal() const;

    /*
     *  \func toString
     *  \brief Gets the python __str__ representation of the object
     *
     *  \return The string equivalent of __str__()
     */
    std::string toString() const;

private:
    void release();

    PyObject* mObject;
};
}
}
}

#endif
