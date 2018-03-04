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
#include <nyra/test/Test.h>
#include <nyra/process/Subprocess.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace process
{
TEST(Subprocess, Stdout)
{
    std::string stdout;
    std::string stderr;

    const std::string proc = core::path::join(
            core::APPLICATION_PATH, "test_subprocess");

    subprocess(proc, {"Test Arg"}, stdout, stderr);

    EXPECT_EQ("Hello World\nTest Arg\n", stdout);
    EXPECT_EQ("Hello Error\n", stderr);
}
}
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        std::cout << "Hello World\n";
        std::cout << argv[1] << "\n";
        std::cerr << "Hello Error\n";

        return 42;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
