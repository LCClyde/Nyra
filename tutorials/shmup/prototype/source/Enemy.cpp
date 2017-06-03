#include "Enemy.h"


Enemy::Enemy(const std::string& pathname,
             int rows,
             int columns,
             float x,
             float y,
             float shootSpeed) :
    Actor(pathname, rows, columns),
    mShootSpeed(shootSpeed),
    mPrevTime(0.0f)
{
    mSprite.setPosition(x, y);
    mSprite.setRotation(180.0f);
}

void Enemy::update(const sf::View& camera, float delta)
{
    if (isOnScreen(camera))
    {
        updateImpl(delta);

        mPrevTime += delta;
        if (mPrevTime >= mShootSpeed)
        {
            mPrevTime = 0.0f;
            fire();
        }

        Actor::update(delta);
        mBullets.update(camera, delta);
    }
}

void Enemy::draw(sf::RenderTarget& target)
{
    mBullets.draw(target);
    Actor::draw(target);
}
