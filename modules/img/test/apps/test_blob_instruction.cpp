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
#include <nyra/img/BlobInstruction.h>

namespace nyra
{
namespace img
{
TEST(BlobInstruction, Start)
{
    const math::Vector2F startPoint(256.0f, 128.0f);
    const BlobInstruction start(createBlobStart(startPoint));
    EXPECT_EQ(startPoint, start.point);
    EXPECT_EQ(BlobInstruction::START, start.type);
}

TEST(BlobInstruction, Line)
{
    const math::Vector2F linePoint(128.0f, 64.0f);
    const BlobInstruction line(createBlobLine(linePoint));
    EXPECT_EQ(linePoint, line.point);
    EXPECT_EQ(BlobInstruction::LINE, line.type);
}

TEST(BlobInstruction, Curve)
{
    const math::Vector2F curvePoint(64.0f, 256.0f);
    const math::Vector2F bezier1(128.0f, 32.0f);
    const math::Vector2F bezier2(256.0f, 128.0f);
    const BlobInstruction curve(createBlobCurve(curvePoint, bezier1, bezier2));
    EXPECT_EQ(curvePoint, curve.point);
    EXPECT_EQ(bezier1, curve.bezier1);
    EXPECT_EQ(bezier2, curve.bezier2);
    EXPECT_EQ(BlobInstruction::CURVE, curve.type);
}
}
}

NYRA_TEST()
