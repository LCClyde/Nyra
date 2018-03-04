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
#include <nyra/test/Test.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/core/Path.h>
#include <nyra/img/Color.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
TEST(SFMLSprite, Render)
{
    RenderTarget target(math::Vector2U(256, 128));
    const std::string basePathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation");
    Sprite sprite(basePathname + ".png");
    img::Image expected;

    // Center the sprite in the middle of the screen
    sprite.setPosition(math::Vector2F(128.0f, 64.0f));

    sprite.updateTransform(math::Transform2D());
    target.clear(img::Color::BLACK);
    sprite.render(target);
    target.flush();
    core::read(basePathname + ".png", expected);
    core::write(target.getPixels(), "expected.png");
    EXPECT_EQ(target.getPixels(), expected);

    sprite.setRotation(180.0);
    sprite.updateTransform(math::Transform2D());
    target.clear(img::Color::BLACK);
    sprite.render(target);
    target.flush();
    core::read(basePathname + "_rotated.png", expected);
    EXPECT_EQ(target.getPixels(), expected);

    sprite.setRotation(0.0);
    sprite.setScale(0.5);
    sprite.updateTransform(math::Transform2D());
    target.clear(img::Color::BLACK);
    sprite.render(target);
    target.flush();
    core::read(basePathname + "_scaled.png", expected);
    EXPECT_EQ(target.getPixels(), expected);

    sprite.setPivot(math::Vector2F(0.0, 0.0));
    sprite.setRotation(45.0);
    sprite.setScale(0.5);
    sprite.setPosition(math::Vector2F(75.0f, 10.0f));
    sprite.updateTransform(math::Transform2D());
    target.clear(img::Color::BLACK);
    sprite.render(target);
    target.flush();
    core::read(basePathname + "_transformed.png", expected);
    EXPECT_EQ(target.getPixels(), expected);
}

TEST(SFMLSprite, Frame)
{
    RenderTarget target(math::Vector2U(512, 512));
    const std::string basePathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation");
    Sprite sprite(basePathname + ".png");
    sprite.setFrame(math::Vector2U(64, 0), math::Vector2U(128, 128));

    // Center the sprite in the middle of the screen
    sprite.setPosition(math::Vector2F(256.0f, 256.0f));

    sprite.updateTransform(math::Transform2D());
    target.clear(img::Color::GRAY);
    sprite.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(
            target.getPixels(), "test_frame_animation_rect.png"));
}
}
}
}

NYRA_TEST()
