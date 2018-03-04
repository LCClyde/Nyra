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
#ifndef __NYRA_GRAPHICS_OGRE_MESH_H__
#define __NYRA_GRAPHICS_OGRE_MESH_H__

#include <OGRE/OgreManualObject.h>
#include <nyra/graphics/Mesh.h>
#include <nyra/ogre/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
/*
 *  \class Mesh
 *  \brief A class that represents a 3D model.
 */
class Mesh : public graphics::Mesh,
        private mem::GlobalDependency<nyra::ogre::GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Initializes a Mesh
     *
     *  \param vertices A list of vertices.
     *  \param indices A list of indices into the vertex buffer.
     */
    Mesh(const std::vector<math::Vector3F>& vertices,
         const std::vector<size_t>& indices);

    /*
     *  \func Destructor
     *  \brief Removes the mesh from the SceneManager.
     */
    ~Mesh();

    /*
     *  \func initialize
     *  \brief Loads a mesh from a file.
     *
     *  \param pathname The pathname of the file on disk.
     */
    void initialize(const std::string& pathname);

    /*
     *  \func initialize
     *  \brief Loads a mesh from vert and indice buffers in memory.
     *
     *  \param vertices A list of vertices.
     *  \param indices A list of indices into the vertex buffer.
     */
    void initialize(const std::vector<math::Vector3F>& vertices,
                    const std::vector<size_t>& indices);
    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param transform The transform that represents this object
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target);

private:
    Ogre::ManualObject* mMesh;
};
}
}
}

#endif
