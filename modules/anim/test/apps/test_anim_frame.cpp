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
#include <nyra/core/Path.h>
#include <nyra/test/Image.h>
#include <nyra/anim/Frame.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace anim
{
TEST(FrameAnimation, Render)
{
    graphics::sfml::RenderTarget target(math::Vector2U(256, 256));
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation.png");
    graphics::sfml::Sprite sprite(pathname);
    sprite.setPosition(math::Vector2F(128, 128));
    img::Image expected;
    anim::Frame<graphics::Sprite> animation(
            0, 7, 8.0, Animation::LOOP,
            math::Vector2U(4, 2), sprite);
    animation.update(0);

    for (size_t ii = 0; ii < 20; ++ii)
    {
        target.clear(img::Color::BLACK);
        sprite.updateTransform(math::Transform2D());
        sprite.render(target);
        target.flush();
        const std::string filename = "test_frame_animation_" +
                core::str::toString((ii % 8) + 1) + ".png";
        EXPECT_TRUE(test::compareImage(target.getPixels(), filename));

        // I need to add an additional offset here otherwise when it loops
        // you see the last frame for one extra frame because the time
        // aligns perfectly to 8.0.
        // In practice this will probably never be an issue.
        animation.update(1.00001);
    }
}
}
}

NYRA_TEST()
