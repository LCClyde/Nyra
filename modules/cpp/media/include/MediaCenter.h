/*
 * Copyright (c) 2016 Clyde Stanfield
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
#ifndef __NYRA_MEDIA_MEDIA_CENTER_H__
#define __NYRA_MEDIA_MEDIA_CENTER_H__

#include <nyra/win/sfml/Window.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/media/GameList.h>
#include <nyra/input/sfml/Keyboard.h>


namespace nyra
{
namespace media
{
/*
 *  \class MediaCenter
 *  \brief Top Level class for running the media center
 */
class MediaCenter
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the Media Center
     *
     *  \param scale Scales up or down the window
     */
    MediaCenter(double scale);

    /*
     *  \func run
     *  \brief Runs the media center. This is a blocking function.
     */
    void run();

private:
    win::sfml::Window mWindow;
    graphics::sfml::RenderTarget mRenderTarget;
    input::sfml::Keyboard mKeyboard;
    media::GameList mGames;
};
}
}

#endif

