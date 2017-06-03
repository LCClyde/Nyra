#include <iostream>
#include "Game.h"

Game::Game() :
    mWindow(sf::VideoMode(1280, 720), "Shump")
{
    mWindow.setFramerateLimit(60);
}

void Game::run()
{
    sf::Clock timer;
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

        mLevelJungle.update(delta, mWindow);

        mWindow.clear(sf::Color(127, 127, 127));
        mLevelJungle.draw(mWindow);
        mWindow.display();
    }

}
