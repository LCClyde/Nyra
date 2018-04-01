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
#include <nyra/algs/MarchingCubes.h>

namespace nyra
{
namespace algs
{

TEST(MarchingCubes, UnitSphere)
{
    MarchingCubes cubes;

    cubes.xyzFunction = [](const math::Vector3F& p)->float
    {
        return ((p.x * p.x) + (p.y * p.y) + (p.z * p.z));
    };

    const std::vector<math::Vector3F>& vertices = cubes(2.5f, 0.1f);

    for (const auto& vert : vertices)
    {
        // All verts should be close to 1.0f
        EXPECT_NEAR(1.0f, vert.length(), 0.01f);
    }
}

TEST(MarchingCubes, Ellipse)
{
    MarchingCubes cubes;

    cubes.xyzFunction = [](const math::Vector3F& p)->float
    {
        const float x = p.x * p.x / std::pow(5.0, 2);
        const float y = p.y * p.y / std::pow(7.0, 2);
        const float z = p.z * p.z / std::pow(11.0, 2);
        return x + y + z;
    };

    const std::vector<math::Vector3F>& vertices = cubes(25.0f, 0.5f);

    float xMin = 100.0f;
    float xMax = -100.0f;
    float yMin = 100.0f;
    float yMax = -100.0f;
    float zMin = 100.0f;
    float zMax = -100.0f;
    for (const auto& vert : vertices)
    {
        xMin = std::min(xMin, vert.x);
        xMax = std::max(xMax, vert.x);
        yMin = std::min(yMin, vert.y);
        yMax = std::max(yMax, vert.y);
        zMin = std::min(zMin, vert.z);
        zMax = std::max(zMax, vert.z);
    }

    EXPECT_NEAR(-5.0f, xMin, 0.01f);
    EXPECT_NEAR(5.0f, xMax, 0.01f);
    EXPECT_NEAR(-7.0f, yMin, 0.01f);
    EXPECT_NEAR(7.0f, yMax, 0.01f);
    EXPECT_NEAR(-11.0f, zMin, 0.01f);
    EXPECT_NEAR(11.0f, zMax, 0.01f);
}
}
}

NYRA_TEST()
