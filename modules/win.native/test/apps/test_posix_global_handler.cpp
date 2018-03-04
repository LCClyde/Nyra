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
#include <nyra/win/native/PosixGlobalHandler.h>

namespace nyra
{
namespace win
{
namespace native
{
TEST(PosixGlobalHandler, Stdout)
{
    PosixGlobalHandler handler;
    const std::string expectedOffResults = "X11 is shutdown";
    EXPECT_EQ(test::stdout(handler), expectedOffResults);

    handler.initialize();
    const std::string expectedOnResults = "X11 is running";
    EXPECT_EQ(test::stdout(handler), expectedOnResults);
    handler.shutdown();
    EXPECT_EQ(test::stdout(handler), expectedOffResults);
}
}
}
}

NYRA_TEST()
