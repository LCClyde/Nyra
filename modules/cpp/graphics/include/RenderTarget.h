/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_GRAPHICS_RENDER_TARGET_H__
#define __NYRA_GRAPHICS_RENDER_TARGET_H__

#include <nyra/img/Color.h>
#include <nyra/img/Image.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class RenderTarget
 *  \brief Base class for all render targets. Anything that wants to draw needs
 *         to use this common interface.
 *         This does not include serialization methods since it requires the
 *         window ID to function correctly. The window ID will not remain
 *         constant between runs.
 */
class RenderTarget
{
public:
    /*
     *  \func initialize
     *  \brief Sets up the default render target without a Window.
     *
     *  \param size The size of the render target.
     */
    virtual void initialize(const math::Vector2U& size) = 0;

    /*
     *  \func initialize
     *  \brief Sets up the default render target.
     *
     *  \param winId The Window ID from a nyra::win::Window object
     */
    virtual void initialize(size_t winId) = 0;

    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~RenderTarget() = default;

    /*
     *  \func getSize
     *  \brief Get the size of the render target.
     *
     *  \return The size of the render target
     */
    virtual math::Vector2U getSize() const = 0;

    /*
     *  \func resize
     *  \brief Sets the size of a render target.
     *
     *  \param size The desired size
     */
    virtual void resize(const math::Vector2U& size) = 0;

    /*
     *  \func setSize
     *  \brief Same as resize. Used to help keep a similar interface
     *         between all classes.
     *
     *  \param size The desired size
     */
    void setSize(const math::Vector2U& size)
    {
        resize(size);
    }

    /*
     *  \func clear
     *  \brief Clears the render target to a single color.
     *
     *  \param color The color to clear to.
     */
    virtual void clear(const img::Color& color) = 0;

    /*
     *  \func render
     *  \brief Renders the target to the screen
     */
    virtual void flush() = 0;

    /*
     *  \func getPixels
     *  \brief Gets the pixels of the underlying target. In general this
     *         will often be slow and should not be used in performance
     *         critical areas.
     *
     *  \return The image representing the render target.
     */
    virtual img::Image getPixels() const = 0;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const RenderTarget& target);
};
}
}

#endif
