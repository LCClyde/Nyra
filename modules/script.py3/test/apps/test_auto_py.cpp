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
#include <nyra/test/Test.h>
#include <nyra/script/py3/AutoPy.h>

namespace nyra
{
namespace script
{
namespace py3
{
TEST(AutoPy, Usage)
{
    // Create the AutoPy object first, as it will initialize Python
    // through the global handler.
    AutoPy origAuto;

    // Create a PyObject. Note that changing this number can change the
    // ref count. If you pick a common number, Python hands you a preallocated
    // value.
    PyObject* pyObject = PyLong_FromLong(42090909);

    // Get the current ref count.
    const Py_ssize_t refCount = Py_REFCNT(pyObject);

    origAuto.reset(pyObject);
    EXPECT_EQ(refCount, Py_REFCNT(origAuto.get()));

    // Test copy construct
    {
        AutoPy newAuto(origAuto);
        EXPECT_EQ(refCount + 1, Py_REFCNT(origAuto.get()));
        EXPECT_EQ(refCount + 1, Py_REFCNT(newAuto.get()));
    }

    // After falling out of scope the ref count should go down
    EXPECT_EQ(refCount, Py_REFCNT(origAuto.get()));

    // Test assignment
    {
        AutoPy newAuto;
        newAuto = origAuto;
        EXPECT_EQ(refCount + 1, Py_REFCNT(origAuto.get()));
        EXPECT_EQ(refCount + 1, Py_REFCNT(newAuto.get()));
    }

    // After falling out of scope the ref count should go down
    EXPECT_EQ(refCount, Py_REFCNT(origAuto.get()));

    // Test move
    {
        AutoPy newAuto(std::move(origAuto));
        EXPECT_EQ(nullptr, origAuto.get());
        EXPECT_EQ(refCount, Py_REFCNT(newAuto.get()));

        // Copy the value back in so we can do more testing
        origAuto = newAuto;
        EXPECT_EQ(refCount + 1, Py_REFCNT(origAuto.get()));
        EXPECT_EQ(refCount + 1, Py_REFCNT(newAuto.get()));
    }

    // After falling out of scope the ref count should go down
    EXPECT_EQ(refCount, Py_REFCNT(origAuto.get()));

    // Test move assignment
    {
        AutoPy newAuto = std::move(origAuto);
        EXPECT_EQ(nullptr, origAuto.get());
        EXPECT_EQ(refCount, Py_REFCNT(newAuto.get()));

        // Copy the value back in so we can do more testing
        origAuto = newAuto;
        EXPECT_EQ(refCount + 1, Py_REFCNT(origAuto.get()));
        EXPECT_EQ(refCount + 1, Py_REFCNT(newAuto.get()));
    }

    // After falling out of scope the ref count should go down
    EXPECT_EQ(refCount, Py_REFCNT(origAuto.get()));

    // Test reset, the only thing we can say here is, that after resetting,
    // the refCount will not be equal.
    origAuto.reset();
    EXPECT_EQ(nullptr, origAuto.get());
    EXPECT_NE(refCount, Py_REFCNT(pyObject));

}
}
}
}

NYRA_TEST()
