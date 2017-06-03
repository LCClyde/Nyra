#include <Actor.h>
#include <iostream>

Actor::Actor(const std::string& pathname,
             int rows,
             int columns) :
    mRows(rows),
    mColumns(columns),
    mCurrentAnimation(nullptr)
{
    mTexture.loadFromFile("data/textures/" + pathname);
    mSprite.setTexture(mTexture);
    mSize.x = mTexture.getSize().x / mColumns;
    mSize.y = mTexture.getSize().y / mRows;
    mSprite.setOrigin(mSize / 2.0f);
}

void Actor::draw(sf::RenderTarget& target)
{
    target.draw(mSprite);
}

void Actor::addAnimation(const std::string& name,
                         int start,
                         int end,
                         float time)
{
    mAnimations[name] = Animation(mRows, mColumns, start, end, time, mSprite);
}

void Actor::playAnimation(const std::string& name)
{
    Animation* newAnim = &mAnimations[name];
    if (newAnim != mCurrentAnimation)
    {
        mCurrentAnimation = newAnim;
        mCurrentAnimation->reset();
    }
}

void Actor::update(float delta)
{
    if (mCurrentAnimation)
    {
        mCurrentAnimation->update(delta);
    }
}

bool Actor::isOnScreen(const sf::View& camera) const
{
    const sf::Vector2f position = mSprite.getPosition();
    const sf::FloatRect sprite(position.x - mSize.x / 2.0f,
                               position.y - mSize.y / 2.0f,
                               mSize.x,
                               mSize.y);

    const sf::Vector2f camSize = camera.getSize();
    const sf::FloatRect cam(camera.getCenter().x - camSize.x / 2.0f,
                            camera.getCenter().y - camSize.y / 2.0f,
                            camSize.x,
                            camSize.y);

    return cam.intersects(sprite);
}
