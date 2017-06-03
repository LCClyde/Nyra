#include <EnemyForwardAttack.h>
#include <Bullet.h>

EnemyForwardAttack::EnemyForwardAttack(float x, float y) :
    Enemy("enemy_01.png", 3, 1, x, y, 0.5f)
{
    addAnimation("idle", 1, 1, 1.0f);
    playAnimation("idle");
}

void EnemyForwardAttack::updateImpl(float delta)
{
    mSprite.move(-50.0f * delta, 0.0f);
}

void EnemyForwardAttack::fire()
{
    mBullets.addBullet(new Bullet(mSprite.getPosition(), 500.0f, 180.0f));
}
