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
#ifndef __NYRA_GRAPHICS_SFML_SPRITE_H__
#define __NYRA_GRAPHICS_SFML_SPRITE_H__

#include <memory>
#include <SFML/Graphics.hpp>
#include <nyra/graphics/Sprite.h>
#include <nyra/graphics/sfml/Texture.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
/*
 *  \class Sprite
 *  \brief Class for rendering images to a render target.
 */
class Sprite : public nyra::graphics::Sprite
{
public:
    Sprite(const std::string& texture);

    /*
     *  \func load
     *  \brief Loads a Sprite from a texture on disk.
     *
     *  \param texture The name of the texture.
     */
    void load(const std::string& texture) override;

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override;

    /*
     *  \func setRect
     *  \brief Sets the visible portion of the sprite.
     *
     *  \param offset The offset in the x and y direction in pixels
     *  \param extents The size of the image x is width, y is height.
     */
    void setRect(const math::Vector2U& offset,
                 const math::Vector2U& extents) override;

private:
    std::shared_ptr<Texture> mTexture;
    std::unique_ptr<sf::Sprite> mSprite;

};
}
}
}

#endif
