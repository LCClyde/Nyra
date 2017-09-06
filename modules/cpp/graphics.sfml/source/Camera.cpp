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
#include <SFML/Graphics.hpp>
#include <nyra/graphics/sfml/Camera.h>
#include <nyra/graphics/sfml/RenderTarget.h>

namespace
{
//===========================================================================//
nyra::math::Vector2F getTargetSize(const nyra::graphics::RenderTarget& target)
{
    const sf::RenderTarget& sfTarget(dynamic_cast
            <const nyra::graphics::sfml::RenderTarget&>(target).get());
    const sf::View& view(sfTarget.getDefaultView());
    return nyra::math::Vector2F(view.getSize().x, view.getSize().y);
}
}

namespace nyra
{
namespace graphics
{
namespace sfml
{
//===========================================================================//
Camera::Camera(const graphics::RenderTarget& target) :
    Camera(getTargetSize(target))
{
}

//===========================================================================//
Camera::Camera(const math::Vector2F& size)
{
    setSize(size);
    setPosition(size / 2);
}

//===========================================================================//
void Camera::render(graphics::RenderTarget& target)
{
    sf::RenderTarget& sfTarget(dynamic_cast
            <graphics::sfml::RenderTarget&>(target).get());
    sf::View view;
    const math::Vector2F size = getScaledSize();
    view.setSize(size.x ,size.y);
    view.setCenter(getPosition().x, getPosition().y);
    view.setRotation(getRotation());
    sfTarget.setView(view);
}
}
}
}
