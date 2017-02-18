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
#include <nyra/media/Game.h>

namespace
{
//===========================================================================//
bool compare(const nyra::media::Game& g1, const nyra::media::Game& g2)
{
    return g1.name == g2.name &&
           g1.filename == g2.filename &&
           g1.boxArtFile == g2.boxArtFile &&
           g1.videoFile == g2.videoFile &&
           g1.zippedFiles == g2.zippedFiles;
}
}

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(Game, Archive)
{
    std::vector<Game> games;

    Game game;
    games.push_back(game);

    game.name = "Mario";
    game.filename = "mario.bin";

    games.push_back(game);

    game.boxArtFile = "mario.png";
    games.push_back(game);

    game.boxArtFile = "";
    game.videoFile = "mario.mp4";
    games.push_back(game);

    game.boxArtFile = "mario.png";
    games.push_back(game);

    const std::vector<std::string> zips = {"a", "b", "c"};
    game.zippedFiles = zips;
    games.push_back(game);

    const std::vector<Game> archived = test::archive(games);

    for (size_t ii = 0; ii < games.size(); ++ii)
    {
        EXPECT_TRUE(compare(archived[ii], games[ii]));
    }
}

//===========================================================================//
TEST(Game, Stdout)
{
    Game game;
    game.name = "Mario";
    game.filename = "mario.bin";
    game.boxArtFile = "mario.png";
    game.videoFile = "mario.mp4";
    game.boxArtFile = "mario.png";
    game.zippedFiles = {"a", "b", "c"};

    const std::string expected =
            "Name: Mario\n"
            "Filename: mario.bin\n"
            "Box Art: mario.png\n"
            "Video: mario.mp4\n"
            "Zipped Files:\n"
            "    a\n"
            "    b\n"
            "    c";

    EXPECT_EQ(expected, test::stdout(game));
}
}
}

NYRA_TEST()
