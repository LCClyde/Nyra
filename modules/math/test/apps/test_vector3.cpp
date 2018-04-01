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
#include <nyra/math/Vector3.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Vector3, Construction)
{
    // x, y construction should assign values
    {
        const Vector3F vecF(5.67f, 1.23f, 4.56f);
        EXPECT_EQ(vecF.x, 5.67f);
        EXPECT_EQ(vecF.y, 1.23f);
        EXPECT_EQ(vecF.z, 4.56f);
        const Vector3D vecD(5.67f, 1.23f, 4.56f);
        EXPECT_EQ(vecD.x, 5.67f);
        EXPECT_EQ(vecD.y, 1.23f);
        EXPECT_EQ(vecD.z, 4.56f);
        const Vector3I vecI(-345, 987, 342);
        EXPECT_EQ(vecI.x, -345);
        EXPECT_EQ(vecI.y, 987);
        EXPECT_EQ(vecI.z, 342);
        const Vector3U VecU(246, 357, 342);
        EXPECT_EQ(VecU.x, static_cast<size_t>(246));
        EXPECT_EQ(VecU.y, static_cast<size_t>(357));
        EXPECT_EQ(VecU.z, static_cast<size_t>(342));
        const Vector3F vec(1.5f);
        EXPECT_EQ(1.5f, vec.x);
        EXPECT_EQ(1.5f, vec.y);
        EXPECT_EQ(1.5f, vec.z);
    }
}

TEST(Vector3, Archive)
{
    Vector3F input(1.234f, 5.678, 8.965);
    Vector3F output =
            test::archive<Vector3F>(input);
    EXPECT_EQ(input, output);
}

TEST(Vector3, Stdout)
{
    Vector3F input(1.234f, 5.678, 2.345);
    std::string out = test::stdout(input);
    EXPECT_EQ(out, "x=1.234 y=5.678 z=2.345");
}
}
}

NYRA_TEST()
