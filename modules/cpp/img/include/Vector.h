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
#ifndef __NYRA_IMG_VECTOR_H__
#define __NYRA_IMG_VECTOR_H__

#include <memory>
#include <cairo.h>
#include <nyra/img/Image.h>
#include <nyra/math/Vector.h>
#include <nyra/img/BlobInstruction.h>

namespace nyra
{
namespace img
{
/*
 *  \class Vector
 *  \brief Class for Vector art images.
 */
class Vector
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up an empty (all alpha image)
     *
     *  \param size The size of the image in pixels.
     */
    Vector(const math::Vector2U& size);

    /*
     *  \func Destructor
     *  \brief Destroys the Cairo objects.
     */
    ~Vector();

    /*
     *  \func draw
     *  \brief Draws a blob to the image
     *
     *  \param blob The object to draw.
     */
    void draw(const std::vector<BlobInstruction>& blob,
              const math::Vector2F& position,
              const Color& fill,
              const Color& stroke);

    /*
     *  \func getImage
     *  \brief Gets the RGBA image from the svg.
     *
     *  \return The RGBA image.
     */
    img::Image getImage() const;

private:
    const math::Vector2U mSize;
    const size_t mStride;
    std::unique_ptr<unsigned char[]> mPixels;
    cairo_surface_t* mSurface;
    cairo_t* mCairo;
};
}
}

#endif
