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
#include <nyra/process/BackgroundSubprocess.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace process
{
TEST(BackgroundSubprocess, Stdout)
{
    const std::string bin = core::path::join(
            core::APPLICATION_PATH, "test_subprocess");

    BackgroundSubprocess proc(bin, {"Test Arg"});

    EXPECT_EQ("Hello World\nTest Arg\n", proc.getStdOut());
    EXPECT_EQ("Hello Error\n", proc.getStdErr());

    //while(true) {}
}

TEST(BackgroundSubprocess, Terminate)
{
    const std::string bin = core::path::join(
            core::APPLICATION_PATH, "test_subprocess");

    BackgroundSubprocess proc(bin, {"loop"});
    EXPECT_TRUE(proc.isRunning());
    proc.terminate();
    EXPECT_FALSE(proc.isRunning());
}

TEST(BackgroundSubprocess, FallOutScope)
{
    const std::string bin = core::path::join(
            core::APPLICATION_PATH, "test_subprocess");

    BackgroundSubprocess proc(bin, {"loop"});
    EXPECT_TRUE(proc.isRunning());
}
}
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (argv[1] == std::string("loop"))
        {
            while (true)
            {
            }
        }
        else
        {
            std::cout << "Hello World\n";
            std::cout << argv[1] << "\n";
            std::cerr << "Hello Error\n";
        }

        return 42;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
