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
#include <nyra/media/BoxArtLoader.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(BoxArtLoader, Load)
{
    std::vector<Game> games(2);

    games[0].boxArtFile = "game 2.png";
    games[1].boxArtFile = "game 3.png";

    BoxArtLoader loader(games, core::path::join(
            core::DATA_PATH, "/textures/mtest/"));

    EXPECT_EQ(nullptr, games[0].sprite.get());
    EXPECT_EQ(nullptr, games[1].sprite.get());

    loader();

    EXPECT_NE(nullptr, games[0].sprite.get());
    EXPECT_NE(nullptr, games[1].sprite.get());
}
}
}

NYRA_TEST()
