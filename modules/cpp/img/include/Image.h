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
#include <opencv2/opencv.hpp>

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
    Image();

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
     *  \func Constuctor
     *  \brief Creates an image from a functor that can supply
     *         a value from an x, y coordinate.
     *
     *  \param functor The functor object that supplies the information
     *  \param size The size of the final image
     *  \param min The min value returned from the functor
     *  \param max The max value returned from the functor
     */
    template <typename T>
    Image(const T& functor,
          const math::Vector2U& size,
          double min,
          double max)
    {
        resize(size);
        const double diff = max - min;

        for (size_t y = 0; y < size.y; ++y)
        {
            const size_t idx = y * size.x;
            for (size_t x = 0; x < size.x; ++x)
            {
                const uint8_t pixel = (functor(x, y) - min) / diff * 255;
                (*this)(idx + x) = Color(pixel, pixel, pixel, 255);
            }
        }
    }

    /*
     *  \func resize
     *  \brief Resizes an image. The contents are not update and should be
     *         considered invalid after resizing.
     *
     *  \param size The desired size of the image
     */
    void resize(const math::Vector2U& size);

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
    math::Vector2U getSize() const
    {
        return math::Vector2U(mMatrix.cols, mMatrix.rows);
    }

    /*
     *  \func Assignment
     *  \brief Sets the image to a single color
     *
     *  \param color The desired color
     *  \return The image object
     */
    Image& operator=(const Color& color);

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param index The 1D index into the image
     *  \return The pixel value
     */
    Color operator()(size_t index) const
    {
        const auto pix = mMatrix.at<cv::Vec4b>(index);
        return Color(pix[2], pix[1], pix[0], pix[3]);
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
    Color operator()(size_t index)
    {
        return Color(mMatrix.at<cv::Vec4b>(index));
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param x The column the pixel
     *  \param y The row of the pixel
     *  \return The pixel value
     */
    Color operator()(size_t x, size_t y) const
    {
        const auto pix = mMatrix.at<cv::Vec4b>(y, x);
        return Color(pix[2], pix[1], pix[0], pix[3]);
    }

    /*
     *  \func Functor
     *  \brief Gets a single pixel from the image. This purposely does not
     *         check the size for speed. It is the users responsibility to
     *         ensure the index is in range.
     *
     *  \param x The column the pixel
     *  \param y The row of the pixel
     *  \return The pixel value
     */
    Color operator()(size_t x, size_t y)
    {
        return Color(mMatrix.at<cv::Vec4b>(y, x));
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

    /*
     *  \func Addition Assignment Operator
     *  \brief Adds two images
     *
     *  \param other The image to add.
     *  \return The sum of the two images
     */
    Image& operator+=(const Image& other);

    /*
     *  \func Addition Operator
     *  \brief Adds two images
     *
     *  \param other The image to add.
     *  \return The sum of the two images
     */
    Image operator+(const Image& other) const
    {
        Image result(*this);
        result += other;
        return result;
    }

    /*
     *  \func Multiply Assignment Operator
     *  \brief Multiplies two images
     *
     *  \param other The image to multiply by.
     *  \return The product of the two images
     */
    Image& operator*=(const Image& other);

    /*
     *  \func Multiply Operator
     *  \brief Multiplies two images
     *
     *  \param other The image to multiply by.
     *  \return The product of the two images
     */
    Image operator*(Image other) const
    {
        other *= (*this);
        return other;
    }

    /*
     *  \func getNative
     *  \brief Returns the underlying OpenCV matrix.
     *
     *  \return The native image object
     */
    cv::Mat& getNative()
    {
        return mMatrix;
    }


    /*
     *  \func getNative
     *  \brief Returns the underlying OpenCV matrix.
     *
     *  \return The native image object
     */
    const cv::Mat& getNative() const
    {
        return mMatrix;
    }

private:
    void testSized(const Image& other, const std::string& op) const;

    friend std::ostream& operator<<(std::ostream& os, const Image& image);

    cv::Mat mMatrix;
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param image The image to save
 *  \param pathname The location to save to.
 *  \param type This will only write binary, even if you select something
 *         else
 */
template <>
void write<img::Image>(const img::Image& image,
                       const std::string& pathname,
                       core::ArchiveType type);

/*
 *  \func read
 *  \brief Reads an image to file. This overrides the traditional calls to
 *         serialize to specialize this for png files.
 *
 *  \param pathname The location to save to.
 *  \param image The image to load
 *  \param type This will only read binary, even if you select something
 *         else
 */
template <>
void read<img::Image>(const std::string& pathname,
                      img::Image& image,
                      core::ArchiveType type);
}
}

#endif
