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
#include <Level.h>
#include <Math.h>

//===========================================================================//
Level* Level::mGlobal = nullptr;

//===========================================================================//
Level::Level(const std::string& name)
{
    mGlobal = this;

    mBackground.resize(10);
    for (size_t ii = 0; ii < mBackground.size(); ++ii)
    {
        mBackground[ii].reset(new Actor(
                name + "_" + std::to_string(ii) + ".png",
                1, 1, ii * 1280, 720.0f / 2.0f, 0.0f));
        mBackground[ii]->getSprite().setColor(sf::Color(128, 128, 128));
    }
}

//===========================================================================//
void Level::update(float delta)
{
    mCamera.update(delta);

    for (auto& background : mBackground)
    {
        background->update(delta);
    }

    updateBullets(delta, mPlayerBullets);
    updateBullets(delta, mEnemyBullets);

    mPlayer.update(delta);

    for (auto& enemy : mEnemies)
    {
        enemy->update(delta);
    }

    handleCollisions();
}

//===========================================================================//
void Level::draw(sf::RenderWindow& target)
{
    mCamera.setActive(target);

    for (auto& background : mBackground)
    {
        background->draw(target);
    }

    for (auto& bullet : mPlayerBullets)
    {
        bullet.get()->draw(target);
    }

    for (auto& bullet : mEnemyBullets)
    {
        bullet.get()->draw(target);
    }

    for (auto& enemy : mEnemies)
    {
        enemy->draw(target);
    }

    mPlayer.draw(target);

    mUI.setActive(target);
}

//===========================================================================//
void Level::handleCollisions()
{
    for (const auto& bullet : mPlayerBullets)
    {
        for (const auto& enemy : mEnemies)
        {
            if (enemy->collides(*bullet))
            {
                dynamic_cast<Ship*>(enemy.get())->hit();
            }
        }
    }

    for (const auto& bullet : mEnemyBullets)
    {
        if (mPlayer.collides(*bullet))
        {
            mPlayer.hit();
        }
    }
}

//===========================================================================//
BulletList& Level::getBullets(bool player)
{
    if (player)
    {
        return mPlayerBullets;
    }
    return mEnemyBullets;
}

//===========================================================================//
void Level::spawnBullet(Bullet* bullet,
                        const sf::Vector2f& velocity,
                        bool player)
{
    bullet->setVelocity(rotate(
            velocity, bullet->getSprite().getRotation()));
    mGlobal->getBullets(player).push_back(std::unique_ptr<Bullet>(bullet));
}

//===========================================================================//
void Level::despawnBullet(Bullet* bullet, bool player)
{
    BulletList& bullets = mGlobal->getBullets(player);

    for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
    {
        if (iter->get() == bullet)
        {
            bullets.erase(iter);
            return;
        }
    }
}

//===========================================================================//
void Level::updateBullets(float delta,
                          BulletList& bullets)
{
    for (auto iter = bullets.begin(); iter != bullets.end();)
    {
        (*iter)->update(delta);

        if (!(*iter)->isOnScreen())
        {
            iter = bullets.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}
