/*
 * Copyright (c) 2017 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef __NYRA_GAME_ACTOR_PTR_H__
#define __NYRA_GAME_ACTOR_PTR_H__

#include <nyra/game/Actor.h>
#include <nyra/game/Input.h>
#include <nyra/game/Types.h>

namespace nyra
{
namespace game
{
/*
 *  \class ActorPtr
 *  \brief Wrapper class around Actor that can accept either a python actor
 *         or a c++ actor.
 */
class ActorPtr
{
public:
    /*
     *  \func Constructor
     *  \brief Necessary to create auto generated functions.
     */
    ActorPtr();

    /*
     *  \func Constructor
     *  \brief Creates an Actor from a filename
     *
     *  \param filename The filename without the path.
     */
    ActorPtr(const std::string& filename,
             const game::Input& input,
             const graphics::RenderTarget& target,
             physics::World2D& world);

    /*
     *  \func get
     *  \brief Gets the underlying actor
     *
     *  \return The actor pointer.
     */
    Actor* get() const
    {
        return mActor;
    }

    bool operator<(const ActorPtr& other) const
    {
        return get()->getLayer() < other.get()->getLayer();
    }

private:
    //=======================================================================//
    void parsePhysics(const mem::Tree<std::string>& map,
                      physics::World2D& world);

    //=======================================================================//
    void parseGui(const mem::Tree<std::string>& map,
                  const input::Mouse& mouse);

    //=======================================================================//
    void parseWidgets(const mem::Tree<std::string>& map,
                      mem::Tree<gui::Widget>& gui);

    //=======================================================================//
    void parseScript(const mem::Tree<std::string>& map);

    //=======================================================================//
    graphics::Sprite* parseSprite(const mem::Tree<std::string>& map) const;

    //=======================================================================//
    void parseTileMap(const mem::Tree<std::string>& map) const;

    //=======================================================================//
    void parseCamera(const mem::Tree<std::string>& map,
                     const graphics::RenderTarget& target) const;

    //=======================================================================//
    void parseAnimation(const mem::Tree<std::string>& map,
                        graphics::Sprite* sprite) const;

    //=======================================================================//
    Actor* mActor;
    std::shared_ptr<Actor> mScopedActor;
};
}
}

#endif
