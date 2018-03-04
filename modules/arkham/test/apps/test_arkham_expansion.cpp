/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/test/Test.h>
#include <nyra/arkham/Expansion.h>

namespace nyra
{
namespace arkham
{
TEST(Expansion, Expansion)
{
    for (size_t ii = 0; ii < MAX_EXPANSION; ++ii)
    {
        const Expansion exp = static_cast<Expansion>(ii);
        const std::string stExp = expansionToString(exp);
        const Expansion newExp = stringToExpansion(stExp);
        EXPECT_EQ(newExp, exp);
    }

    // An empty string should return the core expansion
    EXPECT_EQ(stringToExpansion(""), CORE);

    EXPECT_ANY_THROW(stringToExpansion("Something crazy"));
    EXPECT_ANY_THROW(expansionToString(MAX_EXPANSION));
}
}
}

NYRA_TEST()
