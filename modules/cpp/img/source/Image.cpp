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
#include <png.h>

namespace
{
//===========================================================================//
class PNGWrapper
{
public:
//===========================================================================//
    PNGWrapper() :
        mFile(nullptr),
        mPNG(nullptr),
        mInfo(nullptr)
    {
    }

//===========================================================================//
    virtual ~PNGWrapper()
    {
        if (mFile)
        {
            fclose(mFile);
        }
    }

//===========================================================================//
protected:
    FILE* mFile;
    png_structp mPNG;
    png_infop mInfo;
};

//===========================================================================//
class PNGWriter : public PNGWrapper
{
public:
//===========================================================================//
    PNGWriter(const nyra::img::Image& image,
              const std::string& pathname)
    {
        const size_t width = image.getSize().x;
        const size_t height = image.getSize().y;

        mFile = fopen (pathname.c_str(), "wb");
        mPNG = png_create_write_struct(
                PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        mInfo = png_create_info_struct(mPNG);

        png_set_IHDR(mPNG,
                     mInfo,
                     width,
                     height,
                     8,  // Pixel depth
                     PNG_COLOR_TYPE_RGBA,
                     PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT,
                     PNG_FILTER_TYPE_DEFAULT);

        std::vector<png_byte*> rows(height);
        for (size_t ii = 0; ii < rows.size(); ++ii)
        {
            rows[ii] = reinterpret_cast<png_byte*>(
                    const_cast<nyra::img::Color*>(&(image(ii, 0))));
        }

        png_init_io(mPNG, mFile);
        png_set_rows(mPNG, mInfo, rows.data());
        png_write_png (mPNG, mInfo, PNG_TRANSFORM_IDENTITY, nullptr);
    }

//===========================================================================//
    ~PNGWriter()
    {
        if (mPNG && mInfo)
        {
            png_destroy_write_struct(&mPNG, &mInfo);
        }
    }
};

//===========================================================================//
class PNGReader : public PNGWrapper
{
public:
//===========================================================================//
    PNGReader(const std::string& pathname,
              nyra::img::Image& image)
    {
        mFile = fopen(pathname.c_str(), "rb");

        mPNG = png_create_read_struct(
                PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        mInfo = png_create_info_struct(mPNG);

        png_init_io(mPNG, mFile);
        png_read_info(mPNG, mInfo);

        const size_t width = png_get_image_width(mPNG, mInfo);
        const size_t height = png_get_image_height(mPNG, mInfo);
        const size_t colorType = png_get_color_type(mPNG, mInfo);
        const size_t bitDepth  = png_get_bit_depth(mPNG, mInfo);

        // Read any color_type into 8bit depth, RGBA format.
        // See http://www.libpng.org/pub/png/libpng-manual.txt
        if(bitDepth == 16)
        {
            png_set_strip_16(mPNG);
        }

        if(colorType == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(mPNG);
        }

        // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
        if(colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
        {
            png_set_expand_gray_1_2_4_to_8(mPNG);
        }

        if(png_get_valid(mPNG, mInfo, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(mPNG);
        }

        // These color_type don't have an alpha channel then fill it with 0xff.
        if(colorType == PNG_COLOR_TYPE_RGB ||
           colorType == PNG_COLOR_TYPE_GRAY ||
           colorType == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_filler(mPNG, 0xFF, PNG_FILLER_AFTER);
        }

        if(colorType == PNG_COLOR_TYPE_GRAY ||
           colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        {
            png_set_gray_to_rgb(mPNG);
        }

        png_read_update_info(mPNG, mInfo);

        image.resize(nyra::math::Vector2U(width, height));
        std::vector<png_byte*>rows (height);
        for(size_t ii = 0; ii < rows.size(); ++ii)
        {
            rows[ii] = reinterpret_cast<png_byte*>(&(image(ii, 0)));
        }

        png_read_image(mPNG, rows.data());
    }

//===========================================================================//
    ~PNGReader()
    {
        if (mPNG && mInfo)
        {
            png_destroy_read_struct(&mPNG, &mInfo, nullptr);
        }
    }
};
}

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
    if (size.product() > 0)
    {
        switch (format)
        {
        case RGBA:
        {
            uint8_t* imagePixels = reinterpret_cast<uint8_t*>(mPixels.data());
            memcpy(imagePixels, pixels, size.product() * sizeof(Color));
            break;
        }

        case ARGB:
            for (size_t ii = 0, jj = 0; ii < mPixels.size(); ++ii, jj += 4)
            {
                // Swap the channels around
                mPixels[ii] = Color(pixels[jj + 1],
                                    pixels[jj + 2],
                                    pixels[jj + 3],
                                    pixels[jj]);
            }
            break;

        case BGRA:
            for (size_t ii = 0, jj = 0; ii < mPixels.size(); ++ii, jj += 4)
            {
                // Swap the channels around
                mPixels[ii] = Color(pixels[jj + 2],
                                    pixels[jj + 1],
                                    pixels[jj],
                                    pixels[jj + 3]);
            }
            break;

        case RGB:
            for (size_t ii = 0, jj = 0; ii < mPixels.size(); ++ii, jj += 3)
            {
                mPixels[ii] = Color(pixels[jj],
                                    pixels[jj + 1],
                                    pixels[jj + 2],
                                    255);
            }
            break;

        case BGR:
            for (size_t ii = 0, jj = 0; ii < mPixels.size(); ++ii, jj += 3)
            {
                mPixels[ii] = Color(pixels[jj + 2],
                                    pixels[jj + 1],
                                    pixels[jj],
                                    255);
            }
            break;
        }
    }
}

//===========================================================================//
Image::Image(const math::Vector2U& size)
{
    resize(size);
}

//===========================================================================//
bool Image::operator==(const Image& other) const
{
    return mPixels == other.mPixels;
}

//===========================================================================//
void Image::invert()
{
    for (size_t ii = 0; ii < mSize.product(); ++ii)
    {
        mPixels[ii].invert();
    }
}

//===========================================================================//
Image& Image::operator+=(const Image& other)
{
    testSized(other, "addition");

    for (size_t ii = 0; ii < mSize.product(); ++ii)
    {
        mPixels[ii] += other.mPixels[ii];
    }
    return *this;
}

//===========================================================================//
Image& Image::operator*=(const Image& other)
{
    testSized(other, "multiply");

    for (size_t ii = 0; ii < mSize.product(); ++ii)
    {
        mPixels[ii] *= other.mPixels[ii];
    }
    return *this;
}

//===========================================================================//
void Image::testSized(const Image& other,
                      const std::string& op) const
{
    if (mSize != other.mSize)
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
    PNGWriter(image, pathname);
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
    PNGReader(pathname, image);
}
}
}
