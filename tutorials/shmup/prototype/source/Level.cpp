#include <Level.h>

Level::Level() :
    mCamera(sf::Vector2f(1280.0f / 2.0f, 720.0f / 2.0f),
            sf::Vector2f(1280.0f, 720.0f))
{
}

void Level::update(float delta,
                   sf::RenderTarget& target)
{
    mCamera.move(50.0f * delta, 0.0f);
    target.setView(mCamera);

    mPlayer.update(mCamera, delta);

    for (auto& enemy : mEnemies)
    {
        enemy->update(mCamera, delta);
    }
}

void Level::draw(sf::RenderTarget& target)
{
    mPlayer.draw(target);

    for (auto& enemy : mEnemies)
    {
        enemy->draw(target);
    }
}
