#ifndef __SHMUP_ENEMY_H__
#define __SHMUP_ENEMY_H__

#include <Actor.h>
#include <Bullets.h>

class Enemy : public Actor
{
public:
    Enemy(const std::string& pathname,
          int rows,
          int columns,
          float x,
          float y,
          float shootSpeed);

    virtual ~Enemy() = default;

    void update(const sf::View& camera,
                float delta);

    void draw(sf::RenderTarget& target);

private:
    virtual void updateImpl(float delta) = 0;

    virtual void fire() = 0;

protected:
    Bullets mBullets;
    const float mShootSpeed;
    float mPrevTime;
};

#endif
