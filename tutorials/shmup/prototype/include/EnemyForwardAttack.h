#include "Enemy.h"

class EnemyForwardAttack : public Enemy
{
public:
    EnemyForwardAttack(float x, float y);

private:
    void updateImpl(float delta) override;

    void fire() override;
};
