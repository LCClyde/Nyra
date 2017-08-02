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
#ifndef __SHMUP_LEVEL_H__
#define __SHMUP_LEVEL_H__

#include <vector>
#include <memory>
#include <Camera.h>
#include <Player.h>
#include <Ship.h>
#include <Bullet.h>

typedef std::vector<std::unique_ptr<Actor>> ActorList;
typedef std::vector<std::unique_ptr<Bullet>> BulletList;

class Level
{
public:
    Level(const std::string& name);

    void update(float delta);

    void draw(sf::RenderWindow& target);

    static void spawnBullet(Bullet* bullet,
                            const sf::Vector2f& velocity,
                            bool player);

    static void despawnBullet(Bullet* bullet, bool player);

    static const Camera& getCamera()
    {
        return mGlobal->mCamera;
    }

protected:
    template <typename T>
    void addEnemy(float x, float y)
    {
        mEnemies.push_back(std::unique_ptr<T>(new T(x, y)));
    }

private:
    void handleCollisions();

    static void updateBullets(float delta, BulletList& bullets);

    BulletList& getBullets(bool player);

    Camera mCamera;
    Camera mUI;
    Player mPlayer;
    BulletList mPlayerBullets;
    ActorList mEnemies;
    BulletList mEnemyBullets;
    ActorList mBackground;

    static Level* mGlobal;
};

#endif
