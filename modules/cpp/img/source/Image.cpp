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
#include <nyra/img/Image.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace img
{
//===========================================================================//
Image::Image(const uint8_t* pixels,
             const math::Vector2U& size,
             Format format)
{
resize(size);
    switch (format)
    {
    case RGBA:
    {
        for (size_t ii = 0, jj = 0; ii < size.product(); ++ii, jj += 4)
        {
            (*this)(ii) = Color(pixels[jj],
                                pixels[jj + 1],
                                pixels[jj + 2],
                                pixels[jj + 3]);
        }
        break;
    }

    case ARGB:
        for (size_t ii = 0, jj = 0; ii < size.product(); ++ii, jj += 4)
        {
            (*this)(ii) = Color(pixels[jj + 1],
                                pixels[jj + 2],
                                pixels[jj + 3],
                                pixels[jj]);
        }
        break;

    case BGRA:
        for (size_t ii = 0, jj = 0; ii < size.product(); ++ii, jj += 4)
        {
            (*this)(ii) = Color(pixels[jj + 2],
                                pixels[jj + 1],
                                pixels[jj],
                                pixels[jj + 3]);
        }
        break;

    case RGB:
        for (size_t ii = 0, jj = 0; ii < size.product(); ++ii, jj += 3)
        {
            (*this)(ii) = Color(pixels[jj],
                                pixels[jj + 1],
                                pixels[jj + 2],
                                255);
        }
        break;

    case BGR:
        for (size_t ii = 0, jj = 0; ii < size.product(); ++ii, jj += 3)
        {
            (*this)(ii) = Color(pixels[jj + 2],
                                pixels[jj + 1],
                                pixels[jj],
                                255);
        }
        break;
    }
}

//===========================================================================//
Image::Image() :
    Image(math::Vector2U(0, 0))
{
}

//===========================================================================//
Image::Image(const math::Vector2U& size)
{
    resize(size);
}

//===========================================================================//
void Image::resize(const math::Vector2U& size)
{
    mMatrix = cv::Mat(size.y, size.x, CV_8UC4, cv::Scalar(0, 0, 0, 255));
}

//===========================================================================//
bool Image::operator==(const Image& other) const
{
    if (mMatrix.rows != other.mMatrix.rows ||
        mMatrix.cols != other.mMatrix.cols)
    {
        return false;
    }

    return std::equal(mMatrix.begin<uint8_t>(),
                      mMatrix.end<uint8_t>(),
                      other.mMatrix.begin<uint8_t>());
}

//===========================================================================//
Image& Image::operator+=(const Image& other)
{
    testSized(other, "addition");
    mMatrix += other.mMatrix;
    return *this;
}

//===========================================================================//
Image& Image::operator*=(const Image& other)
{
    testSized(other, "multiply");
    const math::Vector2U size = getSize();
    for(size_t ii = 0; ii < size.y; ++ii)
    {
        for(size_t jj = 0; jj < size.x; ++jj)
        {
            // Ignore alpha for now
            for (size_t c = 0 ; c < 3; c++)
            {
                const double target =
                        mMatrix.at<uchar>(ii, 4 * jj + c) / 255.0;
                const double blend =
                        other.mMatrix.at<uchar>(ii, 4 * jj + c) / 255.0;
                mMatrix.at<uchar>(ii, 4 * jj + c) =
                        cv::saturate_cast<uchar>(target * blend * 255);
            }
        }
    }
    return *this;
}

//===========================================================================//
void Image::testSized(const Image& other,
                      const std::string& op) const
{
    if (mMatrix.rows != other.mMatrix.rows ||
        mMatrix.cols != other.mMatrix.cols)
    {
        throw std::runtime_error(
                "Images do not have the same size during " +
                op + " operation");
    }
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Image& image)
{
    const math::Vector2U dims = image.getSize();
    const size_t size = dims.product();
    os << "Size: " << dims;
    if (size == 0)
    {
        return os;
    }

    if (size <= 10)
    {
        os << "\n[";
        for (size_t ii = 0; ii < size; ++ii)
        {
            if (ii > 0)
            {
                os << ", | ";
            }
            os << image(ii);
        }
        os << "]";
    }
    else
    {
        // Print the first and last five elements
        os << "\n[";
        for (size_t ii = 0; ii < 5; ++ii)
        {
            if (ii > 0)
            {
                os << ", | ";
            }
            os << image(ii);
        }
        os << "]...\n...[";
        for (size_t ii = size - 5; ii < size; ++ii)
        {
            if (ii > size - 5)
            {
                os << ", | ";
            }
            os << image(ii);
        }
        os << "]";
    }
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<img::Image>(const img::Image& image,
                       const std::string& pathname,
                       core::ArchiveType)
{
    cv::imwrite(pathname, image.getNative());
}

//===========================================================================//
template <>
void read<img::Image>(const std::string& pathname,
                      img::Image& image,
                      core::ArchiveType)
{
    if (!core::path::exists(pathname))
    {
        throw std::runtime_error("Pathname: " + pathname + " does not exist");
    }
    image.getNative() = cv::imread(pathname, cv::IMREAD_UNCHANGED);
}
}
}
