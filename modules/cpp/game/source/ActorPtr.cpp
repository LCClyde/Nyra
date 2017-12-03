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
#include <nyra/game/ActorPtr.h>
#include <nyra/game/Types.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace game
{
//===========================================================================//
ActorPtr::ActorPtr() :
    mActor(nullptr)
{
}

//===========================================================================//
ActorPtr::ActorPtr(const std::string& filename,
                   const game::Input& input,
                   const graphics::RenderTarget& target,
                   physics::World2D& world) :
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
        mScopedActor.reset(new Actor());
        mActor = mScopedActor.get();
    }

    if (map.has("physics"))
    {
        parsePhysics(map["physics"], world, false);
    }

    if (map.has("trigger"))
    {
        parsePhysics(map["trigger"], world, true);
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

    graphics::Sprite* sprite = nullptr;
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

//===========================================================================//
void ActorPtr::parsePhysics(const mem::Tree<std::string>& map,
                            physics::World2D& world,
                            bool isTrigger)
{
    const std::string stype = map["type"].get();
    physics::Type type = physics::STATIC;

    if (stype == "dynamic")
    {
        type = physics::DYNAMIC;
    }
    else if (stype == "character")
    {
        type = physics::CHARACTER;
    }

    if (isTrigger)
    {
        auto body = world.createTrigger(type, *mActor);
        mActor->getPhysics().addTrigger(body.release());

        if (map.has("onEnter"))
        {
            mActor->getPhysics().setOnEnter(map["onEnter"].get());
        }

        if (map.has("onExit"))
        {
            mActor->getPhysics().setOnExit(map["onExit"].get());
        }
    }
    else
    {
        auto body = world.createBody(type, *mActor, 1.0, 0.3);
        mActor->getPhysics().addBody(body.release());
    }

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
                    circle["offset"]["y"].get());
        }

        mActor->getPhysics().addCircleCollision(radius, offset);
    }

    if (map.has("box"))
    {
        const auto& box = map["box"];

        math::Vector2F size(
                core::str::toType<double>(box["size"]["x"].get()),
                core::str::toType<double>(box["size"]["y"].get()));

        math::Vector2F offset;
        if (box.has("offset"))
        {
            offset.x = core::str::toType<double>(
                    box["offset"]["x"].get());
            offset.y = core::str::toType<double>(
                    box["offset"]["y"].get());
        }

        mActor->getPhysics().addBoxCollision(size, offset);
    }
}

//===========================================================================//
void ActorPtr::parseGui(const mem::Tree<std::string>& map,
                        const input::Mouse& mouse)
{
    Gui* gui = new Gui(mouse);
    parseWidgets(map, gui->get());
    gui->finalize();
    mActor->addGUI(gui);
    mActor->setType(Actor::GUI);
}

//===========================================================================//
void ActorPtr::parseWidgets(const mem::Tree<std::string>& map,
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
            gui::Widget* widget = Gui::addWidget(
                    type, param, name, gui);

            if (wMap.has("size"))
            {
                const math::Vector2F size(
                        core::str::toType<float>(
                                wMap["size"]["width"].get()),
                        core::str::toType<float>(
                                wMap["size"]["height"].get()));
                widget->setSize(size);
            }

            if (wMap.has("position"))
            {
                const math::Vector2F position(
                        core::str::toType<float>(
                                wMap["position"]["x"].get()),
                        core::str::toType<float>(
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

//===========================================================================//
void ActorPtr::parseScript(const mem::Tree<std::string>& map)
{
    const std::string filename = map["filename"].get();
    const std::string className = map["class"].get();
    IncludeT include(filename);
    ObjectT* script = new ObjectT(include, className);

    script::FunctionPtr thisPtr = script->function("nyra_pointer");
    size_t ptr = (*thisPtr)()->get<size_t>();
    mActor = reinterpret_cast<Actor*>(ptr);
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

//===========================================================================//
graphics::Sprite* ActorPtr::parseSprite(
        const mem::Tree<std::string>& map) const
{
    const std::string filename = map["filename"].get();
    const std::string pathname = core::path::join(
            core::DATA_PATH, "textures/" + filename);

    SpriteT* sprite = new SpriteT(pathname);
    mActor->addSprite(sprite);
    return sprite;
}

//===========================================================================//
void ActorPtr::parseTileMap(const mem::Tree<std::string>& map) const
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
    TileMapT* mapPtr = new TileMapT(
            pathname, tiles, tileSize);
    mActor->addTileMap(mapPtr);

    // Check for a navmesh
    if (map.has("collision"))
    {
        std::unordered_set<size_t> collision;
        for (size_t ii = 0; ii < map["collision"].loopSize(); ++ii)
        {
            collision.insert(core::str::toType<size_t>(
                    map["collision"][ii].get()));
        }
        NavMesh* navMesh = new NavMesh(*mapPtr, collision);
        mActor->addNavMesh(navMesh);
    }
}

//===========================================================================//
void ActorPtr::parseCamera(const mem::Tree<std::string>& map,
                           const graphics::RenderTarget& target) const
{
    graphics::Camera2D* camera = new CameraT(target);

    // Move the camera back to zero, just so things are lined up
    camera->setPosition(math::Vector2F());

    mActor->addCamera(camera);
}

//===========================================================================//
void ActorPtr::parseAnimation(const mem::Tree<std::string>& map,
                              graphics::Sprite* sprite) const
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

        if (currAnim.has("type"))
        {
            const std::string type = currAnim["type"].get();
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
                playType = anim::Animation::LOOP;
            }
            else
            {
                throw std::runtime_error(
                        "Unknown animation type: " + type);
            }
        }
        anim::Frame<graphics::Sprite>* anim =
                new anim::Frame<graphics::Sprite>(
                        start, end, duration,
                        playType, frames, *sprite);
        mActor->addAnimation(name, anim);
    }

    if (map.has("initial"))
    {
        const std::string initial = map["initial"].get();
        mActor->playAnimation(initial);
    }
}
}
}
