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
#include <fstream>
#include <nyra/core/Path.h>
#include <nyra/test/Test.h>

namespace
{
bool openBinary(const std::string& path,
                const std::string& binary)
{
    std::fstream thisBinary((path + "/" + binary).c_str(),
                            std::ios::in | std::ios::binary);
    return thisBinary.is_open();
}
}

namespace nyra
{
namespace core
{
TEST(Path, Constants)
{
    EXPECT_TRUE(openBinary(APPLICATION_PATH, "test_path"));
    EXPECT_TRUE(openBinary(INSTALL_PATH, "tests/core/test_path"));
    EXPECT_TRUE(openBinary(DATA_PATH, "../tests/core/test_path"));
}

namespace path
{
TEST(Path, Split)
{
    std::vector<std::string> expected;
    expected.push_back("/");
    EXPECT_EQ(split("/"), expected);

    expected.push_back("foo");
    expected.push_back("bar");
    expected.push_back("baz.txt");
    EXPECT_EQ(split("/foo/bar/baz.txt"), expected);

    expected.clear();
    expected.push_back("foo");
    expected.push_back("bar.txt");
    EXPECT_EQ(split("foo/bar.txt"), expected);

    expected.clear();
    expected.push_back("C:");
    expected.push_back(".");
    EXPECT_EQ(split("C://"), expected);

    expected.clear();
    expected.push_back("C:");
    expected.push_back("foo");
    expected.push_back("bar");
    expected.push_back("baz.txt");
    EXPECT_EQ(split("C://foo/bar/baz.txt"), expected);
}

TEST(Path, Join)
{
    EXPECT_EQ(join("/foo/bar", "baz"), "/foo/bar/baz");
    EXPECT_EQ(join("/foo/bar", "../baz"), "/foo/baz");
    EXPECT_EQ(join("foo/bar", "../../../baz"), "../baz");
}
}
}
}

NYRA_TEST()
