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
#include <iostream>
#include <Actor.h>
#include <Camera.h>
#include <Level.h>

//===========================================================================//
Actor::Actor(const std::string& pathname,
             int rows,
             int columns,
             float x,
             float y,
             float rotation) :
    mTexture(pathname),
    mRows(rows),
    mColumns(columns),
    mCurrentAnimation(nullptr),
    mOnScreen(false),
    mVisible(true)
{
    mSprite.setTexture(mTexture.getTexture());
    mSize.x = mTexture.getTexture().getSize().x / mColumns;
    mSize.y = mTexture.getTexture().getSize().y / mRows;
    mSprite.setOrigin(mSize / 2.0f);
    mSprite.setPosition(x, y);
    mSprite.setRotation(rotation);
}

//===========================================================================//
void Actor::draw(sf::RenderWindow& target)
{
    if (mOnScreen && mVisible)
    {
        target.draw(mSprite);
    }
}

//===========================================================================//
void Actor::addAnimation(const std::string& name,
                         int start,
                         int end,
                         float time,
                         bool looping)
{
    mAnimations[name] = Animation(mRows, mColumns, start,
                                  end, time, looping, mSprite);
}

//===========================================================================//
void Actor::playAnimation(const std::string& name)
{
    Animation* newAnim = &mAnimations[name];
    if (newAnim != mCurrentAnimation)
    {
        mCurrentAnimation = newAnim;
        mCurrentAnimation->reset();
    }
}

//===========================================================================//
void Actor::update(float delta)
{
    if (mCurrentAnimation)
    {
        mCurrentAnimation->update(delta);
    }

    mSprite.move(mVelocity * delta);

    updateOnScreen();
}

//===========================================================================//
void Actor::updateOnScreen()
{
    mOnScreen = mSprite.getGlobalBounds().intersects(
            Level::getCamera().getRect());
}

//===========================================================================//
bool Actor::collides(const Actor& other)
{
    sf::FloatRect intersection;
    if (mSprite.getGlobalBounds().intersects(
            other.mSprite.getGlobalBounds(),
            intersection))
    {
        const sf::IntRect& subRect = mSprite.getTextureRect();
        const sf::IntRect& otherSubRect = other.mSprite.getTextureRect();
        int pix = 0;

        for (float ii = intersection.left;
             ii < intersection.left + intersection.width;
             ++ii)
        {
            for (float jj = intersection.top;
                 jj < intersection.top + intersection.height;
                 ++jj)
            {
                const sf::Vector2f vec1 =
                        mSprite.getInverseTransform().transformPoint(ii, jj);
                const sf::Vector2f vec2 =
                        other.mSprite.getInverseTransform().transformPoint(ii, jj);

                if (vec1.x > 0.0f  && vec1.y > 0.0f &&
                    vec2.x > 0.0f && vec2.y > 0.0f &&
                    vec1.x < subRect.width && vec1.y < subRect.height &&
                    vec2.x < otherSubRect.width && vec2.y < otherSubRect.height)
                {
                    if (mTexture.isPixel(vec1.x + subRect.left, vec1.y + subRect.top) &&
                        other.mTexture.isPixel(vec2.x + otherSubRect.left, vec2.y + otherSubRect.top))
                    {
                        if (++pix > 256)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
