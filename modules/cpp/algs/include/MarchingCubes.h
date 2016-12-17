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
#ifndef __NYRA_ALGS_MARCHING_CUBES_H__
#define __NYRA_ALGS_MARCHING_CUBES_H__

#include <vector>
#include <nyra/math/Vector3.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace algs
{
/*
 *  \class MarchingCubes
 *  \brief Runs the marching cubes algorithm to generate a procedural mesh.
 */
class MarchingCubes
{
public:
    /*
     *  \func Functor
     *  \brief Generates the marching cube mesh.
     *
     *  \param extents The size of the cube to generate the mesh in. This
     *         is specified in generic units. The value here is the length
     *         of the cube.
     *  \param cubeSize The size of each cube used to generate vertices. If
     *         this is a smaller number, you will get a finer mesh. The value
     *         is the length of the cube.
     *  \param isoLevel The desired evaluation criteria for the xyzFunction.
     *         Changing this will have unique effects on each function
     *         type. For example, a sphere function will scale through
     *         changing this value.
     */
    const std::vector<math::Vector3F>& operator()(float extents,
                                                  float cubeSize,
                                                  float isoLevel = 1.0f);

    /*
     *  \var xyzFunction
     *  \brief The function used to generate the mesh. For example:
     *         x^2 + y^2 + z^2 will generate a sphere.
     */
    core::Event<float(const math::Vector3F& point)> xyzFunction;

private:
    void march(const std::vector<math::Vector3F>& cube,
               float isoLevel);

    std::vector<math::Vector3F> mVerts;
};
}
}

#endif
