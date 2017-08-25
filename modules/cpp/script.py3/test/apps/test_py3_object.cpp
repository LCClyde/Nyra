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
#include <nyra/script/py3/Include.h>
#include <nyra/script/py3/Variable.h>
#include <nyra/script/py3/Object.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace script
{
namespace py3
{
TEST(Py3Function, Print)
{
    Include include("test_python");
    Object object(include, "SampleClass");
    Variable a(2);
    EXPECT_EQ(20, (*object.function("multiply_value"))(a)->get<int32_t>());
    EXPECT_EQ(40, (*object.function("multiply_value"))(a)->get<int32_t>());
    EXPECT_EQ(80, (*object.function("multiply_value"))(a)->get<int32_t>());
    EXPECT_EQ(80, object.variable("value")->get<int32_t>());
    object.variable("value")->set(5);
    EXPECT_EQ(5, object.variable("value")->get<int32_t>());
    EXPECT_EQ(10, (*object.function("multiply_value"))(a)->get<int32_t>());
    EXPECT_EQ(10, object.variable("value")->get<int32_t>());
}
}
}
}

NYRA_TEST()
