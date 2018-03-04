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
#ifndef __NYRA_SCRIPT_FUNCTION_H__
#define __NYRA_SCRIPT_FUNCTION_H__

#include <nyra/script/Variable.h>

namespace nyra
{
namespace script
{
/*
 *  \class Function
 *  \brief Class to call script based functions.
 */
class Function
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~Function() = default;

    /*
     *  \func Functor
     *  \brief The implementation of the function call.
     *
     *  \param variables The function parameters
     *  \return The result.
     */
    virtual VariablePtr operator()(const VariableList& variables) = 0;

    VariablePtr call(const VariableList& variables)
    {
        return (*this)(variables);
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 0 params.
     */
    VariablePtr operator()()
    {
        return (*this)({});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 1 params.
     */
    VariablePtr operator()(const Variable& a)
    {
        return (*this)({&a});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 2 params.
     */
    VariablePtr operator()(const Variable& a,
                           const Variable& b)
    {
        return (*this)({&a, &b});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 3 params.
     */
    VariablePtr operator()(const Variable& a,
                           const Variable& b,
                           const Variable& c)
    {
        return (*this)({&a, &b, &c});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 4 params.
     */
    VariablePtr operator()(const Variable& a,
                           const Variable& b,
                           const Variable& c,
                           const Variable& d)
    {
        return (*this)({&a, &b, &c, &d});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 5 params.
     */
    VariablePtr operator()(const Variable& a,
                           const Variable& b,
                           const Variable& c,
                           const Variable& d,
                           const Variable& e)
    {
        return (*this)({&a, &b, &c, &d, &e});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 6 params.
     */
    VariablePtr operator()(const Variable& a,
                           const Variable& b,
                           const Variable& c,
                           const Variable& d,
                           const Variable& e,
                           const Variable& f)
    {
        return (*this)({&a, &b, &c, &d, &e, &f});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 0 params.
     */
    VariablePtr call()
    {
        return (*this)({});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 1 params.
     */
    VariablePtr call(const Variable& a)
    {
        return (*this)({&a});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 2 params.
     */
    VariablePtr call(const Variable& a,
                     const Variable& b)
    {
        return (*this)({&a, &b});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 3 params.
     */
    VariablePtr call(const Variable& a,
                     const Variable& b,
                     const Variable& c)
    {
        return (*this)({&a, &b, &c});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 4 params.
     */
    VariablePtr call(const Variable& a,
                     const Variable& b,
                     const Variable& c,
                     const Variable& d)
    {
        return (*this)({&a, &b, &c, &d});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 5 params.
     */
    VariablePtr call(const Variable& a,
                     const Variable& b,
                     const Variable& c,
                     const Variable& d,
                     const Variable& e)
    {
        return (*this)({&a, &b, &c, &d, &e});
    }

    /*
     *  \func Functor
     *  \brief Same as above but with 6 params.
     */
    VariablePtr call(const Variable& a,
                     const Variable& b,
                     const Variable& c,
                     const Variable& d,
                     const Variable& e,
                     const Variable& f)
    {
        return (*this)({&a, &b, &c, &d, &e, &f});
    }
};

typedef std::unique_ptr<Function> FunctionPtr;
}
}

#endif
