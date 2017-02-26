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
#ifndef __NYRA_MEDIA_GAME_H__
#define __NYRA_MEDIA_GAME_H__

#include <vector>
#include <string>
#include <nyra/graphics/Sprite.h>

namespace nyra
{
namespace media
{

/*
 *  \class Game
 *  \brief Struct to hold game information.
 */
struct Game
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a default Game object.
     */
    Game();

    /*
     *  \class GamesDb
     *  \brief Holds onto TheGamesDb.net information.
     */
    struct GamesDb
    {
        GamesDb();

        /*
         *  \var id
         *  \brief The identification for the game
         */
        std::string id;

        /*
         *  \var rating
         *  \brief The user rating from 0-10
         */
        double rating;

        /*
         *  \var youtube
         *  \brief Link to a youtube video of the game
         */
        std::string youtube;

        /*
         *  \var fanArt
         *  \brief A list of available fan art.
         */
        std::vector<std::string> fanArt;
        /*
         *  \var boxArt
         *  \brief A list of available box art.
         */
        std::vector<std::string> boxArt;

        /*
         *  \var baannerArt
         *  \brief A list of available banner art.
         */
        std::vector<std::string> bannerArt;

    private:
        friend std::ostream& operator<<(std::ostream& os,
                                        const GamesDb& game);
    };

    /*
     *  \var sprite
     *  \brief Sprite to represent the game, usually box art.
     */
    std::shared_ptr<graphics::Sprite> sprite;

    /*
     *  \var name
     *  \brief Name of the game
     */
    std::string name;

    /*
     *  \var filename
     *  \brief The filename of the game (no directory)
     */
    std::string filename;

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

    /*
     *  \var zippedFiles
     *  \brief The files contained within the file. If the file is not a
     *         zip, this vector will be empty.
     */
    std::vector<std::string> zippedFiles;

    /*
     *  \var rating
     *  \brief The aggregated rating of the game from 0 - 100
     */
    double rating;

    /*
     *  \var gamesDb
     *  \brief TheGamesDb.net information.
     */
    GamesDb gamesDb;

private:
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes a list of Games to file.
 *
 *  \param games The list of games to save
 *  \param pathname The location to save to.
 *  \param type This will only write json, even if you select something
 *         else
 */
template <>
void write<std::vector<media::Game> >(const std::vector<media::Game>& games,
                                      const std::string& pathname,
                                      core::ArchiveType type);

/*
 *  \func read
 *  \brief Reads a list of Games from file.
 *
 *  \param pathname The location to save to.
 *  \param games The games to load
 *  \param type This will only read json, even if you select something
 *         else
 */
template <>
void read<std::vector<media::Game> >(const std::string& pathname,
                                     std::vector<media::Game>& games,
                                     core::ArchiveType type);
}
}

#endif
