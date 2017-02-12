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
#ifndef __NYRA_MEDIA_PLAY_GAME_H__
#define __NYRA_MEDIA_PLAY_GAME_H__

#include <nyra/media/Screen.h>
#include <nyra/media/Types.h>
#include <nyra/process/BackgroundSubprocess.h>

namespace nyra
{
namespace media
{
/*
 *  \class PlayGame
 *  \brief Screen that appears when a user is playing a game.
 */
class PlayGame : public Screen
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the play game screen object
     *
     *  \param commandLine The command line parameters for opening the
     *         target executable
     *  \param pathname The pathname of the rom to open.
     *  \param target The render target
     *  \param keyboard The keyboard for input
     */
    PlayGame(const GameCommandLine& commandLine,
             const std::string& pathname,
             const Config& config,
             graphics::RenderTarget& target,
             input::Keyboard& keyboard);

    /*
     *  \func update
     *  \brief Updates the screen
     *
     *  \param delta The time in seconds since the last update
     */
    void update(double delta) override;

    /*
     *  \func render
     *  \brief Renders the screen
     */
    void render() override;

private:
    process::BackgroundSubprocess mProcess;
};
}
}

#endif
