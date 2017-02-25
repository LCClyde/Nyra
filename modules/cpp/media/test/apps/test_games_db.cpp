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
#include <nyra/media/GamesDb.h>
#include <nyra/core/Path.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(GamesDb, GetID)
{
    // CMake has trouble with this crazy filename. So instead
    // we save off the contents and copy it before running.
    // We do this to speed up the test and pinging TheGameDb is
    // too time consuming.
    const std::string realFilename = "GetGame.php?name=Super%20Mario%20Bros.&"
                                     "platform=Nintendo%20Entertainment"
                                     "%20System%20%28NES%29";
    const std::string basePath =
            core::path::join(core::DATA_PATH,
                             "misc/media_cache/thegamesdb.net/api/");
    const std::string savedPathname = core::path::join(basePath, "GetGameId");
    const std::string actualPathname =
            core::path::join(basePath, realFilename);

    std::ifstream src(savedPathname, std::ios::binary);
    std::ofstream dst(actualPathname, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    const std::string timestampPathname = actualPathname + ".timestamp";
    std::ofstream timestamp(timestampPathname);

    // Current time plus 1 hour
    timestamp << core::epoch() + 360000;
    timestamp.close();

    std::shared_ptr<net::Browser> browser(new net::Browser(
            360, core::path::join(core::DATA_PATH, "misc/media_cache")));

    GamesDb gamesDb(browser);

    const std::string id = gamesDb.getId(
            "Super Mario Bros.",
            "Nintendo Entertainment System (NES)");

    EXPECT_EQ("140", id);
}

//===========================================================================//
TEST(GamesDb, UpdateGame)
{
    // CMake has trouble with this crazy filename. So instead
    // we save off the contents and copy it before running.
    // We do this to speed up the test and pinging TheGameDb is
    // too time consuming.
    const std::string realFilename = "GetGame.php?id=140";
    const std::string basePath =
            core::path::join(core::DATA_PATH,
                             "misc/media_cache/thegamesdb.net/api/");
    const std::string savedPathname =
            core::path::join(basePath, "UpdateGame");
    const std::string actualPathname =
            core::path::join(basePath, realFilename);

    std::ifstream src(savedPathname, std::ios::binary);
    std::ofstream dst(actualPathname, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    const std::string timestampPathname = actualPathname + ".timestamp";
    std::ofstream timestamp(timestampPathname);

    // Current time plus 1 hour
    timestamp << core::epoch() + 360000;
    timestamp.close();

    std::shared_ptr<net::Browser> browser(new net::Browser(
            360, core::path::join(core::DATA_PATH, "misc/media_cache")));

    GamesDb gamesDb(browser);

    Game game;
    gamesDb.updateGame("140", game.gamesDb);

    EXPECT_EQ("140", game.gamesDb.id);
    EXPECT_EQ(7.9048, game.gamesDb.rating);
    EXPECT_EQ("http://www.youtube.com/watch?v=7qirrV8w5SQ",
              game.gamesDb.youtube);
    EXPECT_EQ(static_cast<size_t>(13), game.gamesDb.fanArt.size());
    EXPECT_EQ(static_cast<size_t>(2), game.gamesDb.boxArt.size());
    EXPECT_EQ(static_cast<size_t>(3), game.gamesDb.bannerArt.size());
}

}
}

NYRA_TEST()
