#include <LevelJungle.h>
#include <EnemyForwardAttack.h>

LevelJungle::LevelJungle() :
    Level()
{
    addEnemy<EnemyForwardAttack>(1400.0f, 200.0f);
}
