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
#include <nyra/mem/SetParent.h>
#include <nyra/test/Test.h>

namespace
{
class MockParent
{
public:
    MockParent() :
        set(false)
    {
    }

    void setParent(const MockParent*)
    {
        set = true;
    }

    bool set;
};

class MockNoParent
{
public:
    MockNoParent() :
       set(false)
   {
   }

   bool set;
};
}

namespace nyra
{
namespace mem
{
TEST(SetParent, Call)
{
    MockParent parent;
    MockNoParent noParent;

    EXPECT_TRUE(HasSetParent<MockParent>::value);
    EXPECT_FALSE(HasSetParent<MockNoParent>::value);

    setParent(parent, &parent);
    EXPECT_TRUE(parent.set);

    setParent(noParent, &noParent);
    EXPECT_FALSE(noParent.set);
}
}
}

NYRA_TEST()
