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
#include <nyra/game/Input.h>
#include <nyra/physics/World.h>

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
             const game::Input<GameT>& input,
             const graphics::RenderTarget& target,
             typename GameT::Physics::World& world) :
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

        if (map.has("physics"))
        {
            parsePhysics(map["physics"], world);
        }

        if (map.has("gui"))
        {
            parseGui(map["gui"], input.getMouse());
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

        if (map.has("layer"))
        {
            const int32_t layer = core::str::toType<int32_t>(
                    map["layer"].get());
            mActor->setLayer(layer);
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

    bool operator<(const ActorPtr& other) const
    {
        return get()->getLayer() < other.get()->getLayer();
    }

private:
    void parsePhysics(const mem::Tree<std::string>& map,
                      typename GameT::Physics::World& world)
    {
        const std::string stype = map["type"].get();
        physics::Type type = physics::STATIC;

        if (stype == "dynamic")
        {
            type = physics::DYNAMIC;
        }

        auto body = world.createBody(type, *mActor, 1.0, 0.3);
        mActor->addBody(body.release());

        if (map.has("circle"))
        {
            const auto& circle = map["circle"];
            const double radius = core::str::toType<double>(
                    circle["radius"].get());
            math::Vector2F offset;
            if (circle.has("offset"))
            {
                offset.x = core::str::toType<double>(
                        circle["offset"]["x"].get());
                offset.y = core::str::toType<double>(
                        circle["offset"]["x"].get());
            }
            mActor->addCircleCollision(radius, offset);
        }
    }

    void parseGui(const mem::Tree<std::string>& map,
                  const input::Mouse& mouse)
    {
        Gui<GameT>* gui = new Gui<GameT>(mouse);
        parseWidgets(map, gui->get());
        gui->finalize();
        mActor->addGUI(gui);
    }

    void parseWidgets(const mem::Tree<std::string>& map,
                      mem::Tree<gui::Widget>& gui)
    {
        if (map.has("widget"))
        {
            for (size_t ii = 0; ii < map["widget"].loopSize(); ++ii)
            {
                const auto& wMap = map["widget"][ii];
                const std::string type = wMap["type"].get();
                const std::string name = wMap["name"].get();
                std::string param;

                if (wMap.has("text"))
                {
                    param = wMap["text"].get();
                }
                gui::Widget* widget = Gui<GameT>::addWidget(
                        type, param, name, gui);

                if (wMap.has("size"))
                {
                    const math::Vector2F size(
                            core::str::toType<size_t>(
                                    wMap["size"]["width"].get()),
                            core::str::toType<size_t>(
                                    wMap["size"]["height"].get()));
                    widget->setSize(size);
                }

                if (wMap.has("position"))
                {
                    const math::Vector2F position(
                            core::str::toType<size_t>(
                                    wMap["position"]["x"].get()),
                            core::str::toType<size_t>(
                                    wMap["position"]["y"].get()));
                    widget->setPosition(position);
                }

                if (wMap.has("activated"))
                {
                    const std::string onPressed = wMap["activated"].get();
                    mActor->setActivatedFunction(onPressed, widget->activated);
                }

                parseWidgets(wMap, gui[name]);
            }
        }
    }

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

        if (map.has("initialize"))
        {
            mActor->setInitializeFunction(map["initialize"].get());
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
        mActor->addRenderable(mapPtr);

        // Check for a navmesh
        if (map.has("collision"))
        {
            std::unordered_set<size_t> collision;
            for (size_t ii = 0; ii < map["collision"].loopSize(); ++ii)
            {
                collision.insert(core::str::toType<size_t>(
                        map["collision"][ii].get()));
            }
            NavMesh<GameT>* navMesh = new NavMesh<GameT>(*mapPtr, collision);
            mActor->addNavMesh(navMesh);
        }
    }

    //=======================================================================//
    void parseCamera(const mem::Tree<std::string>& map,
                     const graphics::RenderTarget& target) const
    {
        typename GameT::Graphics::Camera* camera =
                new typename GameT::Graphics::Camera(target);

        // Move the camera back to zero, just so things are lined up
        camera->setPosition(math::Vector2F());

        mActor->addRenderable(camera);
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
