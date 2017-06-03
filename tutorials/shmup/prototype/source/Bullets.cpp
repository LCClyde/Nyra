#include <iostream>
#include <Bullets.h>

void Bullets::addBullet(Bullet* bullet)
{
    mBullets.push_back(std::unique_ptr<Bullet>(bullet));
}

void Bullets::update(const sf::View& camera, float delta)
{
    for (auto iter = mBullets.begin(); iter != mBullets.end();)
    {
        (*iter)->update(delta);

        if (!(*iter)->isOnScreen(camera))
        {
            std::cout << "offscreen\n";
            iter = mBullets.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void Bullets::draw(sf::RenderTarget& target)
{
    for (const auto& bullet : mBullets)
    {
        bullet->draw(target);
    }
}
