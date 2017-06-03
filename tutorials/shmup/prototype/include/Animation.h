#ifndef __SHMUP_ANIMATION_H__
#define __SHMUP_ANIMATION_H__

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation() = default;

    Animation(int rows,
              int columns,
              int start,
              int end,
              float time,
              sf::Sprite& sprite);

    void update(float delta);

    void reset();

private:
    void setRect();

    int mRows;
    int mColumns;
    int mStart;
    int mEnd;
    float mTimePerFrame;
    float mCurrentTime;
    int mCurrentFrame;
    sf::Sprite* mSprite;
    int mRectWidth;
    int mRectHeight;
    int mDirection;
};

#endif
