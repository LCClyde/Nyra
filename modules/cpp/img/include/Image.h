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
#ifndef __NYRA_IMG_IMAGE_H__
#define __NYRA_IMG_IMAGE_H__

#include <nyra/img/Color.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace img
{
/*
 *  \class Image
 *  \brief Class to hold onto image information. Serialization of this
 *         class is done through png files.
 */
class Image
{
public:
    /*
     *  \type Format
     *  \brief The Pixel format of the image
     */
    enum Format
    {
        RGBA,
        ARGB,
        BGRA,
        RGB,
        BGR
    };

    /*
     *  \func Constructor
     *  \brief Creates an empty image
     */
    Image() = default;

    /*
     *  \func Constructor
     *  \brief Creates an image from pixels
     *
     *  \param pixels Pixels in RGBA format.
     *  \param size The size of the image.
     *  \param format The format of the incoming pixels
     */
    Image(const uint8_t* pixels,
          const math::Vector2U& size,
          Format format = RGBA);

    /*
     *  \func Constructor
     *  \brief Creates a blank image from at a certain size
     *
     *  \param size The size of the image
     */
    Image(const math::Vector2U& size);

    /*
     *  \func resize
     *  \brief Resizes an image. The contents are not update and should be
     *         considered invalid after resizing.
     *
     *  \param size The desired size of the image
     */
    inline void resize(const math::Vector2U& size)
    {
        mSize = size;
        mPixels.resize(mSize.product());
    }

    /*
     *  \func setSize
     *  \brief Same as resize. This is to make the interface similar to other
     *         classes in Nyra.
     *
     *  \param size The desired size of the image.
     */
    inline void setSize(const math::Vector2U& size)
    {
        resize(size);
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the image
     *
     *  \return The size where x is rows and y is columns
     */
    inline const math::Vector2U& getSize() const
    {
        return mSize;
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param index The 1D index into the image
     *  \return The pixel value
     */
    inline const Color& operator()(size_t index) const
    {
        return mPixels[index];
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param index The 1D index into the image
     *  \return The pixel value
     */
    inline Color& operator()(size_t index)
    {
        return mPixels[index];
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param row The row of the pixel
     *  \param col The column the pixel
     *  \return The pixel value
     */
    inline const Color& operator()(size_t row, size_t col) const
    {
        return mPixels[row * mSize.x() + col];
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param row The row of the pixel
     *  \param col The column the pixel
     *  \return The pixel value
     */
    Color& operator()(size_t row, size_t col)
    {
        return mPixels[row * mSize.x() + col];
    }

    /*
     *  \func Equal
     *  \brief Checks if two images are equal
     *
     *  \param other The image to check against.
     *  \return true if the images are the same
     */
    bool operator==(const Image& other) const;

    /*
     *  \func Not Equal
     *  \brief Checks if two images are not equal
     *
     *  \param other The image to check against
     *  \return true if the images are not equal
     */
    bool operator!=(const Image& other) const
    {
        return !((*this) == other);
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Image& image);

    math::Vector2U mSize;
    std::vector<Color> mPixels;
};
}

namespace core
{
/*
 *  \func writeArchive
 *  \brief Writes an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param image The image to save
 *  \param pathname The location to save to.
 */
template <>
void writeArchive<img::Image>(const img::Image& image,
                              const std::string& pathname);

/*
 *  \func readArchive
 *  \brief Reads an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param pathname The location to save to.
 *  \param image The image to load
 */
template <>
void readArchive<img::Image>(const std::string& pathname,
                             img::Image& image);
}
}

#endif
