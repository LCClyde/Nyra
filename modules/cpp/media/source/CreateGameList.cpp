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
#include <nyra/media/CreateGameList.h>
#include <nyra/core/Path.h>
#include <nyra/media/Platform.h>
#include <nyra/zip/Reader.h>
#include <nyra/zip/Verify.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
typedef std::unordered_map<std::string, std::string> FileMap;

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
    const std::vector<std::string> parts = nyra::core::str::split(
            nyra::core::path::getBase(file));

    std::string name = parts[0];

    for (size_t ii = 1; ii < parts.size(); ++ii)
    {
        if (parts[ii][0] == '(' || parts[ii][0] == '[')
        {
            return name;
        }

        if (ii > 0)
        {
            name += " ";
        }

        name += parts[ii];
    }

    return name;
}

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
}

namespace nyra
{
namespace media
{
//===========================================================================//
std::vector<Game> createGameList(const std::string& dataPath,
                                 const std::string& platformName)
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

    return games;
}
}
}
