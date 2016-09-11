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
#include <nyra/math/Transform2D.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Transform2D, Construction)
{
    const Transform2D transform;
    EXPECT_EQ(Vector2F(0.0f, 0.0f), transform.getPosition());
    EXPECT_EQ(Vector2F(1.0f, 1.0f), transform.getScale());
    EXPECT_EQ(Vector2F(0.0f, 0.0f), transform.getSize());
    EXPECT_EQ(Vector2F(0.5f, 0.5f), transform.getPivot());
    EXPECT_EQ(0.0f, transform.getRotation());
}

TEST(Transform2D, GetSet)
{
    Transform2D transform;
    const Vector2F position(100.0f, 200.0f);
    transform.setPosition(position);
    EXPECT_EQ(position, transform.getPosition());
    transform.moveBy(position);
    EXPECT_EQ(position + position, transform.getPosition());

    const Vector2F scale(2.0f, 3.0f);
    transform.setScale(scale);
    EXPECT_EQ(scale, transform.getScale());
    transform.scaleBy(scale);
    EXPECT_EQ(Vector2F(4.0f, 9.0f), transform.getScale());
    transform.setScale(Vector2F(1.0f, 1.0f));
    transform.setScale(2.0f);
    EXPECT_EQ(Vector2F(2.0f, 2.0f), transform.getScale());
    transform.scaleBy(2.0f);
    EXPECT_EQ(Vector2F(4.0f, 4.0f), transform.getScale());

    const Vector2F size(256.0f, 512.0f);
    transform.setSize(size);
    EXPECT_EQ(size, transform.getSize());

    const Vector2F pivot(0.75f, 0.25f);
    transform.setPivot(pivot);
    EXPECT_EQ(pivot, transform.getPivot());

    const float rotation = 45.0f;
    transform.setRotation(rotation);
    EXPECT_EQ(rotation, transform.getRotation());
    transform.rotateBy(rotation);
    EXPECT_EQ(90.0f, transform.getRotation());
}

TEST(Transform2D, Matrix)
{
    const Transform2D identity;
    Transform2D transform;

    // From the matrix test. Make sure nothing broke when this went into
    // the transform class.
    transform.setPosition(Vector2F(5.0f, 6.0f));
    transform.setScale(Vector2F(2.0f, 3.0f));
    transform.setRotation(180.0f);
    transform.setSize(Vector2F(10.0f, 20.0f));
    transform.setPivot(Vector2F(1.0f, 1.0f));
    transform.update(identity);
    Matrix3x3 results = transform.getMatrix();
    Matrix3x3 expected(-2.0f, 0.0f,  -15.0f,
                       0.0f,  -3.0f, -54.0f,
                       0.0f,  0.0f,  1.0f);
    EXPECT_EQ(expected, results);

    const Transform2D copied = transform;
    transform.update(copied);
    results = transform.getMatrix();

    // This should equal something crazy. Just make sure that the results
    // changed after adding a parent transform.
    EXPECT_NE(expected, results);
}
}
}

NYRA_TEST()
