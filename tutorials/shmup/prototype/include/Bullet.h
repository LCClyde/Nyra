#ifndef __SHMUP_BULLET_H__
#define __SHMUP_BULLET_H__

#include "Actor.h"

class Bullet : public Actor
{
public:
    Bullet(const sf::Vector2f& position,
           float speed,
           float rotation);

    void update(float delta);

private:
    const sf::Vector2f mVelocty;
};

#endif
