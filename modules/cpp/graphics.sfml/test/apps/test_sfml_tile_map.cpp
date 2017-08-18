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
#include <nyra/graphics/TileMap.h>
#include <nyra/core/Path.h>
#include <nyra/img/Color.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
TEST(SFMLTileMap, Rect)
{
    RenderTarget target(math::Vector2U(512, 512));

    mem::Buffer2D<size_t> tiles({{0, 1, 2, 3, 3, 2, 1, 0},
                                 {3, 2, 1, 0, 0, 1, 2, 3},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {1, 1, 1, 1, 1, 1, 1, 1},
                                 {2, 2, 2, 2, 2, 2, 2, 2}});
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/test_frame_animation.png");
    TileMap<Sprite> tileMap(pathname, tiles, math::Vector2U(64, 128));

    target.clear(img::Color::GRAY);
    tileMap.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(
            target.getPixels(), "test_tile_map.png"));
}
}
}
}

NYRA_TEST()
