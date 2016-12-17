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
#include <nyra/graphics/MarchingCubes.h>
#include <nyra/graphics/MarchingCubeTables.h>
#include <nyra/math/Interpolate.h>

namespace
{
//===========================================================================//
nyra::math::Vector3F interp(float isoLevel,
                            const nyra::math::Vector3F& p1,
                            const nyra::math::Vector3F& p2,
                            float value1,
                            float value2)
{
    // TODO: Get the holes fixed, then look at adding this back in.
    /*if (std::abs(isoLevel - value1) < 0.00001f)
    {
        return p1;
    }

    if (std::abs(isoLevel - value2) < 0.00001f)
    {
        return p2;
    }

    if (std::abs(value1 - value2) < 0.00001f)
    {
        return p1;
    }*/

    const float delta = (isoLevel - value1) / (value2 - value1);

    // TODO: math::linearInterpolate gave the wrong answer here.
    //       Need to investigate why.
    //return nyra::math::linearInterpolate(p1, p2, delta);
    return nyra::math::Vector3F(
            p1.x() + delta * (p2.x() - p1.x()),
            p1.y() + delta * (p2.y() - p1.y()),
            p1.z() + delta * (p2.z() - p1.z()));
}
}

namespace nyra
{
namespace graphics
{
//===========================================================================//
const std::vector<math::Vector3F>& MarchingCubes::operator()(
        float extents, float cubeSize, float isoLevel)
{
    mVerts.clear();
    std::vector<math::Vector3F> cube(8);

    const float halfExtents = extents / 2.0f;
    for (float x = -halfExtents; x < halfExtents; x += cubeSize)
    {
        for (float y = -halfExtents; y < halfExtents; y += cubeSize)
        {
            for (float z = -halfExtents; z < halfExtents; z += cubeSize)
            {
                cube[0] = math::Vector3F(x,            y,            z+ cubeSize);
                cube[1] = math::Vector3F(x + cubeSize, y,            z+ cubeSize);
                cube[2] = math::Vector3F(x + cubeSize, y,            z );
                cube[3] = math::Vector3F(x,            y,            z );
                cube[4] = math::Vector3F(x,            y + cubeSize, z+ cubeSize);
                cube[5] = math::Vector3F(x + cubeSize, y + cubeSize, z+ cubeSize);
                cube[6] = math::Vector3F(x + cubeSize, y + cubeSize, z );
                cube[7] = math::Vector3F(x,            y + cubeSize, z );

                march(cube, isoLevel);
            }
        }
    }

    return mVerts;
}

//===========================================================================//
void MarchingCubes::march(
            const std::vector<math::Vector3F>& cube,
            float isoLevel)
{
    std::vector<float> values(8);

    // Determine the index into the edge table which
    // tells us which vertices are inside of the surface
    uint8_t cubeIndex = 0;
    for (size_t ii = 0; ii < 8; ++ii)
    {
        values[ii] = xyzFunction(cube[ii]);
        if (values[ii] < isoLevel)
        {
            cubeIndex |= (1 << ii);
        }
    }

    // Cube is entirely in/out of the surface
    if (EDGE_TABLE[cubeIndex] == 0)
    {
        return;
    }

    std::vector<math::Vector3F> verts(12);

    // Find the vertices where the surface intersects the cube
    if (EDGE_TABLE[cubeIndex] & 1)
    {
        verts[0] = interp(isoLevel, cube[0], cube[1], values[0], values[1]);
    }
    if (EDGE_TABLE[cubeIndex] & 2)
    {
        verts[1] = interp(isoLevel, cube[1], cube[2], values[1], values[2]);
    }
    if (EDGE_TABLE[cubeIndex] & 4)
    {
        verts[2] = interp(isoLevel, cube[2], cube[3], values[2], values[3]);
    }
    if (EDGE_TABLE[cubeIndex] & 8)
    {
        verts[3] = interp(isoLevel, cube[3], cube[0], values[3], values[0]);
    }
    if (EDGE_TABLE[cubeIndex] & 16)
    {
        verts[4] = interp(isoLevel, cube[4], cube[5], values[4], values[5]);
    }
    if (EDGE_TABLE[cubeIndex] & 32)
    {
        verts[5] = interp(isoLevel, cube[5], cube[6], values[5], values[6]);
    }
    if (EDGE_TABLE[cubeIndex] & 64)
    {
        verts[6] = interp(isoLevel, cube[6], cube[7], values[6], values[7]);
    }
    if (EDGE_TABLE[cubeIndex] & 128)
    {
        verts[7] = interp(isoLevel, cube[7], cube[4], values[7], values[4]);
    }
    if (EDGE_TABLE[cubeIndex] & 256)
    {
        verts[8] = interp(isoLevel, cube[0], cube[4], values[0], values[4]);
    }
    if (EDGE_TABLE[cubeIndex] & 512)
    {
        verts[9] = interp(isoLevel, cube[1], cube[5], values[1], values[5]);
    }
    if (EDGE_TABLE[cubeIndex] & 1024)
    {
        verts[10] = interp(isoLevel, cube[2], cube[6], values[2], values[6]);
    }
    if (EDGE_TABLE[cubeIndex] & 2048)
    {
        verts[11] = interp(isoLevel, cube[3], cube[7], values[3], values[7]);
    }

    // Create the triangle
    for (size_t ii = 0; TRIANGLE_TABLE[cubeIndex][ii] != -1; ii += 3)
    {
        mVerts.push_back(verts[TRIANGLE_TABLE[cubeIndex][ii]]);
        mVerts.push_back(verts[TRIANGLE_TABLE[cubeIndex][ii + 1]]);
        mVerts.push_back(verts[TRIANGLE_TABLE[cubeIndex][ii + 2]]);
   }
}
}
}
