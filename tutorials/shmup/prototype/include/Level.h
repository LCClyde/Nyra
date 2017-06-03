#ifndef __SHMUP_LEVEL_H__
#define __SHMUP_LEVEL_H__

#include <vector>
#include <memory>
#include "Enemy.h"
#include "Player.h"

class Level
{
public:
    Level();

    void update(float delta,
                sf::RenderTarget& target);

    void draw(sf::RenderTarget& target);

protected:
    template <typename T>
    void addEnemy(float x, float y)
    {
        mEnemies.push_back(std::unique_ptr<T>(new T(x, y)));
    }

private:
    Player mPlayer;
    std::vector<std::unique_ptr<Enemy> > mEnemies;
    sf::View mCamera;
};

#endif
