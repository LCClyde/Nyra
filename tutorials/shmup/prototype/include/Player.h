#ifndef __SHMUP_PLAYER_H__
#define __SHMUP_PLAYER_H__

#include "Actor.h"
#include "Bullets.h"
#include "KeyPress.h"

class Player : public Actor
{
public:
    Player();

    void update(const sf::View& camera,
                float delta);

    void draw(sf::RenderTarget& target);

private:
    const float mSpeed;
    Bullets mBullets;
    KeyPress mShootKey;
    sf::Vector2f mLocalPosition;
};

#endif
