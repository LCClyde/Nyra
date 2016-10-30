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
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/mem/SharedResource.h>
#include <nyra/graphics/sfml/RenderTarget.h>

namespace
{
//===========================================================================//
static nyra::mem::SharedResource<nyra::graphics::sfml::Texture> resource;
}

namespace nyra
{
namespace graphics
{
namespace sfml
{
//===========================================================================//
Sprite::Sprite(const std::string& texture)
{
    load(texture);
}

//===========================================================================//
void Sprite::load(const std::string& texture)
{
    mSprite.reset(new sf::Sprite());
    mTexture = resource[texture];
    mSprite->setTexture(mTexture->get());
    setSize(math::Vector2U(mTexture->get().getSize().x,
                           mTexture->get().getSize().y));
}

//===========================================================================//
void Sprite::render(graphics::RenderTarget& target)
{
    const math::Matrix3x3& m = getMatrix();
    sf::Transform transform(m(0, 0), m(0, 1), m(0, 2),
                            m(1, 0), m(1, 1), m(1, 2),
                            m(2, 0), m(2, 1), m(2, 2));
    dynamic_cast<graphics::sfml::RenderTarget&>(
            target).get().draw(*mSprite, transform);
}
}
}
}
