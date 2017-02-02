/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_GRAPHICS_FBX_H__
#define __NYRA_GRAPHICS_FBX_H__

#include <string>
#include <nyra/math/Vector3.h>
#include <nyra/xml/XML.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class Collada
 *  \brief Class for reading and parsing Collada (.dae) 3D model files.
 */
class Collada
{
public:
    /*
     *  \func Constructor
     *  \brief Reads and parses the file.
     *
     *  \param pathname The Collada file on disk.
     */
    Collada(const std::string& pathname);

    /*
     *  \func getVertices
     *  \brief Gets the list of vertices
     *
     *  \return The vertices
     */
    const std::vector<math::Vector3F>& getVertices() const
    {
        return mVerts;
    }

    /*
     *  \func getIndices
     *  \brief Gets the list of indices
     *
     *  \return The indices
     */
    const std::vector<size_t>& getIndices() const
    {
        return mIndices;
    }

private:
    void initializeVerts(const mem::Tree<xml::Element>& tree);


    std::vector<math::Vector3F> mVerts;
    std::vector<size_t> mIndices;
};
}
}

#endif
