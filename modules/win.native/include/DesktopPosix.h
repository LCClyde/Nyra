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
#ifndef __NYRA_WIN_NATIVE_DESKTOP_POSIX_H__
#define __NYRA_WIN_NATIVE_DESKTOP_POSIX_H__

#include <nyra/img/Image.h>
#include <nyra/math/Vector2.h>
#include <nyra/win/native/PosixGlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace win
{
namespace native
{
/*
 *  \class DesktopPosix
 *  \brief Handles interacting the desktop
 */
class DesktopPosix :
        private mem::GlobalDependency<PosixGlobalHandler>
{
public:
    /*
     *  \func getSize
     *  \brief Gets the size of the desktop in pixels
     *
     *  \return The size of the desktop
     */
    math::Vector2U getSize() const;

    /*
     *  \func getPixels
     *  \brief Takes a screenshot of the desktop.
     *
     *  \param offset The starting pixel
     *  \param size The number of pixels
     *  \return The image of the desktop
     */
    img::Image getPixels(const math::Vector2I& offset,
                         const math::Vector2U& size) const;

    /*
     *  \func getPixels
     *  \brief Takes a screenshot of the desktop.
     *
     *  \return The image of the desktop
     */
    img::Image getPixels() const
    {
        return getPixels(math::Vector2I(0, 0), getSize());
    }
};
}
}
}

#endif
