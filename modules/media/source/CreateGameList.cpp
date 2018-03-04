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
#include <algorithm>
#include <limits>
#include <regex>
#include <nyra/media/CreateGameList.h>
#include <nyra/core/Path.h>
#include <nyra/media/Platform.h>
#include <nyra/zip/Reader.h>
#include <nyra/zip/Verify.h>
#include <nyra/core/String.h>
#include <nyra/media/GamesDb.h>
#include <nyra/core/Time.h>
#include <nyra/media/GameTokens.h>

namespace
{
//===========================================================================//
typedef std::unordered_map<std::string, std::string> FileMap;
const static size_t RETRIES = 15;
const static size_t WAIT_TIME = 16000;

//===========================================================================//
bool sortGame(const nyra::media::Game &a, const nyra::media::Game &b)
{
    return a.rating > b.rating;
}

//===========================================================================//
bool isValid(const std::string& file,
             const std::vector<std::string>& extensions)
{
    for (const std::string& extension : extensions)
    {
        if (file.find(extension) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

//===========================================================================//
std::string getName(const std::string& file)
{
    // TODO: Replace with regex
    std::vector<std::string> parts = nyra::core::str::split(
            nyra::core::path::getBase(file));

    std::string name = parts[0];

    for (size_t ii = 1; ii < parts.size(); ++ii)
    {
        if (parts[ii][0] == '(' || parts[ii][0] == '[')
        {
            break;
        }

        name += " " + parts[ii];
    }

    // Split at " - ". This is used instead of a colon
    parts = nyra::core::str::split(name, " - ");

    for (size_t ii = 0; ii < parts.size(); ++ii)
    {
        if (nyra::core::str::endsWith(parts[ii], ", The"))
        {
            parts[ii] = "The " + name.substr(0, parts[ii].size() - 5);
        }
    }

    // Re-assemble, replacing the first instance of " - " with a colon
    name = parts[0];

    for (size_t ii = 1; ii < parts.size(); ++ii)
    {
        name += ": " + parts[ii];
    }

    return name;
}

//===========================================================================//
FileMap getFileMap(const std::string& path)
{
    std::unordered_map<std::string, std::string> ret;
    const std::vector<std::string> files =
            nyra::core::path::listDirectory(path);
    for (const std::string& file : files)
    {
        ret[getName(file)] = file;
    }

    return ret;
}

//===========================================================================//
struct GameSort
{
    inline bool operator() (const std::string& s1,
                            const std::string& s2)
    {
        return (nyra::media::GameTokens(s1) <
                nyra::media::GameTokens(s2));
    }
};
}

namespace nyra
{
namespace media
{
//===========================================================================//
std::vector<Game> createGameList(const std::string& dataPath,
                                 const std::string& platformName,
                                 bool disableGamesDb)
{
    // Make sure there is a rom dir
    const std::string romsDir =
            core::path::join(dataPath, "roms/" + platformName);
    const std::string artDir =
            core::path::join(dataPath, "textures/" + platformName);
    const std::string videoDir =
            core::path::join(dataPath, "videos/" + platformName);

    if (!core::path::exists(romsDir))
    {
        throw std::runtime_error(romsDir + " does not exist.");
    }

    // Get the platform info
    const std::string platformPathname = core::path::join(
            dataPath, "serial/platform_" + platformName + ".json");
    if (!core::path::exists(platformPathname))
    {
        throw std::runtime_error(platformPathname + " does not exist.");
    }
    const media::Platform platform =
            core::read<media::Platform>(platformPathname);

    // Get the game media maps
    const FileMap boxArt = getFileMap(artDir);
    const FileMap videos = getFileMap(videoDir);

    const std::vector<std::string> potentialRoms =
            core::path::listDirectory(romsDir);
    std::vector<Game> games;

    for (const std::string& potentialRom : potentialRoms)
    {
        std::cout << "Looking at: " << potentialRom << "\n";
        const std::string fullpath(core::path::join(romsDir, potentialRom));
        std::vector<std::string> verifiedZips;
        if (zip::verify(fullpath))
        {
            const std::vector<std::string> zippedFiles =
                    zip::Reader(fullpath).list();
            for (const std::string& zippedFile : zippedFiles)
            {
                if (isValid(zippedFile, platform.extensions))
                {
                    verifiedZips.push_back(zippedFile);
                }
            }

            std::sort(verifiedZips.begin(), verifiedZips.end(), GameSort());
        }

        if (!verifiedZips.empty() || isValid(fullpath, platform.extensions))
        {
            Game game;
            game.zippedFiles = verifiedZips;
            game.name = potentialRom;
            game.filename = potentialRom;
            game.name = getName(potentialRom);

            if (boxArt.find(game.name) != boxArt.end())
            {
                game.boxArtFile = boxArt.at(game.name);
            }

            if (videos.find(game.name) != videos.end())
            {
                game.videoFile = videos.at(game.name);
            }

            games.push_back(game);
        }
    }

    if (!disableGamesDb)
    {
        std::shared_ptr<net::Browser> browser(new net::Browser(
                265, core::path::join(dataPath, "cache"), 100));
        GamesDb gamesDb(browser);

        for (Game& game : games)
        {
            std::cout << "Checking: " << game.name << "\n";
            std::string id;

            for (size_t ii = 0; ii < RETRIES; ++ii)
            {
                try
                {
                    for (size_t jj = 0;
                         jj < platform.gamesDbPlatforms.size();
                         ++jj)
                    {
                        if (!id.empty())
                        {
                            break;
                        }

                        id = gamesDb.getId(
                                game.name, platform.gamesDbPlatforms[jj]);
                    }

                    break;
                }
                catch (const std::exception& ex)
                {
                    if (ii == RETRIES - 1)
                    {
                        throw;
                    }
                    else
                    {
                        std::cout << "Retry on failure: " << ex.what() << "\n";
                        core::sleep(WAIT_TIME);
                    }
                }
            }


            for (size_t ii = 0; ii < RETRIES; ++ii)
            {
                try
                {
                    gamesDb.updateGame(id, game.gamesDb);
                    break;
                }
                catch (const std::exception& ex)
                {
                    if (ii == RETRIES - 1)
                    {
                        throw;
                    }
                    else
                    {
                        std::cout << "Retry on failure: " << ex.what() << "\n";
                        core::sleep(WAIT_TIME);
                    }
                }
            }

            if (id.empty())
            {
                std::cout << "Could not find game info on: " << game.name << "\n";
            }
        }
    }

    // Aggregate ratings
    double minRating = std::numeric_limits<double>::max();
    double maxRating = 0.0;
    for (const Game& game : games)
    {
        minRating = std::min(minRating, game.gamesDb.rating);
        maxRating = std::max(maxRating, game.gamesDb.rating);
    }

    const double deltaRating = maxRating - minRating;

    for (Game& game : games)
    {
        game.rating = (game.gamesDb.rating) / deltaRating;
        game.rating *= 100.0;
    }

    std::sort(games.begin(), games.end(), sortGame);

    return games;
}
}
}
