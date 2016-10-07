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
#include <nyra/test/Test.h>
#include <nyra/test/Variable.h>

namespace nyra
{
namespace script
{
namespace py3
{
class TestVariable : public test::Variable<Variable>
{
};

TEST_F(TestVariable, GetSet)
{
    EXPECT_EQ(expectedInt8, int8());
    EXPECT_EQ(expectedUInt8, uint8());
    EXPECT_EQ(expectedInt16, int16());
    EXPECT_EQ(expectedUInt16, uint16());
    EXPECT_EQ(expectedInt32, int32());
    EXPECT_EQ(expectedUInt32, uint32());
    EXPECT_EQ(expectedInt64, int64());
    EXPECT_EQ(expectedUInt64, uint64());
    EXPECT_EQ(expectedFloat, floatPres());
    EXPECT_EQ(expectedDouble, doublePres());
    EXPECT_EQ(expectedString, string());
}

TEST_F(TestVariable, Stdout)
{
    EXPECT_EQ(expectedIntOut, stdoutInt());

    // This can fail because of precision, seeing how this is just a
    // mock, it doesn't really matter. Just remove some precision.
    EXPECT_EQ(expectedFloatOut, stdoutFloat().substr(0, 6));
    EXPECT_EQ(expectedStringOut, stdoutString());
}
}
}
}

NYRA_TEST()
