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
#include <nyra/core/String.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace core
{
//===========================================================================//
TEST(String, FindAndReplace)
{
    {
        const std::string input("This is ${TARGET} test!");
        const std::string results =
                findAndReplace(input, "${TARGET}", "a successful");
        EXPECT_EQ("This is a successful test!", results);
    }
    {
        const std::string input("abacadaeafa");
        const std::string results =
                findAndReplace(input, "a", "aa");
        EXPECT_EQ("aabaacaadaaeaafaa", results);
    }
}

//===========================================================================//
TEST(String, toString)
{
    EXPECT_EQ("Hello World!", toString("Hello World!"));
    EXPECT_EQ("Hello World!", toString(std::string("Hello World!")));
    EXPECT_EQ("42", toString(42));
    EXPECT_EQ("42.234", toString(42.234f));
    EXPECT_EQ("42.234567", toString(42.234567));
    EXPECT_EQ("true", toString(true));
    EXPECT_EQ("false", toString(false));
}

//===========================================================================//
TEST(String, toType)
{
    EXPECT_EQ("Hello World!", toType<std::string>("Hello World!"));
    EXPECT_EQ("Hello World!", toType<std::string>(std::string("Hello World!")));
    EXPECT_EQ(42, toType<int>("42"));
    EXPECT_FLOAT_EQ(42.234, toType<float>("42.234f"));
    EXPECT_DOUBLE_EQ(42.234567, toType<double>("42.234567"));
    EXPECT_FALSE(toType<bool>("False"));
    EXPECT_TRUE(toType<bool>("True"));
    EXPECT_FALSE(toType<bool>("false"));
    EXPECT_TRUE(toType<bool>("true"));
    EXPECT_FALSE(toType<bool>("0"));
    EXPECT_TRUE(toType<bool>("1"));
    EXPECT_ANY_THROW(toType<int>("foo"));
}
}
}

NYRA_TEST()
