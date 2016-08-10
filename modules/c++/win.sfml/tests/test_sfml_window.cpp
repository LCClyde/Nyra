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
#include <nyra/win.sfml/Window.h>
#include <nyra/test/Test.h>
#include <nyra/test/Required.h>

namespace
{
void update(nyra::win::sfml::Window& window)
{
    for (size_t ii = 0; ii < 10000; ++ii)
    {
        window.update();
    }
}
}

TEST(Window, Archive)
{
    nyra::win::sfml::Window input("Test",
                                  nyra::math::Vector2U(1280, 720),
                                  nyra::math::Vector2I(512, 256));
    update(input);
    nyra::win::sfml::Window output = nyra::test::testArchive(input);
    update(output);
    EXPECT_EQ(input.getName(), output.getName());
    EXPECT_EQ(input.getSize(), output.getSize());
    EXPECT_EQ(input.getPosition(), output.getPosition());
    std::cout << input.getPosition() << "\n";
    std::cout << output.getPosition() << "\n";
}

TEST(Required, Stdout)
{
    nyra::win::sfml::Window input("Test",
                                  nyra::math::Vector2U(1280, 720),
                                  nyra::math::Vector2I(0, 0));
    update(input);
    const std::string out = nyra::test::testStdout(input);

    // TODO: This fails because SFML does not set and get the
    //       window position correctly.
    EXPECT_EQ(out, "Name: Test\nSize: x=1280 y=720\nPosition: x=512 y=256");
    //EXPECT_EQ(out.substr(0, 30), "Name: Test\nSize: x=1280 y=720\n");

}

NYRA_TEST()
