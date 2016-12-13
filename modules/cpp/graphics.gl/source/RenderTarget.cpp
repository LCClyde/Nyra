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
#include <nyra/graphics/gl/RenderTarget.h>

namespace nyra
{
namespace graphics
{
namespace gl
{
//===========================================================================//
RenderTarget::RenderTarget(const math::Vector2U& size) :
    mWindow(nullptr)
{
    initialize(size);
}

//===========================================================================//
RenderTarget::RenderTarget(win::Window& window) :
    mWindow(nullptr)
{
    initialize(window);
}

//===========================================================================//
void RenderTarget::initialize(win::Window& window)
{
    mWindow = reinterpret_cast<GLFWwindow*>(window.getNative());
    resize(window.getSize());
}

//===========================================================================//
void RenderTarget::initialize(const math::Vector2U& size)
{
}

//===========================================================================//
void RenderTarget::resize(const math::Vector2U& size)
{
    mSize = size;
    glViewport(0, 0, mSize.x(), mSize.y());
}

//===========================================================================//
void RenderTarget::clear(const img::Color& color)
{
    glClearColor(color.r / 255.0f,
                 color.g / 255.0f,
                 color.b / 255.0f,
                 color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//===========================================================================//
void RenderTarget::flush()
{
    if (mWindow)
    {
        glfwSwapBuffers(mWindow);
    }
}

//===========================================================================//
img::Image RenderTarget::getPixels() const
{
    std::vector<uint8_t> pixels(4 * mSize.x() * mSize.y());
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(0, 0, mSize.x(), mSize.y(), GL_RGBA,
                 GL_UNSIGNED_BYTE, &pixels[0]);
    return img::Image(pixels.data(), mSize, img::Image::RGBA);
}
}
}
}
