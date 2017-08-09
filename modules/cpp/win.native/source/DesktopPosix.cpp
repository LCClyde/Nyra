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
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <nyra/win/native/DesktopPosix.h>

namespace nyra
{
namespace win
{
namespace native
{
//===========================================================================//
img::Image DesktopPosix::getPixels(const math::Vector2I& offset,
                                   const math::Vector2U& size) const
{
    Display* display = getGlobalInstance().get();
    const int screen = getGlobalInstance().getScreen();

    XImage* image;
    image = XGetImage(display,
                      RootWindow(display, screen),
                      offset.x, offset.y,
                      size.x, size.y,
                      AllPlanes, XYPixmap);

    nyra::img::Image ret(size);
    const uint64_t redMask = image->red_mask;
    const uint64_t greenMask = image->green_mask;
    const uint64_t blueMask = image->blue_mask;

    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x)
        {
            const uint64_t pixel = XGetPixel(image,x,y);
            const uint8_t blue = pixel & blueMask;
            const uint8_t green = (pixel & greenMask) >> 8;
            const uint8_t red = (pixel & redMask) >> 16;
            ret(y, x) = img::Color(red, green, blue);
        }
    }
    XFree (image);
    return ret;
}

//===========================================================================//
math::Vector2U DesktopPosix::getSize() const
{
    Screen* screen = DefaultScreenOfDisplay(getGlobalInstance().get());
    return math::Vector2U(screen->width, screen->height);
}
}
}
}
