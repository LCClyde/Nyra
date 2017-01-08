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
#ifndef __NYRA_MEDIA_TYPES_H__
#define __NYRA_MEDIA_TYPES_H__

#include <string>
#include <unordered_map>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace media
{
/*
 *  \class GameMediaFiles
 *  \brief Files related to the game
 */
struct GameMediaFiles
{
    /*
     *  \var boxArtFile
     *  \brief The name of the box art
     */
    std::string boxArtFile;

    /*
     *  \var videoFile
     *  \brief The name of the video file
     */
    std::string videoFile;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(boxArtFile);
        archive & BOOST_SERIALIZATION_NVP(videoFile);
    }
};

/*
 *  \class GameCommandLine
 *  \brief Holds command line information about opening a game subprocess.
 */
struct GameCommandLine
{
    /*
     *  \var binary
     *  \brief The full path to the binary
     */
    std::string binary;

    /*
     *  \var args
     *  \brief The arguments to send to the command.
     */
    std::vector<std::string> args;

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(binary);
        archive & BOOST_SERIALIZATION_NVP(args);
    }
};

/*
 *  \type FileToName
 *  \brief Converts a filename to a game name
 */
typedef std::unordered_map<std::string, std::string> FileToName;

/*
 *  \type NameToMediaFiles
 *  \brief Converts a game name to a GameMediaFile
 */
typedef std::unordered_map<std::string, GameMediaFiles> NameToMediaFiles;

/*
 *  \type PlatformToBinary
 *  \brief Converts a platfrom to a command line.
 */
typedef std::unordered_map<std::string, GameCommandLine> PlatformToBinary;
}
}

#endif
