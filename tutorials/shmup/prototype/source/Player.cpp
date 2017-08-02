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
#include <Player.h>
#include <Camera.h>
#include <Math.h>
#include <Level.h>

//===========================================================================//
Player::Player() :
    Ship("player.png", 5, 1, 200.0f, 320.0f, 0.0f),
    mLocalPosition(-300.0f, 0.0f),
    mWeapon(EXPLOSION),
    mLaser(nullptr),
    mDelta(0.0f),
    mChargeTime(0.0f)
{
    addAnimation("idle", 2, 2, 1.0f);
    addAnimation("up", 1, 0, 0.5f);
    addAnimation("down", 3, 4, 0.5f);

    playAnimation("idle");
}

//===========================================================================//
void Player::updateImpl(float delta)
{
    mDelta = delta;
    sf::Vector2f move;
    move.x += sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    move.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    move.y += sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    move.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    normalize(move);
    setVelocity((move * 500.0f) + Level::getCamera().getVelocity());

    if (move.y > 0.0f)
    {
        playAnimation("down");
    }
    else if (move.y < 0.0f)
    {
        playAnimation("up");
    }
    else
    {
        playAnimation("idle");
    }
}

//===========================================================================//
float Player::fire()
{
    const sf::Vector2f position = getSprite().getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        switch (mWeapon)
        {
        case NORMAL:
            Level::spawnBullet(new Bullet("bullet_simple.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          0.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            return 0.5f;

        case EXPLOSION:
            Level::spawnBullet(new Bullet("bullet_exploding.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          0.0f,
                                          1.0f),
                               sf::Vector2f(650.0f, 0.0f),
                               true);
            return 0.8f;

        case RAPID:
            Level::spawnBullet(new Bullet("bullet_rapid.png",
                                          1, 1,
                                          position.x,
                                          position.y - 35.0f,
                                          0.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            Level::spawnBullet(new Bullet("bullet_rapid.png",
                                          1, 1,
                                          position.x,
                                          position.y + 35.0f,
                                          0.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            return 0.1f;

        case SCATTER:
            Level::spawnBullet(new Bullet("bullet_simple.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          5.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            Level::spawnBullet(new Bullet("bullet_simple.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          15.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            Level::spawnBullet(new Bullet("bullet_simple.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          -5.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            Level::spawnBullet(new Bullet("bullet_simple.png",
                                          1, 1,
                                          position.x,
                                          position.y,
                                          -15.0f,
                                          1.0f),
                               sf::Vector2f(1000.0f, 0.0f),
                               true);
            return 0.6f;

        case CHARGE:
            mChargeTime += mDelta;
            return 0.0f;

        case LASER:
            if (!mLaser)
            {
                mLaser = new Bullet("bullet_laser.png",
                                    1, 1,
                                    position.x,
                                    position.y,
                                    0.0f,
                                    1.0f);
                const sf::Vector2f& origin = mLaser->getSprite().getOrigin();
                mLaser->getSprite().setOrigin(0.0f, origin.y);
                mLaser->getSprite().setScale(100.0f, 1.0f);
                Level::spawnBullet(mLaser, sf::Vector2f(0.0f, 0.0f), true);
            }
            mLaser->getSprite().setPosition(getSprite().getPosition());
            return 0.0f;

        case FLAME:
            {
                for (size_t ii = 0; ii < 5; ++ii)
                {
                    float random = ((float)rand()) / (float)RAND_MAX;
                    float diff = 30.0f;
                    float r = random * diff;
                    Bullet* bullet = new Bullet("bullet_flame.png",
                                               1, 13,
                                               position.x,
                                               position.y,
                                               -15.0f +  r,
                                               1.0f);
                    bullet->addAnimation("idle", 0, 12, 1.5f);
                    bullet->playAnimation("idle");
                    Level::spawnBullet(bullet,
                                       sf::Vector2f(500.0f, 0.0f),
                                       true);
                }
            }
            return 0.05f;
        }

    }
    else
    {
        switch (mWeapon)
        {
        case LASER:
            if (mLaser)
            {
                Level::despawnBullet(mLaser, true);
                mLaser = nullptr;
            }
            break;

        case CHARGE:
            if (mChargeTime > 0.0f)
            {
                if (mChargeTime < 1.0f)
                {
                    Bullet* bullet = new Bullet("bullet_charge_small.png",
                                                1, 1,
                                                position.x,
                                                position.y,
                                                0.0f,
                                                1.0f);
                    Level::spawnBullet(bullet,
                                       sf::Vector2f(1000.0f, 0.0f),
                                       true);
                }
                else if (mChargeTime < 2.0f)
                {
                    Bullet* bullet = new Bullet("bullet_charge_mid.png",
                                                3, 1,
                                                position.x,
                                                position.y,
                                                0.0f,
                                                1.0f);
                    bullet->addAnimation("idle", 0, 2, 0.2f, true);
                    bullet->playAnimation("idle");
                    Level::spawnBullet(bullet,
                                       sf::Vector2f(1000.0f, 0.0f),
                                       true);
                }
                else
                {
                    Bullet* bullet = new Bullet("bullet_charge_large.png",
                                                2, 1,
                                                position.x,
                                                position.y,
                                                0.0f,
                                                1.0f);
                    bullet->addAnimation("idle", 0, 1, 0.1f, true);
                    bullet->playAnimation("idle");
                    Level::spawnBullet(bullet,
                                       sf::Vector2f(1000.0f, 0.0f),
                                       true);
                }
                mChargeTime = 0.0f;
            }
            break;
        default:
            break;
        }
    }

    return 0.0f;

}

//===========================================================================//
void Player::hit()
{
    getSprite().setPosition(-100.0f, -100.0f);
}
