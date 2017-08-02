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
#ifndef __SHMUP_ACTOR_H__
#define __SHMUP_ACTOR_H__

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <Animation.h>
#include <Texture.h>

class Actor
{
public:
    Actor(const std::string& pathname,
          int rows,
          int columns,
          float x,
          float y,
          float rotation);

    virtual ~Actor() = default;

    void draw(sf::RenderWindow& target);

    void addAnimation(const std::string& name,
                      int start,
                      int end,
                      float time,
                      bool looping = false);

    void playAnimation(const std::string& name);

    virtual void update(float delta);

    void updateOnScreen();

    bool isOnScreen() const
    {
        return mOnScreen && mVisible;
    }

    sf::Sprite& getSprite()
    {
        return mSprite;
    }

    const sf::Vector2f& getSize() const
    {
        return mSize;
    }

    bool collides(const Actor& other);

    void setVelocity(const sf::Vector2f& velocity)
    {
        mVelocity = velocity;
    }

    void hide()
    {
        mVisible = false;
    }

private:
    Texture mTexture;
    sf::Sprite mSprite;
    sf::Vector2f mSize;
    const int mRows;
    const int mColumns;
    Animation* mCurrentAnimation;
    std::unordered_map<std::string, Animation> mAnimations;
    sf::Vector2f mVelocity;
    bool mOnScreen;
    bool mVisible;
};

#endif
