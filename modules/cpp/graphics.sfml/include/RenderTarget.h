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
#ifndef __NYRA_GRAPHICS_SFML_RENDER_TARGET_H__
#define __NYRA_GRAPHICS_SFML_RENDER_TARGET_H__

#include <nyra/graphics/RenderTarget.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace nyra
{
namespace graphics
{
namespace sfml
{
/*
 *  \class RenderTarget
 *  \brief Render target for SFML.
 */
class RenderTarget : public graphics::RenderTarget
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the default render target without a Window.
     *
     *  \param size The size of the render target.
     */
    RenderTarget(const math::Vector2U& size);

    /*
     *  \func Constructor
     *  \brief Sets up the default render target.
     *
     *  \param window The Window to render to.
     */
    RenderTarget(win::Window& window);

    /*
     *  \func initialize
     *  \brief Sets up the default render target without a Window.
     *
     *  \param size The size of the render target.
     */
    void initialize(const math::Vector2U& size) override;

    /*
     *  \func initialize
     *  \brief Sets up the default render target.
     *
     *  \param window The Window to render to.
     */
    void initialize(win::Window& window) override;

    /*
     *  \func getSize
     *  \brief Get the size of the render target.
     *
     *  \return The size of the render target
     */
    math::Vector2U getSize() const override;

    /*
     *  \func resize
     *  \brief Sets the size of a render target.
     *
     *  \param size The desired size
     */
    void resize(const math::Vector2U& size) override;

    /*
     *  \func clear
     *  \brief Clears the render target to a single color.
     *
     *  \param color The color to clear to.
     */
    void clear(const img::Color& color) override;

    /*
     *  \func render
     *  \brief Renders the target to the screen
     */
    void flush() override;

    /*
     *  \func getPixels
     *  \brief Gets the pixels of the underlying target. In general this
     *         will often be slow and should not be used in performance
     *         critical areas.
     *
     *  \return The image representing the render target.
     */
    img::Image getPixels() const;

    /*
     *  \func get
     *  \brief Gets the underlying render target.
     *
     *  \return The SFML render texture.
     */
    sf::RenderTarget& get()
    {
        return *mTexture;
    }


private:
    std::unique_ptr<sf::RenderWindow> mWindow;
    std::unique_ptr<sf::RenderTexture> mTexture;
    std::unique_ptr<sf::Sprite> mSprite;
};
}
}
}

#endif
