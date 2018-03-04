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
#ifndef __NYRA_MEDIA_GAME_SELECTION_SCREEN_H__
#define __NYRA_MEDIA_GAME_SELECTION_SCREEN_H__

#include <string>
#include <vector>
#include <thread>
#include <nyra/graphics/Video.h>
#include <nyra/media/Game.h>
#include <nyra/media/Screen.h>
#include <nyra/media/GameListLayout.h>
#include <nyra/media/BoxArtList.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
/*
 *  \class GameSelectionScreen
 *  \brief Screen to list and select games
 */
class GameSelectionScreen : public Screen
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the game list
     *
     *  \param pathname The pathname to the game list
     *  \param target The render target
     *  \param keyboard The keyboard for input
     */
    GameSelectionScreen(const std::string& platform,
                        const Config& config,
                        graphics::RenderTarget& target,
                        input::Keyboard& keyboard);

    /*
     *  \func update
     *  \brief Updates the game list
     *
     *  \param delta The time in seconds since the last update
     */
    void update(double delta) override;

    /*
     *  \func render
     *  \brief Renders the game list
     */
    void render() override;

    /*
     *  \func getGame
     *  \brief Gets the currently selected game
     *
     *  \return The current game
     */
    const Game& getGame() const
    {
        return mGames[mIndex];
    }

    /*
     *  \func getGamePathname
     *  \brief Gets the pathname to the game on disk
     *
     *  \return The pathname to the game.
     */
    const std::string getGamePathname() const
    {
        return core::path::join(mGamePath, mGames[mIndex].filename);
    }

private:
    void updateIndex();

    void playVideo();

    const std::string mGamePath;
    const std::string mPlatform;
    std::vector<Game> mGames;
    std::unique_ptr<graphics::Video> mVideo;
    int64_t mIndex;
    GameListLayout mLayout;
    BoxArtList mBoxArt;
    std::thread mBoxArtLoaderThread;

};
}
}

#endif

