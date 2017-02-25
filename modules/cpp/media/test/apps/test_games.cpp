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
           g1.zippedFiles == g2.zippedFiles &&
           g1.gamesDb.id == g2.gamesDb.id &&
           g1.gamesDb.rating == g2.gamesDb.rating &&
           g1.gamesDb.youtube == g2.gamesDb.youtube &&
           g1.gamesDb.boxArt == g2.gamesDb.boxArt &&
           g1.gamesDb.fanArt == g2.gamesDb.fanArt &&
           g1.gamesDb.bannerArt == g2.gamesDb.bannerArt;
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

    game.zippedFiles = {"a"};
    games.push_back(game);

    game.zippedFiles = {"a", "b", "c"};
    games.push_back(game);

    game.gamesDb.id = "140";
    game.gamesDb.youtube = "youtube";
    game.gamesDb.rating = 8.5;
    game.gamesDb.fanArt = {"f1"};

    // Makes sure looping is correct for 1 or 0 sized art vectors
    games.push_back(game);

    game.gamesDb.boxArt = {"b1", "b2", "b3"};
    game.gamesDb.fanArt = {"f1", "f2", "f3", "f4"};
    game.gamesDb.bannerArt = {"bn1", "bn2"};
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

    std::string expected =
            "Name: Mario\n"
            "Filename: mario.bin\n"
            "Box Art: mario.png\n"
            "Video: mario.mp4\n"
            "Zipped Files:\n"
            "    a\n"
            "    b\n"
            "    c";

    EXPECT_EQ(expected, test::stdout(game));

    game.gamesDb.id = "140";
    game.gamesDb.youtube = "youtube";
    game.gamesDb.rating = 8.5;
    game.gamesDb.boxArt = {"b1", "b2", "b3"};
    game.gamesDb.fanArt = {"f1", "f2", "f3", "f4"};
    game.gamesDb.bannerArt = {"bn1", "bn2"};

    expected +=
            "\nGamesDb Data:\n"
            "    ID:       140\n"
            "    Rating:   8.5\n"
            "    YouTube:  youtube\n"
            "    Fan Art:\n"
            "         f1\n"
            "         f2\n"
            "         f3\n"
            "         f4\n"
            "    Box Art:\n"
            "         b1\n"
            "         b2\n"
            "         b3\n"
            "    Banner:\n"
            "         bn1\n"
            "         bn2";

    EXPECT_EQ(expected, test::stdout(game));
}
}
}

NYRA_TEST()
