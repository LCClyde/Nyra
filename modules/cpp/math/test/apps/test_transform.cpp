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
#include <nyra/math/Transform.h>
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
    transform.updateTransform(identity);
    Matrix3x3 results = transform.getMatrix();
    Matrix3x3 expected(-2.0f, 0.0f,  25.0f,
                       0.0f,  -3.0f, 66.0f,
                       0.0f,  0.0f,  1.0f);
    EXPECT_EQ(expected, results);

    const Transform2D copied = transform;
    transform.updateTransform(copied);
    results = transform.getMatrix();

    // This should equal something crazy. Just make sure that the results
    // changed after adding a parent transform.
    EXPECT_NE(expected, results);
}

TEST(Transform2D, ScaledSize)
{
    Transform2D transform;
    transform.setSize(Vector2F(10.0f, 20.0f));
    transform.setScale(Vector2F(2.0f, 3.0f));
    EXPECT_EQ(math::Vector2F(20.0f, 60.0f), transform.getScaledSize());
}

TEST(Transform3D, Construction)
{
    const Transform3D transform;
    EXPECT_EQ(Vector3F(0.0f, 0.0f, 0.0f), transform.getPosition());
    EXPECT_EQ(Vector3F(1.0f, 1.0f, 1.0f), transform.getScale());
    EXPECT_EQ(Vector3F(0.0f, 0.0f, 0.0f), transform.getSize());
    EXPECT_EQ(Vector3F(0.5f, 0.5f, 0.5f), transform.getPivot());
    EXPECT_EQ(Vector3F(0.0f, 0.0f, 0.0f), transform.getRotation());
}

TEST(Transform3D, GetSet)
{
    Transform3D transform;
    const Vector3F position(100.0f, 200.0f, 300.0f);
    transform.setPosition(position);
    EXPECT_EQ(position, transform.getPosition());
    transform.moveBy(position);
    EXPECT_EQ(position + position, transform.getPosition());

    const Vector3F scale(2.0f, 3.0f, 4.0f);
    transform.setScale(scale);
    EXPECT_EQ(scale, transform.getScale());
    transform.scaleBy(scale);
    EXPECT_EQ(Vector3F(4.0f, 9.0f, 16.0f), transform.getScale());
    transform.setScale(Vector3F(1.0f, 1.0f, 1.0f));
    transform.setScale(2.0f);
    EXPECT_EQ(Vector3F(2.0f, 2.0f, 2.0f), transform.getScale());
    transform.scaleBy(2.0f);
    EXPECT_EQ(Vector3F(4.0f, 4.0f, 4.0f), transform.getScale());

    const Vector3F size(256.0f, 512.0f, 128.0f);
    transform.setSize(size);
    EXPECT_EQ(size, transform.getSize());

    const Vector3F pivot(0.75f, 0.25f, 0.5f);
    transform.setPivot(pivot);
    EXPECT_EQ(pivot, transform.getPivot());

    const Vector3F rotation = Vector3F(45.0f, 25.0f, 30.0f);
    transform.setRotation(rotation);
    EXPECT_EQ(rotation, transform.getRotation());
    transform.rotateBy(rotation);
    EXPECT_EQ(Vector3F(90.0f, 50.0f, 60.0f), transform.getRotation());
}

TEST(Transform3D, Matrix)
{
    const Transform3D identity;
    Transform3D transform;

    // From the matrix test. Make sure nothing broke when this went into
    // the transform class.
    transform.setPosition(Vector3F(5.0f, 6.0f, 7.0f));
    transform.setScale(Vector3F(2.0f, 3.0f, 4.0f));
    transform.setRotation(Vector3F(180.0f, 15.0f, 45.0f));
    transform.setSize(Vector3F(10.0f, 20.0f, 30.0f));
    transform.setPivot(Vector3F(1.0f, 1.0f, 1.0f));
    transform.updateTransform(identity);
    Matrix4x4 results = transform.getMatrix();
    EXPECT_NE(Matrix4x4(), results);

    const Transform3D copied = transform;
    transform.updateTransform(copied);
    Matrix4x4 updatedResults = transform.getMatrix();

    // This should equal something crazy. Just make sure that the results
    // changed after adding a parent transform.
    EXPECT_NE(updatedResults, results);
}

TEST(Transform3D, ScaledSize)
{
    Transform3D transform;
    transform.setSize(Vector3F(10.0f, 20.0f, 30.0f));
    transform.setScale(Vector3F(2.0f, 3.0f, 0.5f));
    EXPECT_EQ(math::Vector3F(20.0f, 60.0f, 15.0f), transform.getScaledSize());
}
}
}

NYRA_TEST()
