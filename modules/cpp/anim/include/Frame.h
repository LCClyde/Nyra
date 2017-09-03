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
#ifndef __NYRA_ANIM_FRAME_H__
#define __NYRA_ANIM_FRAME_H__

#include <nyra/graphics/Sprite.h>
#include <nyra/anim/Interpolate.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace anim
{
/*
 *  \class Frame
 *  \brief Applies frame to frame animations to a sprite.
 */
class Frame : public Animation
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the animation
     *
     *  \param startFrame The starting frame number (1D)
     *  \param endFrame The ending frame number (1D)
     *  \param duration The animation time in seconds
     *  \param playType How should the animation handle finishing?
     *  \param numTiles The number of tiles in the image
     *  \param sprite The sprite that will be modified
     */
    Frame(size_t startFrame,
          size_t endFrame,
          double duration,
          Animation::PlayType playType,
          const math::Vector2U& numTiles,
          graphics::Sprite& sprite);

    /*
     *  \func update
     *  \brief Updates the animation
     *
     *  \param deltaTime The time in seconds to increment by
     */
    void update(double deltaTime) override;

    /*
     *  \func reset
     *  \brief Returns back to the starting frame
     */
    void reset() override;

private:
    const math::Vector2U mSize;
    std::vector<math::Vector2U> mFrames;
    graphics::Sprite& mSprite;
    size_t mCurrentFrame;
    Interpolate<size_t> mInterpolate;
};
}
}

#endif
