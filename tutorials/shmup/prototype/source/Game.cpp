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
#include "Game.h"

Game::Game() :
    mWindow(sf::VideoMode(1280, 720), "Shoot 'Em Up")
{
    //mWindow.setFramerateLimit(60);
    mWindow.setMouseCursorVisible(false);
}

void Game::run()
{
    sf::Clock timer;
    float fpsTime = 0.0f;
    int frames = 0;

    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
                return;
            }
        }

        const float delta = timer.restart().asSeconds();
        fpsTime += delta;
        ++frames;

        if (fpsTime >= 1.0f)
        {
            mWindow.setTitle("Shoot 'Em Up " + std::to_string(frames) + " FPS");
            fpsTime = 0.0f;
            frames = 0;
        }

        mLevelJungle.update(delta);

        mWindow.clear(sf::Color(127, 127, 127));
        mLevelJungle.draw(mWindow);
        mWindow.display();
    }

}
