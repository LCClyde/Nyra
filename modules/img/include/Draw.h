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
/*
 *  \class Font
 *  \brief Controls how text is drawn to an image.
 *         TODO: Should have a global usable font across all modules.
 */
struct Font
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default usable font
     */
    Font();

    /*
     *  \var name
     *  \brief The name of the font
     */
    std::string name;

    /*
     *  \var size
     *  \brief Standard font size
     */
    size_t size;

    /*
     *  \var color
     *  \brief Draw color
     */
    Color color;

    /*
     *  \var bold
     *  \brief Is the font bold?
     */
    bool bold;

    /*
     *  \var italic
     *  \brief Is the font italic?
     */
    bool italic;

    /*
     *  \var maxWidth
     *  \brief The max width in pixels. After this width
     *         line breaks start.
     */
    size_t maxWidth;

    /*
     *  \var xOffset
     *  \brief a tab offset on the first line.
     */
    size_t xOffset;

    /*
     *  \var returnNextLine
     *  \brief If true, the next line is returned from the
     *         draw function
     */
    size_t returnNextLine;
};

namespace draw
{
/*
 *  \func text
 *  \brief Same as above, but also does word wrap
 *
 *  \param text The text to draw
 *  \param offset The top left corner to draw the text to.
 *  \param font The name of the desired font
 *  \param image The input/output image
 *  \return The spot where the text ends
 */
math::Vector2U text(const std::string& text,
                    const math::Vector2U& offset,
                    const Font& font,
                    Image& image);
}
}
}

#endif
