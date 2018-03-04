/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/math/Vector2.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Vector2, Construction)
{
    // x, y construction should assign values
    {
        const Vector2F vecF(5.67f, 1.23f);
        EXPECT_EQ(vecF.x, 5.67f);
        EXPECT_EQ(vecF.y, 1.23f);
        const Vector2D vecD(5.67f, 1.23f);
        EXPECT_EQ(vecD.x, 5.67f);
        EXPECT_EQ(vecD.y, 1.23f);
        const Vector2I vecI(-345, 987);
        EXPECT_EQ(vecI.x, -345);
        EXPECT_EQ(vecI.y, 987);
        const Vector2U VecU(246, 357);
        EXPECT_EQ(VecU.x, static_cast<size_t>(246));
        EXPECT_EQ(VecU.y, static_cast<size_t>(357));
        const Vector2F vec(1.5f);
        EXPECT_EQ(1.5f, vec.x);
        EXPECT_EQ(1.5f, vec.y);
    }
}

TEST(Vector2, Constructor)
{
    const Vector2F foo(1280, 720);
    Vector2F bar(foo);
    bar.x = foo.x / 2;
    bar.y = foo.y / 2;
    EXPECT_EQ(static_cast<size_t>(1280), foo.x);
    EXPECT_EQ(static_cast<size_t>(720), foo.y);
    EXPECT_EQ(static_cast<size_t>(640), bar.x);
    EXPECT_EQ(static_cast<size_t>(360), bar.y);

    bar.x = 12.9f;
    bar.y = 13.4f;
    const Vector2U baz(bar);
    EXPECT_EQ(12.9f, bar.x);
    EXPECT_EQ(13.4f, bar.y);
    EXPECT_EQ(12, baz.x);
    EXPECT_EQ(13, baz.y);
}

TEST(Vector2, Archive)
{
    Vector2F input(1.234f, 5.678);
    Vector2F output =
            test::archive<Vector2F>(input);
    EXPECT_EQ(input, output);
}

TEST(Vector2, Stdout)
{
    Vector2F input(1.234f, 5.678);
    std::string out = test::stdout(input);
    EXPECT_EQ(out, "x=1.234 y=5.678");
}
}
}

NYRA_TEST()
