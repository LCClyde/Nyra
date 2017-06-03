#include <iostream>
#include "Player.h"
#include "Utils.h"

Player::Player() :
    Actor("player.png", 5, 1),
    mSpeed(500.0f),
    mShootKey(sf::Keyboard::Space),
    mLocalPosition(-300.0f, 0.0f)
{
    addAnimation("idle", 2, 2, 1.0f);
    addAnimation("up", 1, 0, 0.5f);
    addAnimation("down", 3, 4, 0.5f);

    playAnimation("idle");
    mSprite.setPosition(mLocalPosition);
}

void Player::update(const sf::View& camera,
                    float delta)
{
    sf::Vector2f move;
    move.x += sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    move.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    move.y += sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    move.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    normalize(move);
    mLocalPosition += move * mSpeed * delta;
    mSprite.setPosition(camera.getCenter() + mLocalPosition);

    if (move.y > 0.0f)
    {
        playAnimation("down");
    }
    else if (move.y < 0.0f)
    {
        playAnimation("up");
    }
    else
    {
        playAnimation("idle");
    }

    if (mShootKey.get())
    {
        mBullets.addBullet(new Bullet(mSprite.getPosition(), 1000.0f, 0.0f));
    }

    mBullets.update(camera, delta);

    Actor::update(delta);
}

void Player::draw(sf::RenderTarget& target)
{
    mBullets.draw(target);
    Actor::draw(target);
}
