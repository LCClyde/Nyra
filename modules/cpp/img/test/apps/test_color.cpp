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
#include <nyra/test/Test.h>
#include <nyra/img/Color.h>

namespace nyra
{
namespace img
{
TEST(Color, Equality)
{
    Color color;
    color.r = 0x56;
    color.g = 0x78;
    color.b = 0x9A;
    color.a = 0xBC;
    EXPECT_TRUE(color == color);

    Color wrong;
    wrong.r = 0x00;
    wrong.g = color.g;
    wrong.b = color.b;
    wrong.a = color.a;
    EXPECT_TRUE(color != wrong);

    wrong.r = color.r;
    wrong.g = 0x00;
    EXPECT_TRUE(color != wrong);

    wrong.g = color.g;
    wrong.b = 0x00;
    EXPECT_TRUE(color != wrong);

    wrong.b = color.b;
    wrong.a = 0x00;
    EXPECT_TRUE(color != wrong);
}

TEST(Color, Constructor)
{
    Color defaultColor;
    EXPECT_EQ(defaultColor.r, static_cast<uint8_t>(0x00));
    EXPECT_EQ(defaultColor.g, static_cast<uint8_t>(0x00));
    EXPECT_EQ(defaultColor.b, static_cast<uint8_t>(0x00));
    EXPECT_EQ(defaultColor.a, static_cast<uint8_t>(0xFF));

    Color rgbColor(0x56, 0x78, 0x9A);
    EXPECT_EQ(rgbColor.r, static_cast<uint8_t>(0x56));
    EXPECT_EQ(rgbColor.g, static_cast<uint8_t>(0x78));
    EXPECT_EQ(rgbColor.b, static_cast<uint8_t>(0x9A));
    EXPECT_EQ(rgbColor.a, static_cast<uint8_t>(0xFF));

    Color rgbaColor(0x56, 0x78, 0x9A, 0xBC);
    EXPECT_EQ(rgbaColor.r, static_cast<uint8_t>(0x56));
    EXPECT_EQ(rgbaColor.g, static_cast<uint8_t>(0x78));
    EXPECT_EQ(rgbaColor.b, static_cast<uint8_t>(0x9A));
    EXPECT_EQ(rgbaColor.a, static_cast<uint8_t>(0xBC));

    Color copyColor(rgbaColor);
    EXPECT_EQ(copyColor.r, static_cast<uint8_t>(0x56));
    EXPECT_EQ(copyColor.g, static_cast<uint8_t>(0x78));
    EXPECT_EQ(copyColor.b, static_cast<uint8_t>(0x9A));
    EXPECT_EQ(copyColor.a, static_cast<uint8_t>(0xBC));

    Color assignColor = rgbaColor;
    EXPECT_EQ(assignColor.r, static_cast<uint8_t>(0x56));
    EXPECT_EQ(assignColor.g, static_cast<uint8_t>(0x78));
    EXPECT_EQ(assignColor.b, static_cast<uint8_t>(0x9A));
    EXPECT_EQ(assignColor.a, static_cast<uint8_t>(0xBC));
}

TEST(Color, Cast)
{
    Color color(0x56, 0x78, 0x9A, 0xBC);
    EXPECT_EQ(reinterpret_cast<uint8_t*>(&color)[0],
              static_cast<uint8_t>(0x56));
    EXPECT_EQ(reinterpret_cast<uint8_t*>(&color)[1],
              static_cast<uint8_t>(0x78));
    EXPECT_EQ(reinterpret_cast<uint8_t*>(&color)[2],
              static_cast<uint8_t>(0x9A));
    EXPECT_EQ(reinterpret_cast<uint8_t*>(&color)[3],
              static_cast<uint8_t>(0xBC));
}

TEST(Color, Uint32)
{
    Color color(0x56, 0x78, 0x9A, 0xBC);
    EXPECT_EQ(color.toRGBA(), static_cast<uint32_t>(0x56789ABC));
    EXPECT_EQ(color.toARGB(), static_cast<uint32_t>(0xBC56789A));
}

TEST(Color, Add)
{
    Color c1;
    Color c2;

    c1 = Color(255, 0, 0, 255);
    c2 = Color(0, 0, 255, 255);
    EXPECT_EQ(Color(255, 0, 255, 255), c1 + c2);

    c1 = Color(1, 2, 3, 255);
    c2 = Color(4, 5, 6, 255);
    EXPECT_EQ(Color(5, 7, 9, 255), c1 + c2);

    c1 = Color(255, 80, 200, 255);
    c2 = Color(80, 255, 200, 255);
    EXPECT_EQ(Color(255, 255, 255, 255), c1 + c2);

    // TODO: Verify alpha is what we want
    c1 = Color(10, 50, 100, 90);
    c2 = Color(30, 100, 200, 110);
    EXPECT_EQ(Color(33, 117, 235, 110), c2 + c1);
    EXPECT_EQ(Color(22, 93, 186, 90), c1 + c2);
}

TEST(Color, Multiply)
{
    Color c1;
    Color c2;

    c1 = Color(0, 0, 0, 255);
    c2 = Color(100, 200, 255, 255);
    EXPECT_EQ(Color(0, 0, 0, 255), c1 * c2);

    c1 = Color(32, 64, 128, 255);
    c2 = Color(80, 100, 200, 255);
    EXPECT_EQ(Color(10, 25, 100, 255), c1 * c2);

    c1 = Color(255, 255, 255, 255);
    c2 = Color(255, 255, 255, 255);
    EXPECT_EQ(Color(255, 255, 255, 255), c1 * c2);

    c1 = Color(10, 50, 100, 90);
    c2 = Color(30, 100, 200, 110);
    EXPECT_EQ(Color(1, 19, 78, 38), c2 * c1);
}

TEST(Color, Invert)
{
    Color color(25, 50, 75);
    color.invert();
    EXPECT_EQ(Color(250, 205, 180), color);
}

TEST(Color, Archive)
{
    Color color(0x56, 0x78, 0x9A, 0xBC);
    Color archived = test::archive(color);
    EXPECT_EQ(color, archived);
}

TEST(Color, Stdout)
{
    Color color(0x56, 0x78, 0x9A, 0xBC);
    EXPECT_EQ(test::stdout(color), "r=86, g=120, b=154, a=188");
}
}
}

NYRA_TEST()
