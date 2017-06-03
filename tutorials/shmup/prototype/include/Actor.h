#ifndef __SHMUP_ACTOR_H__
#define __SHMUP_ACTOR_H__

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Actor
{
public:
    Actor(const std::string& pathname,
          int rows,
          int columns);

    void draw(sf::RenderTarget& target);

    void addAnimation(const std::string& name,
                      int start,
                      int end,
                      float time);

    void playAnimation(const std::string& name);

    void update(float delta);

    bool isOnScreen(const sf::View& camera) const;

protected:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Vector2f mSize;

private:
    const int mRows;
    const int mColumns;
    Animation* mCurrentAnimation;
    std::unordered_map<std::string, Animation> mAnimations;
};

#endif
