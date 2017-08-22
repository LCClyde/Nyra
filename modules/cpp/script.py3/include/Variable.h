/*
 * Copyright (c) 2016 Clyde Stanfield
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
#ifndef __NYRA_SCRIPT_PY3_VARIABLE_H__
#define __NYRA_SCRIPT_PY3_VARIABLE_H__

#include <nyra/script/Variable.h>
#include <nyra/script/py3/AutoPy.h>

namespace nyra
{
namespace script
{
namespace py3
{
/*
 *  \class Variable
 *  \brief Class that represents a variable that can translate to
 *         Python 3.x
 */
class Variable : public script::Variable
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty variable
     */
    Variable() = default;

    /*
     *  \func Constructor
     *  \brief Creates a variable from a value
     *
     *  \tparam TypeT The variable type
     *  \param t The value to set
     */
    template <typename TypeT>
    Variable(const TypeT& t)
    {
        set<TypeT>(t);
    }

    /*
     *  \func getNative
     *  \brief Gets the underlying PyObject
     *
     *  \return The PyObject
     */
    PyObject* getNative() const
    {
        return mData.get();
    }

    /*
     *  \func setNative
     *  \brief Sets the underlying PyObject
     *
     *  \param The PyObject
     */
    void setNative(PyObject* object)
    {
        mData.reset(object);
    }

    /*
     *  \func getAutoPy
     *  \brief Gets the underlying AutoPy. This is necessary for specialized
     *         functionality such as setting tuples which steal a ref.
     *
     *  \return The AutoPy
     */
    AutoPy& getAutoPy()
    {
        return mData;
    }

private:
    void setInt(int64_t value) override;

    void setFloat(double value) override;

    void setString(const std::string& value) override;

    int64_t getInt() const override;

    double getFloat() const override;

    std::string getString() const override;

    std::string toString() const override;

    AutoPy mData;
};
}
}
}

#endif
