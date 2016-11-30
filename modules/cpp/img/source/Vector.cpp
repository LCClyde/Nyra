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
#include <nyra/img/Vector.h>
#include <iostream>

namespace nyra
{
namespace img
{
//===========================================================================//
Vector::Vector(const math::Vector2U& size) :
    mSize(size),
    mStride(cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.x())),
    mPixels(new unsigned char[mStride * size.y()]),
    mSurface(cairo_image_surface_create_for_data(
            mPixels.get(), CAIRO_FORMAT_ARGB32, size.x(), size.y(), mStride)),
    mCairo(cairo_create(mSurface))
{
    // Clear out the buffer
    memset(mPixels.get(), 0, mStride * size.y());
}

//============================================================================//
Vector::~Vector()
{
    cairo_destroy(mCairo);
    cairo_surface_destroy(mSurface);
}

//============================================================================//
img::Image Vector::getImage() const
{
    return Image(mPixels.get(), mSize, Image::BGRA);
}

//============================================================================//
void Vector::draw(const std::vector<BlobInstruction>& blob,
                  const math::Vector2F& position,
                  const Color& fill,
                  const Color& stroke)
{
    // We need at least three points to make anything
    if (blob.size() < 3)
    {
        throw std::runtime_error(
                "Blob cannot be drawn. It only contains: " +
                std::to_string(blob.size()) + " points.");
    }

    // Make sure the first point is a start position
    if (blob[0].type != BlobInstruction::START)
    {
        throw std::runtime_error(
                "The first instruction in a blob must"
                " be a START instruction.");
    }

    cairo_move_to(mCairo,
                  position.x() + blob[0].point.x(),
                  position.y() + blob[0].point.y());

    // Draw all the other elements
    for (size_t ii = 1; ii < blob.size(); ++ii)
    {
        switch (blob[ii].type)
        {
        case BlobInstruction::START:
            throw "Invalid START instruction in blob.";
            break;

        case BlobInstruction::LINE:
            cairo_line_to(mCairo,
                          position.x() + blob[ii].point.x(),
                          position.y() + blob[ii].point.y());
            break;

        case BlobInstruction::CURVE:
            cairo_curve_to(mCairo,
                           position.x() + blob[ii].bezier1.x(),
                           position.y() + blob[ii].bezier1.y(),
                           position.x() + blob[ii].bezier2.x(),
                           position.y() + blob[ii].bezier2.y(),
                           position.x() + blob[ii].point.x(),
                           position.y() + blob[ii].point.y());
            break;
        };
    }

    // close the blob
    cairo_close_path(mCairo);

    // Apply the fill
    cairo_set_source_rgba(mCairo,
                          fill.r / 255.0,
                          fill.g / 255.0,
                          fill.b / 255.0,
                          fill.a / 255.0);
    cairo_fill_preserve(mCairo);

    // Apply the stroke
    cairo_set_source_rgba(mCairo,
                          stroke.r / 255.0,
                          stroke.g / 255.0,
                          stroke.b / 255.0,
                          stroke.a / 255.0);
    cairo_stroke(mCairo);

}
}
}

