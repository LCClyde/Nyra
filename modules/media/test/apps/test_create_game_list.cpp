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
#include <nyra/media/CreateGameList.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(CreateGameList, Create)
{
    std::vector<Game> games =
            createGameList(core::DATA_PATH, "mtest", true);

    bool found[3] = {false, false, false};

    for (const Game& game : games)
    {
        if (game.name == "game 1")
        {
            EXPECT_EQ("game 1.bin", game.filename);
            EXPECT_EQ("", game.boxArtFile);
            EXPECT_EQ("", game.videoFile);
            EXPECT_EQ(std::vector<std::string>(), game.zippedFiles);
            found[0] = true;
        }
        else if (game.name == "game 2")
        {
            EXPECT_EQ("game 2.bin", game.filename);
            EXPECT_EQ("game 2.png", game.boxArtFile);
            EXPECT_EQ("game 2.mp4", game.videoFile);
            EXPECT_EQ(std::vector<std::string>(), game.zippedFiles);
            found[1] = true;
        }
        else if (game.name == "game 3")
        {
            EXPECT_EQ("game 3.7z", game.filename);
            EXPECT_EQ("game 3.png", game.boxArtFile);
            EXPECT_EQ("game 3.mp4", game.videoFile);
            const std::vector<std::string> expectedZip = {
                    "game 3 (U) [!].bin",
                    "game 3 (U) [b0].bin",
                    "game 3 (U) [b1].bin"};
            EXPECT_EQ(expectedZip, game.zippedFiles);
            found[2] = true;
        }
        else
        {
            throw std::runtime_error("Found unknown game: " + game.name);
        }
    }

    EXPECT_TRUE(found[0]);
    EXPECT_TRUE(found[1]);
    EXPECT_TRUE(found[2]);
}
}
}

NYRA_TEST()
