/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/img/Draw.h>
#include <opencv2/opencv.hpp>
#include <cairo/cairo.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
class TextDrawer
{
public:
    TextDrawer(cv::Mat& image) :
       mImage(image)
    {
        // Create Cairo
        mSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                              mImage.cols,
                                              mImage.rows);
        mCairo = cairo_create(mSurface);

        // Wrap Cairo with a Mat
        mCairoImage = cv::Mat(cairo_image_surface_get_height(mSurface),
                              cairo_image_surface_get_width(mSurface),
                              CV_8UC4,
                              cairo_image_surface_get_data(mSurface),
                              cairo_image_surface_get_stride(mSurface));

        // Put image onto Cairo
        mImage.copyTo(mCairoImage);
    }

    nyra::math::Vector2U getSize(const std::string& text,
                                 const std::string& fontFace,
                                 double fontSize,
                                 bool fontItalic,
                                 bool fontBold)
    {
        mText = text;

        // Set font and write text
        cairo_select_font_face (
                mCairo,
                fontFace.c_str(),
                fontItalic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                fontBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

        cairo_set_font_size(mCairo, fontSize);
        cairo_text_extents(mCairo, mText.c_str(), &mExtents);
        return nyra::math::Vector2U(mExtents.width, mExtents.height);
    }

    void draw(const nyra::img::Color& color,
              const nyra::math::Vector2U& offset)
    {
        cairo_set_source_rgb(mCairo,
                             color.r / 255.0,
                             color.g / 255.0,
                             color.b / 255.0);

        cairo_move_to(mCairo,
                      offset.x - mExtents.x_bearing,
                      offset.y - mExtents.y_bearing);
        cairo_show_text(mCairo, mText.c_str());

        // Copy the data to the output image
        mCairoImage.copyTo(mImage);
    }

private:
    cv::Mat& mImage;
    cv::Mat mCairoImage;
    cairo_surface_t* mSurface;
    cairo_t* mCairo;
    cairo_text_extents_t mExtents;
    std::string mText;
    nyra::math::Vector2U mSize;
};
}

namespace nyra
{
namespace img
{
namespace draw
{
//===========================================================================//
void text(const std::string& text,
          const math::Vector2U& offset,
          const std::string& font,
          size_t fontSize,
          const Color& color,
          bool bold,
          bool italic,
          Image& image)
{
    TextDrawer drawer(image.getNative());
    drawer.getSize(text, font, fontSize, italic, bold);
    drawer.draw(color, offset);
}

//===========================================================================//
void text(const std::string& text,
          const math::Vector2U& offset,
          const std::string& font,
          size_t fontSize,
          const Color& color,
          bool bold,
          bool italic,
          size_t maxWidth,
          Image& image)
{
    TextDrawer drawer(image.getNative());

    std::string prevLine;
    std::string thisLine;
    const std::vector<std::string> parts = core::str::split(text, " ");
    for (const std::string& word : parts)
    {
        if (!thisLine.empty())
        {
            thisLine += " ";
        }
        thisLine += word;
        const math::Vector2U size = drawer.getSize(
                thisLine, font, fontSize, italic, bold);

        if (size.x > maxWidth)
        {
            drawer.getSize(prevLine, font, fontSize, italic, bold);
            drawer.draw(color, offset);
            offset.y += size.y + 2;
            thisLine = word;
        }
        prevLine = thisLine;
    }

    drawer.getSize(prevLine, font, fontSize, italic, bold);
    drawer.draw(color, offset);
}
}
}
}

