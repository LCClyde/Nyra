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
#include <nyra/graphics/ogre/Mesh.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
//===========================================================================//
Mesh::Mesh(const std::vector<math::Vector3F>& vertices,
           const std::vector<size_t>& indices)
{
    initialize(vertices, indices);
}

//===========================================================================//
Mesh::~Mesh()
{
    getGlobalInstance().getSceneManager()->destroyManualObject(mMesh);
}

//===========================================================================//
void Mesh::initialize(const std::string& pathname)
{
    throw std::runtime_error("Load mesh from file is unimplemented");
}

//===========================================================================//
void Mesh::initialize(const std::vector<math::Vector3F>& vertices,
                      const std::vector<size_t>& indices)
{
    // create ManualObject
    mMesh = getGlobalInstance().getSceneManager()->
            createManualObject("manual");

    // specify the material (by name) and rendering type
    mMesh->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);

    // define start and end point
    for (const auto& vert : vertices)
    {
        mMesh->position(vert.x, vert.y, vert.z);
    }

    for (const auto& index : indices)
    {
        mMesh->index(index);
    }

    // tell Ogre, your definition has finished
    mMesh->end();

    // add ManualObject to the RootSceneNode (so it will be visible)
    getGlobalInstance().getSceneManager()->
            getRootSceneNode()->attachObject(mMesh);
}

//===========================================================================//
void Mesh::render(graphics::RenderTarget& target)
{
    // No-Op
}
}
}
}

