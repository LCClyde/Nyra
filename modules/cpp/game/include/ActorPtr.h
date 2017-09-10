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

#include <stddef.h>
#include <nyra/game/Actor.h>

namespace nyra
{
namespace game
{
/*
 *  \class ActorPtr
 *  \brief Wrapper class around Actor that can accept either a python actor
 *         or a c++ actor.
 *
 *  \tparam GameT The game type
 */
template <typename GameT>
class ActorPtr
{
public:
    /*
     *  \func Constructor
     *  \brief Necessary to create auto generated functions.
     */
    ActorPtr() :
        mActor(nullptr)
    {
    }

    /*
     *  \func Constructor
     *  \brief Creates an Actor from a filename
     *
     *  \param filename The filename without the path.
     */
    ActorPtr(const std::string& filename,
             const graphics::RenderTarget& target) :
        mActor(nullptr)
    {
        const json::JSON map = core::read<json::JSON>(
                core::path::join(core::DATA_PATH, "actors/" + filename));

        if (map.has("script"))
        {
            parseScript(map["script"]);
        }
        else
        {
            mScopedActor.reset(new Actor<GameT>());
            mActor = mScopedActor.get();
        }

        if (map.has("tile_map"))
        {
            for (size_t ii = 0; ii < map["tile_map"].loopSize(); ++ii)
            {
                parseTileMap(map["tile_map"][ii]);
            }
        }

        typename GameT::Graphics::Sprite* sprite = nullptr;
        if (map.has("sprite"))
        {
            if (map["sprite"].loopSize() > 1)
            {
                throw std::runtime_error(
                        "TODO: Cannot support more than 1 "
                        "sprite on an actor.");
            }

            for (size_t ii = 0; ii < map["sprite"].loopSize(); ++ii)
            {
                sprite = parseSprite(map["sprite"][ii]);
            }
        }

        if (map.has("camera"))
        {
            parseCamera(map["camera"], target);
        }

        // For now we know we only have one sprite per actor
        if (map.has("animation"))
        {
            parseAnimation(map["animation"], sprite);
        }
    }

    /*
     *  \func get
     *  \brief Gets the underlying actor
     *
     *  \return The actor pointer.
     */
    Actor<GameT>* get() const
    {
        return mActor;
    }

private:
    //=======================================================================//
    void parseScript(const mem::Tree<std::string>& map)
    {
        const std::string filename = map["filename"].get();
        const std::string className = map["class"].get();
        typename GameT::Script::Include include(filename);
        typename GameT::Script::Object* script =
                new typename GameT::Script::Object(include, className);

        script::FunctionPtr thisPtr = script->function("nyra_pointer");
        size_t ptr = (*thisPtr)()->get<size_t>();
        mActor = reinterpret_cast<Actor<GameT>*>(ptr);
        mActor->setScript(script);

        if (map.has("update"))
        {
            mActor->setUpdateFunction(map["update"].get());
        }
    }

    //=======================================================================//
    typename GameT::Graphics::Sprite*
            parseSprite(const mem::Tree<std::string>& map) const
    {
        const std::string filename = map["filename"].get();
        const std::string pathname = core::path::join(
                core::DATA_PATH, "textures/" + filename);

        typename GameT::Graphics::Sprite* sprite =
                new typename GameT::Graphics::Sprite(pathname);
        mActor->addRenderable(sprite);
        return sprite;
    }

    //=======================================================================//
    void parseTileMap(const mem::Tree<std::string>& map) const
    {
        const std::string filename = map["filename"].get();
        const std::string name =
                map.has("name") ? map["name"].get() : "";

        math::Vector2U tileSize(
                core::str::toType<size_t>(
                        map["tile_size"]["width"].get()),
                core::str::toType<size_t>(
                        map["tile_size"]["height"].get()));
        math::Vector2U mapSize(map["tiles"][0].loopSize(),
                               map["tiles"].loopSize());
        mem::Buffer2D<size_t> tiles(mapSize);

        for (size_t row = 0; row < tiles.getNumRows(); ++row)
        {
            for (size_t col = 0; col < tiles.getNumCols(); ++col)
            {
                tiles(col, row) = core::str::toType<size_t>(
                        map["tiles"][row][col].get());
            }
        }

        const std::string pathname = core::path::join(
                core::DATA_PATH, "textures/" + filename);
        graphics::TileMap<typename GameT::Graphics::Sprite>* mapPtr =
                new graphics::TileMap<typename GameT::Graphics::Sprite>(
                        pathname,
                        tiles,
                        tileSize);
        mActor->addRenderable(mapPtr, name);
    }

    //=======================================================================//
    void parseCamera(const mem::Tree<std::string>& map,
                     const graphics::RenderTarget& target) const
    {
        const std::string name =
                map.has("name") ? map["name"].get() : "";

        typename GameT::Graphics::Camera* camera =
                new typename GameT::Graphics::Camera(target);

        // Move the camera back to zero, just so things are lined up
        camera->setPosition(math::Vector2F());

        mActor->addRenderable(camera, name);
    }

    //=======================================================================//
    void parseAnimation(const mem::Tree<std::string>& map,
                        typename GameT::Graphics::Sprite* sprite) const
    {
        // TODO: Support different frames for each animation
        const math::Vector2U frames(
                core::str::toType<size_t>(
                        map["frames"]["cols"].get()),
                core::str::toType<size_t>(
                        map["frames"]["rows"].get()));

        for (size_t ii = 0; ii < map["anims"].loopSize(); ++ii)
        {
            const auto& currAnim = map["anims"][ii];
            const std::string name = currAnim["name"].get();
            const size_t start = core::str::toType<size_t>(
                    currAnim["start"].get());
            const size_t end = core::str::toType<size_t>(
                    currAnim["end"].get());
            const double duration = core::str::toType<double>(
                    currAnim["duration"].get());
            anim::Animation::PlayType playType = anim::Animation::LOOP;

            if (map.has("type"))
            {
                const std::string type = map["type"].get();
                if (type == "ping_pong")
                {
                    playType = anim::Animation::PING_PONG;
                }
                else if (type == "once")
                {
                    playType = anim::Animation::ONCE;
                }
                else if (type == "loop")
                {
                    playType = anim::Animation::ONCE;
                }
                else
                {
                    throw std::runtime_error(
                            "Unknown animation type: " + type);
                }
            }
            anim::Frame* anim =
                    new anim::Frame(start, end, duration,
                                    playType, frames, *sprite);
            mActor->addAnimation(name, anim);
        }

        if (map.has("initial"))
        {
            const std::string initial = map["initial"].get();
            mActor->playAnimation(initial);
        }
    }

    //=======================================================================//
    Actor<GameT>* mActor;
    std::shared_ptr<Actor<GameT>> mScopedActor;
};
}
}

#endif
