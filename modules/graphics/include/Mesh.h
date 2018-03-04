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
#ifndef __NYRA_GRAPHICS_MESH_H__
#define __NYRA_GRAPHICS_MESH_H__

#include <nyra/graphics/Renderable.h>
#include <nyra/math/Transform.h>
#include <nyra/math/Vector3.h>
#include <vector>
#include <string>

namespace nyra
{
namespace graphics
{
/*
 *  \class Mesh
 *  \brief A class that represents a 3D model.
 */
class Mesh : public Renderable<math::Transform3D>
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    virtual ~Mesh() = default;

    /*
     *  \func initialize
     *  \brief Loads a mesh from a file.
     *
     *  \param pathname The pathname of the file on disk.
     */
    virtual void initialize(const std::string& pathname) = 0;

    /*
     *  \func initialize
     *  \brief Loads a mesh from vert and indice buffers in memory.
     *
     *  \param vertices A list of vertices.
     *  \param indices A list of indices into the vertex buffer.
     */
    virtual void initialize(const std::vector<math::Vector3F>& vertices,
                            const std::vector<size_t>& indices) = 0;
};
}
}

#endif
