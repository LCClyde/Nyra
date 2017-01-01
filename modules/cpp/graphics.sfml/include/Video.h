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
#ifndef __NYRA_GRAPHICS_SFML_VIDEO_H__
#define __NYRA_GRAPHICS_SFML_VIDEO_H__

#include <sfeMovie/Movie.hpp>
#include <nyra/graphics/Video.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
/*
 *  \class Video
 *  \brief Class used for playing pre-rendered videos for SFML
 */
class Video : public graphics::Video
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the video for playback.
     *
     *  \param pathname The location of the video on disk.
     */
    Video(const std::string& pathname);

    /*
     *  \func initialize
     *  \brief Sets up the video for playback. The video is not valid until
     *         this is called.
     *
     *  \param pathname The location of the video on disk.
     */
    void initialize(const std::string& pathname) override;

    /*
     *  \func play
     *  \brief Begin playback.
     */
    void play() override;

    /*
     *  \func pause
     *  \brief Pauses the video
     */
    void pause() override;

    /*
     *  \func stop
     *  \brief Stops the video.
     */
    void stop() override;

    /*
     *  \func update
     *  \brief Updates the video playback.
     */
    void update() override;

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override;

private:
    sfe::Movie mVideo;
};
}
}
}

#endif
