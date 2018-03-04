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
#include <nyra/media/BoxArtList.h>
#include <nyra/media/Config.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>
#include <nyra/test/Image.h>

namespace
{
//===========================================================================//
std::vector<nyra::media::Game> getGames()
{
    const std::string path = nyra::core::DATA_PATH + "/textures/";
    std::vector<nyra::media::Game> games(5);
    games[0].sprite.reset(new nyra::graphics::sfml::Sprite(
            path + "/test_256x512_box_art.png"));
    games[1].sprite.reset(new nyra::graphics::sfml::Sprite(
            path + "/test_512x256_box_art.png"));
    games[2].sprite.reset(new nyra::graphics::sfml::Sprite(
            path + "/test_256x256_box_art.png"));
    games[3].sprite.reset(new nyra::graphics::sfml::Sprite(
            path + "/test_512x256_box_art.png"));
    games[4].sprite.reset(new nyra::graphics::sfml::Sprite(
            path + "/test_256x512_box_art.png"));
    return games;
}
}

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(BoxArtList, Horizontal)
{
    graphics::sfml::RenderTarget target(Config::DEFAULT_SIZE / 3.0);
    GameListLayout layout;
    layout.boxSize = 200.0;
    layout.boxLayout = GameListLayout::HORIZONTAL;
    layout.boxPosition = 800.0;
    layout.boxSpacing = 5.0;

    std::vector<Game> games = getGames();
    BoxArtList list(layout, games);
    list.resetLayout(target.getSize());

    for (size_t ii = 0; ii < games.size(); ++ii)
    {
        list.updateIndex(ii);
        target.clear(img::Color::BLACK);
        list.render(target);
        target.flush();
        EXPECT_TRUE(test::compareImage(
            target.getPixels(),
            "test_box_art_horizontal_" + core::str::toString(ii) + ".png"));
    }
}

//===========================================================================//
TEST(BoxArtList, Vertical)
{
    graphics::sfml::RenderTarget target(Config::DEFAULT_SIZE / 3.0);
    GameListLayout layout;
    layout.boxSize = 200.0;
    layout.boxLayout = GameListLayout::VERTICAL;
    layout.boxPosition = 200.0;
    layout.boxSpacing = 5.0;

    std::vector<Game> games = getGames();
    BoxArtList list(layout, games);
    list.resetLayout(target.getSize());

    for (size_t ii = 0; ii < games.size(); ++ii)
    {
        list.updateIndex(ii);
        target.clear(img::Color::BLACK);
        list.render(target);
        target.flush();
        EXPECT_TRUE(test::compareImage(
            target.getPixels(),
            "test_box_art_vertical_" + core::str::toString(ii) + ".png"));
    }
}
}
}

NYRA_TEST()
