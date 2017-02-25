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
#include <nyra/media/Game.h>
#include <nyra/json/JSON.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace media
{
//===========================================================================//
Game::GamesDb::GamesDb() :
    rating(0.0)
{
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Game::GamesDb& game)
{
    os << "\nGamesDb Data:\n"
       << "    ID:       " << game.id << "\n"
       << "    Rating:   " << game.rating;

   if (!game.youtube.empty())
   {
       os << "\n    YouTube:  " << game.youtube;
   }

   if (!game.fanArt.empty())
   {
       os << "\n    Fan Art:";
       for (const std::string& art : game.fanArt)
       {
           os << "\n         " << art;
       }
   }

   if (!game.boxArt.empty())
   {
       os << "\n    Box Art:";
       for (const std::string& art : game.boxArt)
       {
           os << "\n         " << art;
       }
   }

   if (!game.bannerArt.empty())
   {
       os << "\n    Banner:";
       for (const std::string& art : game.bannerArt)
       {
           os << "\n         " << art;
       }
   }

    return os;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << "Name: " << game.name << "\n"
       << "Filename: " << game.filename << "\n"
       << "Box Art: " << game.boxArtFile << "\n"
       << "Video: " << game.videoFile;

    if (!game.zippedFiles.empty())
    {
        os << "\nZipped Files:";
        for (const std::string& zip : game.zippedFiles)
        {
            os << "\n    " << zip;
        }
    }

    if (!game.gamesDb.id.empty())
    {
        os << game.gamesDb;
    }

    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<std::vector<media::Game> >(const std::vector<media::Game>& games,
                                      const std::string& pathname,
                                      core::ArchiveType type)
{
    json::JSON tree;
    tree["games"] = std::string();

    for (size_t ii = 0; ii < games.size(); ++ii)
    {
        tree["games"][ii] = std::string();
        tree["games"][ii]["name"] = games[ii].name;
        tree["games"][ii]["filename"] = games[ii].filename;
        tree["games"][ii]["box_art"] = games[ii].boxArtFile;
        tree["games"][ii]["video"] = games[ii].videoFile;

        if (!games[ii].zippedFiles.empty())
        {
            tree["games"][ii]["zip"] = "";
            for (size_t jj = 0; jj < games[ii].zippedFiles.size(); ++jj)
            {
                tree["games"][ii]["zip"][jj] = games[ii].zippedFiles[jj];
            }
        }

        tree["games"][ii]["games_db"] = "";
        tree["games"][ii]["games_db"]["id"] = games[ii].gamesDb.id;
        tree["games"][ii]["games_db"]["rating"] =
                core::str::toString(games[ii].gamesDb.rating);
        tree["games"][ii]["games_db"]["youtube"] = games[ii].gamesDb.youtube;

        if (!games[ii].gamesDb.boxArt.empty())
        {
            tree["games"][ii]["games_db"]["box_art"] = "";
            for (size_t jj = 0; jj < games[ii].gamesDb.boxArt.size(); ++jj)
            {
                tree["games"][ii]["games_db"]["box_art"][jj] =
                        games[ii].gamesDb.boxArt[jj];
            }
        }

        if (!games[ii].gamesDb.fanArt.empty())
        {
            tree["games"][ii]["games_db"]["fan_art"] = "";
            for (size_t jj = 0; jj < games[ii].gamesDb.fanArt.size(); ++jj)
            {
                tree["games"][ii]["games_db"]["fan_art"][jj] =
                        games[ii].gamesDb.fanArt[jj];
            }
        }

        if (!games[ii].gamesDb.bannerArt.empty())
        {
            tree["games"][ii]["games_db"]["banner_art"] = "";
            for (size_t jj = 0; jj < games[ii].gamesDb.bannerArt.size(); ++jj)
            {
                tree["games"][ii]["games_db"]["banner_art"][jj] =
                        games[ii].gamesDb.bannerArt[jj];
            }
        }
    }


    core::write(tree, pathname);
}

//===========================================================================//
template <>
void read<std::vector<media::Game> >(const std::string& pathname,
                                     std::vector<media::Game>& games,
                                     core::ArchiveType type)
{
    const json::JSON tree = core::read<json::JSON>(pathname);

    for (size_t ii = 0; ii < tree["games"].size(); ++ii)
    {
        media::Game game;
        game.name = tree["games"][ii]["name"].get();
        game.filename = tree["games"][ii]["filename"].get();
        game.boxArtFile = tree["games"][ii]["box_art"].get();
        game.videoFile = tree["games"][ii]["video"].get();

        if (tree["games"][ii].has("zip"))
        {
            for (size_t jj = 0;
                 jj < tree["games"][ii]["zip"].loopSize();
                 ++jj)
            {
                game.zippedFiles.push_back(
                        tree["games"][ii]["zip"][jj].get());
            }
        }

        const auto& gamesDb = tree["games"][ii]["games_db"];
        game.gamesDb.id = gamesDb["id"].get();
        game.gamesDb.rating =
                core::str::toType<double>(gamesDb["rating"].get());
        game.gamesDb.youtube = gamesDb["youtube"].get();

        if (gamesDb.has("box_art"))
        {
            for (size_t jj = 0; jj < gamesDb["box_art"].loopSize(); ++jj)
            {
                game.gamesDb.boxArt.push_back(
                        gamesDb["box_art"][jj].get());
            }
        }

        if (gamesDb.has("fan_art"))
        {
            for (size_t jj = 0; jj < gamesDb["fan_art"].loopSize(); ++jj)
            {
                game.gamesDb.fanArt.push_back(
                        gamesDb["fan_art"][jj].get());
            }
        }

        if (gamesDb.has("banner_art"))
        {
            for (size_t jj = 0; jj < gamesDb["banner_art"].loopSize(); ++jj)
            {
                game.gamesDb.bannerArt.push_back(
                        gamesDb["banner_art"][jj].get());
            }
        }

        games.push_back(game);
    }
}
}
}
