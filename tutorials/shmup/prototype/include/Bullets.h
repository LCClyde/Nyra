#ifndef __SHMUP_BULLETS_H__
#define __SHMUP_BULLETS_H__

#include <memory>
#include <vector>
#include "Bullet.h"

class Bullets
{
public:
    void addBullet(Bullet* bullet);

    void update(const sf::View& camera,
                float delta);

    void draw(sf::RenderTarget& target);

private:
    std::vector<std::unique_ptr<Bullet>> mBullets;
};

#endif
