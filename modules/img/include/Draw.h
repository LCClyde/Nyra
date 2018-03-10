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
#ifndef __NYRA_IMG_DRAW_H__
#define __NYRA_IMG_DRAW_H__

#include <string>
#include <nyra/img/Image.h>

namespace nyra
{
namespace img
{
namespace draw
{
/*
 *  \func text
 *  \brief Draws text to an image
 *
 *  \param text The text to draw
 *  \param offset The top left corner to draw the text to.
 *  \param font The name of the desired font
 *  \param fontSize The size of the font
 *  \param color The color of the font
 *  \param bold Is the text bold?
 *  \param italic Is the text italics?
 *  \param The input/output image
 */
void text(const std::string& text,
          const math::Vector2U& offset,
          const std::string& font,
          size_t fontSize,
          const Color& color,
          bool bold,
          bool italic,
          Image& image);

/*
 *  \func text
 *  \brief Same as above, but also does word wrap
 *
 *  \param text The text to draw
 *  \param offset The top left corner to draw the text to.
 *  \param font The name of the desired font
 *  \param fontSize The size of the font
 *  \param color The color of the font
 *  \param bold Is the text bold?
 *  \param italic Is the text italics?
 *  \param maxWidth The width to word wrap to.
 *  \param The input/output image
 */
void text(const std::string& text,
          const math::Vector2U& offset,
          const std::string& font,
          size_t fontSize,
          const Color& color,
          bool bold,
          bool italic,
          size_t maxWidth,
          Image& image);
}
}
}

#endif
