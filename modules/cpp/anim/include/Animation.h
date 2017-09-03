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
#ifndef __NYRA_ANIM_ANIMATION_H__
#define __NYRA_ANIM_ANIMATION_H__

namespace nyra
{
namespace anim
{
/*
 *  \class Animation
 *  \brief A base animation class to allow for polymorphism.
 */
class Animation
{
public:
    /*
     *  \enum PlayType
     *  \brief Used to determine the play type for this animation.
     *
     *  \value ONCE The animation plays onces.
     *  \value LOOP The animation restarts after finishing.
     *  \value PING_PONG The animation plays forward then plays backwards
     *         it then repeats this process until destroyed.
     */
    enum PlayType
    {
        ONCE,
        LOOP,
        PING_PONG
    };

    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~Animation() = default;

    /*
     *  \func update
     *  \brief Updates an animation.
     *
     *  \param deltaTime The time that has passed since the last animation
     *         update.
     */
    virtual void update(double deltaTime) = 0;

protected:
    void initialize(double duration,
                    PlayType playType);

    double normalizeTime(double deltaTime);

private:
    void updatePing(double& deltaTime);

    void updatePong(double& deltaTime);

    PlayType mPlayType;
    double mDuration;
    double mElapsed;

    enum PingPong
    {
        PING,
        PONG
    };

    PingPong mPingPong;
};
}
}

#endif
