#include "Bullet.h"
#include "Utils.h"

Bullet::Bullet(const sf::Vector2f& position,
               float speed,
               float rotation) :
    Actor("bullet_simple.png", 1, 1),
    mVelocty(rotate(sf::Vector2f(1.0f, 0.0f), rotation) * speed)
{
    mSprite.setPosition(position);
    mSprite.setRotation(rotation);
}

void Bullet::update(float delta)
{
    mSprite.move(mVelocty * delta);
    Actor::update(delta);
}
