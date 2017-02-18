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

namespace nyra
{
namespace media
{
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
        tree["games"][ii]["zip"] = std::string();

        for (size_t jj = 0; jj < games[ii].zippedFiles.size(); ++jj)
        {
            tree["games"][ii]["zip"][jj] = games[ii].zippedFiles[jj];
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
            for (size_t jj = 0; jj < tree["games"][ii]["zip"].size(); ++jj)
            {
                game.zippedFiles.push_back(
                        tree["games"][ii]["zip"][jj].get());
            }
        }

        games.push_back(game);
    }
}
}
}
