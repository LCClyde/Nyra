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
#ifndef __NYRA_GUI_CEGUI_IMAGE_H__
#define __NYRA_GUI_CEGUI_IMAGE_H__

#include <nyra/gui/cegui/Widget.h>
#include <nyra/gui/Image.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
/*
 *  \class Image
 *  \brief A class used to render an image to the screen.
 */
class Image : public gui::Image, public Widget
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default Image.
     *
     *  \param pathname The location of the image on disk. There is currently
     *         an issue with this where it cannot use anything other than
     *         an image in install/data/textures.
     */
    Image(const std::string& pathname);

    /*
     *  \func initialize
     *  \brief Creates a default Image.
     *
     *  \param pathname The location of the image on disk. There is currently
     *         an issue with this where it cannot use anything other than
     *         an image in install/data/textures.
     */
    void initialize(const std::string& pathname);
};
}
}
}

#endif
