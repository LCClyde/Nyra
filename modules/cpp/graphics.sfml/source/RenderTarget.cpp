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
#include <nyra/graphics/sfml/RenderTarget.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
//===========================================================================//
RenderTarget::RenderTarget(const math::Vector2U& size) :
    mTexture(new sf::RenderTexture()),
    mSprite(new sf::Sprite())
{
    initialize(size);
}

//===========================================================================//
RenderTarget::RenderTarget(win::Window& window) :
    mTexture(new sf::RenderTexture()),
    mSprite(new sf::Sprite())
{
    initialize(window);
}

//===========================================================================//
void RenderTarget::initialize(win::Window& window)
{
    mWindow.reset(new sf::RenderWindow(
            static_cast<sf::WindowHandle>(window.getID())));
    resize(math::Vector2U(mWindow->getSize().x,
                          mWindow->getSize().y));
}

//===========================================================================//
void RenderTarget::initialize(const math::Vector2U& size)
{
    resize(size);
}

//===========================================================================//
math::Vector2U RenderTarget::getSize() const
{
    return math::Vector2U(mTexture->getSize().x,
                          mTexture->getSize().y);
}

//===========================================================================//
void RenderTarget::resize(const math::Vector2U& size)
{
    mTexture->create(size.x, size.y);
    mSprite->setTexture(mTexture->getTexture(), true);

    // Set the window as the active render target. This allows external
    // applications to get the current OpenGL context after the initial
    // setup.
    if (mWindow.get())
    {
        mWindow->setActive(true);
    }
}

//===========================================================================//
void RenderTarget::clear(const img::Color& color)
{
    const sf::Color sfColor(color.r, color.g, color.b);
    if (mWindow.get())
    {
        mWindow->clear(sfColor);
    }
    mTexture->clear(sfColor);
}

//===========================================================================//
void RenderTarget::flush()
{
    mTexture->display();

    if (mWindow.get())
    {
        mWindow->draw(*mSprite);
        mWindow->display();
    }
}

//===========================================================================//
img::Image RenderTarget::getPixels() const
{
    const sf::Image image = mTexture->getTexture().copyToImage();
    return img::Image(image.getPixelsPtr(),
                      math::Vector2U(image.getSize().x,
                                     image.getSize().y));
}
}
}
}
