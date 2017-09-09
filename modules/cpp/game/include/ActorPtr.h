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
        static const std::string DATA = core::DATA_PATH;
        const json::JSON tree = core::read<json::JSON>(
                core::path::join(DATA, "actors/" + filename));

        if (tree.has("script"))
        {
            const auto& scriptXML = tree["script"];
            const std::string filename = scriptXML["filename"].get();
            const std::string className = scriptXML["class"].get();
            typename GameT::Script::Include include(filename);
            typename GameT::Script::Object* script =
                    new typename GameT::Script::Object(include, className);

            script::FunctionPtr thisPtr = script->function("nyra_pointer");
            size_t ptr = (*thisPtr)()->get<size_t>();
            mActor = reinterpret_cast<Actor<GameT>*>(ptr);
            mActor->setScript(script);

            if (scriptXML.has("update"))
            {
                mActor->setUpdateFunction(scriptXML["update"].get());
            }
        }
        else
        {
            mScopedActor.reset(new Actor<GameT>());
            mActor = mScopedActor.get();
        }

        if (tree.has("tile_map"))
        {
            for (size_t ii = 0; ii < tree["tile_map"].loopSize(); ++ii)
            {
                const auto& tileMap = tree["tile_map"][ii];
                const std::string filename = tileMap["filename"].get();
                const std::string name =
                        tileMap.has("name") ? tileMap["name"].get() : "";

                math::Vector2U tileSize(
                        core::str::toType<size_t>(
                                tileMap["tile_size"]["width"].get()),
                        core::str::toType<size_t>(
                                tileMap["tile_size"]["height"].get()));
                math::Vector2U mapSize(tileMap["tiles"][0].loopSize(),
                                       tileMap["tiles"].loopSize());
                mem::Buffer2D<size_t> tiles(mapSize);

                for (size_t row = 0; row < tiles.getNumRows(); ++row)
                {
                    for (size_t col = 0; col < tiles.getNumCols(); ++col)
                    {
                        tiles(col, row) = core::str::toType<size_t>(
                                tileMap["tiles"][row][col].get());
                    }
                }

                const std::string pathname = core::path::join(
                        DATA, "textures/" + filename);
                graphics::TileMap<typename GameT::Graphics::Sprite>* mapPtr =
                        new graphics::TileMap<typename GameT::Graphics::Sprite>(
                                pathname,
                                tiles,
                                tileSize);
                mActor->addRenderable(mapPtr, name);
            }
        }

        typename GameT::Graphics::Sprite* sprite = nullptr;
        if (tree.has("sprite"))
        {
            if (tree["sprite"].loopSize() > 1)
            {
                throw std::runtime_error(
                        "TODO: Cannot support more than 1 "
                        "sprite on an actor.");
            }

            for (size_t ii = 0; ii < tree["sprite"].loopSize(); ++ii)
            {
                const auto& spriteMap = tree["sprite"][ii];
                const std::string filename = spriteMap["filename"].get();
                const std::string pathname = core::path::join(
                        DATA, "textures/" + filename);

                sprite = new typename GameT::Graphics::Sprite(pathname);
                mActor->addRenderable(sprite);
            }
        }

        if (tree.has("camera"))
        {
            const auto& camMap = tree["camera"];
            const std::string name =
                    camMap.has("name") ? camMap["name"].get() : "";

            typename GameT::Graphics::Camera* camera =
                    new typename GameT::Graphics::Camera(target);

            // Move the camera back to zero, just so things are lined up
            camera->setPosition(math::Vector2F());

            mActor->addRenderable(camera, name);
        }

        // For now we know we only have one sprite per actor
        if (tree.has("animation"))
        {
            const auto& animMap = tree["animation"];

            // TODO: Support different frames for each animation
            const math::Vector2U frames(
                    core::str::toType<size_t>(
                            animMap["frames"]["cols"].get()),
                    core::str::toType<size_t>(
                            animMap["frames"]["rows"].get()));

            for (size_t ii = 0; ii < animMap["anims"].loopSize(); ++ii)
            {
                const auto& currAnim = animMap["anims"][ii];
                const std::string name = currAnim["name"].get();
                const size_t start = core::str::toType<size_t>(
                        currAnim["start"].get());
                const size_t end = core::str::toType<size_t>(
                        currAnim["end"].get());
                const double duration = core::str::toType<double>(
                        currAnim["duration"].get());
                anim::Animation::PlayType playType = anim::Animation::LOOP;

                if (animMap.has("type"))
                {
                    const std::string type = animMap["type"].get();
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

            if (animMap.has("initial"))
            {
                const std::string initial = animMap["initial"].get();
                mActor->playAnimation(initial);
            }
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
    Actor<GameT>* mActor;
    std::shared_ptr<Actor<GameT>> mScopedActor;
};
}
}

#endif
