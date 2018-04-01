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
#include <nyra/graphics/gl/Mesh.h>

namespace nyra
{
namespace graphics
{
namespace gl
{
//===========================================================================//
Mesh::Mesh(const std::vector<math::Vector3F>& vertices,
           const std::vector<size_t>& indices) :
    mShader("", ""),
    mVectorBufferObject(0),
    mVectorArrayObject(0),
    mElementBufferObject(0)
{
    initialize(vertices, indices);
}

//===========================================================================//
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &mVectorArrayObject);
    glDeleteBuffers(1, &mVectorBufferObject);
    glDeleteBuffers(1, &mElementBufferObject);
}

//===========================================================================//
void Mesh::initialize(const std::string& pathname)
{
}

//===========================================================================//
void Mesh::initialize(const std::vector<math::Vector3F>& vertices,
                      const std::vector<size_t>& indices)
{
    std::vector<GLfloat> glVerts(vertices.size() * 3);
    for (size_t ii = 0, jj = 0; ii < vertices.size(); ++ii, jj += 3)
    {
        glVerts[jj] = vertices[ii].x;
        glVerts[jj + 1] = vertices[ii].y;
        glVerts[jj + 2] = vertices[ii].z;
    }

    std::vector<GLuint> glIndices(indices.size());
    for (size_t ii = 0; ii < indices.size(); ++ii)
    {
        glIndices[ii] = indices[ii];
    }

    glGenVertexArrays(1, &mVectorArrayObject);
    glGenBuffers(1, &mVectorBufferObject);
    glGenBuffers(1, &mElementBufferObject);

    // Bind the Vertex Array Object first, then bind and
    // set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(mVectorArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, mVectorBufferObject);
    glBufferData(GL_ARRAY_BUFFER, glVerts.size() * sizeof(GLfloat),
                 glVerts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, glIndices.size() * sizeof(GLuint),
                 glIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mNumVerts = indices.size();
}

//===========================================================================//
void Mesh::render(RenderTarget& target)
{
    glUseProgram(mShader.getNative());
    glBindVertexArray(mVectorArrayObject);
    glDrawElements(GL_TRIANGLES, mNumVerts, GL_UNSIGNED_INT, 0);
    glScalef(0.01f, 0.01f, 0.01f);
    glBindVertexArray(0);
}
}
}
}
