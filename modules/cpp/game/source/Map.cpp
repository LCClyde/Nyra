/*
* Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/game/Map.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace game
{
//===========================================================================//
Map* Map::mMap = nullptr;

//===========================================================================//
Map::Map(const game::Input& input,
         const graphics::RenderTarget& target) :
    mInput(input),
    mTarget(target),
    // TODO: This should be a part of config params
    mWorld(64.0, 0.0, 60.0),
    mRenderCollision(false),
    mCamera(nullptr)
{
    mMap = this;
}

//===========================================================================//
void Map::update(double delta)
{
    for (size_t ii = 0; ii < mActors.size(); ++ii)
    {
        mActors[ii].get()->update(delta);
    }

    // Add new actors
    if (!mSpawnedActors.empty())
    {
        for (size_t ii = 0; ii < mSpawnedActors.size(); ++ii)
        {
            mActors.push_back(mSpawnedActors[ii]);
        }

        mSpawnedActors.clear();
    }

    if (mWorld.update(delta))
    {
        for (size_t ii = 0; ii < mActors.size(); ++ii)
        {
            mActors[ii].get()->getPhysics().update();
        }
    }

    for (size_t ii = 0; ii < mActors.size(); ++ii)
    {
        mActors[ii].get()->updateTransform();
    }

    // Kill dead actors
    for (auto actor : mDestroyedActors)
    {
        for (auto it = mActors.begin();  it!=mActors.end(); ++it)
        {
            if(it->get() == actor)
            {
                const auto mapIter = mActorMap.find(actor->getName());
                if (mapIter != mActorMap.end())
                {
                    mActorMap.erase(mapIter);
                }
                mActors.erase(it);
                break;
            }
        }
    }
    mDestroyedActors.clear();
}

//===========================================================================//
void Map::render(graphics::RenderTarget& target)
{
    // Sort before rendering. This keeps everything drawing in the correct
    // order. Without this an object in front in terms of y position will
    // render differently above or below an object
    sort();

    for (size_t ii = 0; ii < mActors.size(); ++ii)
    {
        mActors[ii].get()->render(target);
    }

    if (mRenderCollision)
    {
        for (size_t ii = 0; ii < mActors.size(); ++ii)
        {
            mActors[ii].get()->getPhysics().render(target);
        }
    }
}

//===========================================================================//
game::Actor& Map::spawnActor(const std::string& filename,
                             const std::string& name,
                             bool initalize)
{
    game::ActorPtr actor(filename, mInput, mTarget, mWorld);
    actor.get()->setName(name);

    if (!initalize)
    {
        mActors.push_back(actor);
    }
    else
    {
        mSpawnedActors.push_back(actor);
        actor.get()->initialize();
    }

    if (!name.empty())
    {
        mActorMap[name] = actor.get();
    }

    if (actor.get()->getType() == Actor::CAMERA)
    {
        mCamera = actor.get();
    }

    return *actor.get();
}

//===========================================================================//
void Map::destroyActor(const Actor* actor)
{
    mDestroyedActors.push_back(actor);
}

//===========================================================================//
void Map::initialize()
{
    sort();
    for (size_t ii = 0; ii < mActors.size(); ++ii)
    {
        mActors[ii].get()->initialize();
    }
}

//===========================================================================//
void Map::sort()
{
    std::stable_sort(mActors.begin(), mActors.end());
}
}

namespace core
{
//===========================================================================//
void read(const std::string& pathname,
          game::Map& map)
{
    const json::JSON tree = core::read<json::JSON>(pathname);

    if (tree.has("actors"))
    {
        for (size_t ii = 0; ii < tree["actors"].loopSize(); ++ii)
        {
            const auto& actorMap = tree["actors"][ii];
            const std::string filename = actorMap["filename"].get();
            const std::string name =
                    actorMap.has("name") ? actorMap["name"].get() : "";
            game::Actor& actor = map.spawnActor(filename, name, false);

            if (actorMap.has("position"))
            {
                math::Vector2F position(
                        core::str::toType<double>(
                                actorMap["position"]["x"].get()),
                        core::str::toType<double>(
                                actorMap["position"]["y"].get()));
                actor.setPosition(position);

                // Update the physics position
                actor.getPhysics().update();
            }

            if (actorMap.has("var"))
            {
                const auto& vars = actorMap["var"];
                for (size_t var = 0; var < vars.loopSize(); ++var)
                {
                    actor.getScript().variable(
                            vars[var]["name"].get())->set(vars[var]["value"].get());
                }
            }
        }
    }
    map.initialize();
}
}
}
