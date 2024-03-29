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
#include <nyra/core/Regex.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace core
{
//===========================================================================//
TEST(Regex, Matches)
{
    {
        const std::vector<std::string> results =
                regexMatches("555-867-5309", std::regex("(\\d{3,4})"));
        ASSERT_EQ(static_cast<size_t>(3), results.size());
        EXPECT_EQ("555", results[0]);
        EXPECT_EQ("867", results[1]);
        EXPECT_EQ("5309", results[2]);
    }

    {
        const std::vector<std::string> results =
                regexMatches("555-867-5309", "(\\d{3,4})");
        ASSERT_EQ(static_cast<size_t>(3), results.size());
        EXPECT_EQ("555", results[0]);
        EXPECT_EQ("867", results[1]);
        EXPECT_EQ("5309", results[2]);
    }
}
}
}

NYRA_TEST()
