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
#include <nyra/test/Test.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/Camera.h>
#include <nyra/core/Path.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
//===========================================================================//
TEST(Camera, Transpose)
{
    RenderTarget target(math::Vector2U(512, 512));
    const std::string basePathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation");
    Sprite sprite(basePathname + ".png");
    Camera camera(target);

    // Center the sprite in the middle of the screen
    sprite.setPosition(math::Vector2F(256.0f, 256.0f));
    sprite.updateTransform(math::Transform2D());
    camera.setPosition(math::Vector2F(256.0f + 128.0f, 256.0f - 192.0f));

    target.clear(img::Color::GRAY);
    camera.render(target);
    sprite.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(),
                                   "test_camera_transpose.png"));
}

//===========================================================================//
TEST(Camera, Rotate)
{
    RenderTarget target(math::Vector2U(512, 512));
    const std::string basePathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation");
    Sprite sprite(basePathname + ".png");
    Camera camera(target);

    // Center the sprite in the middle of the screen
    sprite.setPosition(math::Vector2F(256.0f, 256.0f));
    sprite.updateTransform(math::Transform2D());
    camera.setRotation(45.0f);

    target.clear(img::Color::GRAY);
    camera.render(target);
    sprite.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(),
                                   "test_camera_rotate.png"));
}

//===========================================================================//
TEST(Camera, Scale)
{
    RenderTarget target(math::Vector2U(512, 512));
    const std::string basePathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation");
    Sprite sprite(basePathname + ".png");
    Camera camera(target);

    // Center the sprite in the middle of the screen
    sprite.setPosition(math::Vector2F(256.0f, 256.0f));
    sprite.updateTransform(math::Transform2D());
    camera.setScale(math::Vector2F(0.5f, 2.0f));

    target.clear(img::Color::GRAY);
    camera.render(target);
    sprite.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(),
                                   "test_camera_scale.png"));
}
}
}
}

NYRA_TEST()
