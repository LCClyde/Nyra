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
#ifndef __NYRA_MEDIA_GAMES_DB_H__
#define __NYRA_MEDIA_GAMES_DB_H__

#include <string>
#include <memory>
#include <nyra/net/Browser.h>
#include <nyra/media/Game.h>

namespace nyra
{
namespace media
{
/*
 *  \class GamesDb
 *  \brief A class used to obtain information from TheGamesDb.net
 */
class GamesDb
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the GamesDb object.
     *
     *  \param browser The configured browser to use.
     */
    GamesDb(std::shared_ptr<net::Browser> browser);

    /*
     *  \func getId
     *  \brief Gets the identification of a game
     *
     *  \param name The name of the game
     *  \param platform The GamesDb platform name
     */
    std::string getId(const std::string& name,
                      const std::string& platform) const;

    /*
     *  \func updateGame
     *  \brief Updates a game from a known ID
     *
     *  \param id The GamesDb id
     *  \param game [OUTPUT] The game to update.
     */
    void updateGame(const std::string& id, Game::GamesDb& game) const;

private:
    std::shared_ptr<net::Browser> mBrowser;
    const std::string mSite;
};
}
}

#endif

