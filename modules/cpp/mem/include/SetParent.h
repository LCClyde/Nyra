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
#ifndef __NYRA_MEM_SET_PARENT_H__
#define __NYRA_MEM_SET_PARENT_H__

#include <iostream>
#include <typeinfo>

namespace nyra
{
namespace mem
{
/*
 *  \class HasSetParent
 *  \brief Helper class used to determine if a class has a setParent method.
 *         This should only be used internally.
 *
 *  \tparam The class to check against.
 */
template <class Type>
class HasSetParent
{
private:
    template <typename T, T> struct TypeCheck;

    typedef char Yes;
    typedef long No;

    template <typename T> struct SetParentInternal
    {
        typedef void (T::*fptr)(const T*);
    };

    template <typename T> static Yes test(TypeCheck<typename SetParentInternal<T>::fptr, &T::setParent>*);
    template <typename T> static No test(...);

public:
    /*
     *  \var value
     *  \brief true if the class has a setParent(const T*) method.
     */
    static bool const value = (sizeof(test<Type>(0)) == sizeof(Yes));
};

/*
 *  \class SetParent
 *  \brief Base template class for specialization.
 *
 *  \tparam bool True if the class has a setParent method.
 */
template<bool>
struct SetParent;

/*
 *  \class SetParent
 *  \brief Class to call setParent on an object.
 */
template<>
struct SetParent<true>
{
    /*
     *  \func set
     *  \brief Calls setParent.
     *
     *  \tparam T The object type.
     *  \param child The child object.
     *  \param parent The child's parent.
     */
    template<typename T>
    static void set(T& child, const T* parent)
    {
        child.setParent(parent);
    }
};

/*
 *  \class SetParent
 *  \brief Class to call setParent when the method does not exist. In this
 *         case a no-op will be called.
 */
template<>
struct SetParent<false>
{
    /*
     *  \func set
     *  \brief No-op function. If this is called the object does not have
     *         a setParent method.
     *
     *  \tparam T The object type.
     *  \param child The child object.
     *  \param parent The child's parent.
     */
    template<typename T>
    static void set(T& child, const T* parent)
    {
    }
};

/*
 *
 */
template <typename T>
void setParent(T& child, const T* parent)
{
    SetParent<HasSetParent<T>::value>::set(child, parent);
}
}
}

#endif
