/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <nyra/crypto/BaseX.h>

namespace nyra
{
namespace crypto
{
//===========================================================================//
TEST(Base64, Encode)
{
    const std::string buffer = "Hello World!";
    const std::string strResults = base64Encode(buffer);
    const std::string voidResults =
            base64Encode(buffer.c_str(), buffer.length());

    // Expect results from https://www.base64encode.org/
    EXPECT_EQ("SGVsbG8gV29ybGQh", strResults);
    EXPECT_EQ("SGVsbG8gV29ybGQh", voidResults);
}

//===========================================================================//
TEST(Base64, Decode)
{
    const std::string buffer = "SGVsbG8gV29ybGQh";
    const std::string results = base64Decode(buffer);

    // Expect results from https://www.base64encode.org/
    EXPECT_EQ("Hello World!", results);
}
}
}

NYRA_TEST()
