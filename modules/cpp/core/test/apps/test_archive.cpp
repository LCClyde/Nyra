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
#include <nyra/core/Archive.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace core
{
TEST(Archive, Text)
{
    // Test return version
    int foo = 12345;
    write<int>(foo, "temp", TEXT);
    int bar = nyra::core::read<int>("temp", TEXT);
    EXPECT_EQ(foo, bar);

    // Test output param version
    foo = 67890;
    write<int>(foo, "temp", TEXT);
    read<int>("temp", bar, TEXT);
    EXPECT_EQ(foo, bar);

    std::remove("temp");
}

TEST(Archive, Binary)
{
    // Test return version
    int foo = 12345;
    write<int>(foo, "temp", BINARY);
    int bar = nyra::core::read<int>("temp", BINARY);
    EXPECT_EQ(foo, bar);

    // Test output param version
    foo = 67890;
    write<int>(foo, "temp", BINARY);
    read<int>("temp", bar, BINARY);
    EXPECT_EQ(foo, bar);

    std::remove("temp");
}

TEST(Archive, XML)
{
    // Test return version
    int foo = 12345;
    write<int>(foo, "temp", XML);
    int bar = nyra::core::read<int>("temp", XML);
    EXPECT_EQ(foo, bar);

    // Test output param version
    foo = 67890;
    write<int>(foo, "temp", XML);
    read<int>("temp", bar, XML);
    EXPECT_EQ(foo, bar);

    std::remove("temp");
}
}
}

NYRA_TEST()
