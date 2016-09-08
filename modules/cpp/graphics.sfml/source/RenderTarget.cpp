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
#include <nyra/graphics/sfml/RenderTarget.h>
#include <iostream>

namespace nyra
{
namespace graphics
{
namespace sfml
{
//===========================================================================//
RenderTarget::RenderTarget(size_t winId) :
    graphics::RenderTarget(winId),
    mWindow(new sf::RenderWindow(static_cast<sf::WindowHandle>(winId))),
    mTexture(new sf::RenderTexture()),
    mSprite(new sf::Sprite())
{
    resize(mWindow->getSize());
}

//===========================================================================//
math::Vector2U RenderTarget::getSize() const
{
    return math::Vector2U(mTexture->getSize());
}

//===========================================================================//
void RenderTarget::resize(const math::Vector2U& size)
{
    mTexture->create(size.x, size.y);
    mSprite->setTexture(mTexture->getTexture(), true);
}

//===========================================================================//
void RenderTarget::clear(const img::Color& color)
{
    const sf::Color sfColor(color.r, color.g, color.b);
    mWindow->clear(sfColor);
    mTexture->clear(sfColor);
}

//===========================================================================//
void RenderTarget::flush()
{
    mTexture->display();
    mWindow->draw(*mSprite);
    mWindow->display();
}

//===========================================================================//
img::Image RenderTarget::getPixels() const
{
    const sf::Image image = mTexture->getTexture().copyToImage();
    return img::Image(image.getPixelsPtr(), math::Vector2U(image.getSize()));
}
}
}
}
