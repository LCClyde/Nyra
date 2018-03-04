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
#ifndef __NYRA_GRAPHICS_VIDEO_H__
#define __NYRA_GRAPHICS_VIDEO_H__

#include <string>
#include <nyra/graphics/Renderable.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class Video
 *  \brief Class used for playing pre-rendered videos.
 */
class Video : public Renderable<math::Transform2D>
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    virtual ~Video() = default;

    /*
     *  \func initialize
     *  \brief Sets up the video for playback. The video is not valid until
     *         this is called.
     *
     *  \param pathname The location of the video on disk.
     */
    virtual void initialize(const std::string& pathname) = 0;

    /*
     *  \func play
     *  \brief Begin playback.
     */
    virtual void play() = 0;

    /*
     *  \func pause
     *  \brief Pauses the video
     */
    virtual void pause() = 0;

    /*
     *  \func stop
     *  \brief Stops the video.
     */
    virtual void stop() = 0;

    /*
     *  \func update
     *  \brief Updates the video playback.
     */
    virtual void update() = 0;
};
}
}

#endif
