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
#include <nyra/net/GlobalHandler.h>

namespace nyra
{
namespace net
{
TEST(GlobalHandler, Stdout)
{
    GlobalHandler handler;
    const std::string expectedOffResults = "CURL is not initialized";
    EXPECT_EQ(test::stdout(handler), expectedOffResults);
    EXPECT_TRUE(handler.get() == nullptr);

    handler.initialize();
    const std::string expectedOnResults = "CURL is initialized";
    EXPECT_EQ(test::stdout(handler), expectedOnResults);
    EXPECT_TRUE(handler.get() != nullptr);


    handler.shutdown();
    EXPECT_EQ(test::stdout(handler), expectedOffResults);
    EXPECT_TRUE(handler.get() == nullptr);
}
}
}

NYRA_TEST()
