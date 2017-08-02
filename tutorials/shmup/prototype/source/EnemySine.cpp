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
#include <EnemySine.h>
#include <Math.h>
#include <Level.h>

EnemySine::EnemySine(float x, float y):
    Ship("enemy_01.png", 3, 1, x, y, 180.0f),
    mTotalTime(0.0f),
    mDefaultY(y),
    mAmplitude(100.0f),
    mFrequency(4.0f)
{
    addAnimation("idle", 1, 1, 1.0f);
    playAnimation("idle");
}

void EnemySine::updateImpl(float delta)
{
    mTotalTime += delta;
    sf::Vector2f position = getSprite().getPosition();
    position.x -= 200.0f * delta;
    position.y = std::sin(mTotalTime * pi * mFrequency) * mAmplitude + mDefaultY;
    getSprite().setPosition(position);
}

float EnemySine::fire()
{
    Level::spawnBullet(new Bullet("bullet_simple.png",
                                  1, 1,
                                  getSprite().getPosition().x,
                                  getSprite().getPosition().y,
                                  180.0f,
                                  1.0f),
                       sf::Vector2f(500.0f, 0.0f),
                       false);
    return 0.25;
}
