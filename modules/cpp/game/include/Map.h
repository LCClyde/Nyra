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
#ifndef __NYRA_GAME_MAP_H__
#define __NYRA_GAME_MAP_H__

#include <iostream>
#include <nyra/game/ActorPtr.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace game
{
/*
 *  \class Map
 *  \brief Represents a grouping of objects that corresponds to a single
 *         map / level. There is only one map loaded at a time.
 *
 *  \tparam GameT The game type
 */
template <typename GameT>
class Map
{
public:
    /*
     *  \func Constructor
     *  \brief Sets an empty map and assigns it to the global object.
     */
    Map(const game::Input<GameT>& input,
        const graphics::RenderTarget& target) :
        mInput(input),
        mTarget(target),
        // TODO: This should be a part of config params
        mWorld(64.0, 0.0, 60.0)
    {
        mMap = this;
    }

    /*
     *  \func update
     *  \brief Updates everything on the map
     *
     *  \param delta The time in seconds since the last update
     */
    void update(double delta)
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
            sort();
        }

        if (mWorld.update(delta))
        {
            for (size_t ii = 0; ii < mActors.size(); ++ii)
            {
                mActors[ii].get()->updatePhysics();
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

    /*
     *  \func render
     *  \brief Renders the map to the screen.
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target)
    {

        for (size_t ii = 0; ii < mActors.size(); ++ii)
        {
            mActors[ii].get()->render(target);
        }
    }

    /*
     *  \func spawnActor
     *  \brief Adds a new actor to the map
     *
     *  \param filename The filename of the Actor json
     *  \param name The name of the actor
     *  \param initialize Should the actor call initialize when loaded?
     *  \return The actor
     */
    game::Actor<GameT>& spawnActor(const std::string& filename,
                                   const std::string& name,
                                   bool initalize)
    {
        game::ActorPtr<GameT> actor(filename, mInput, mTarget, mWorld);
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
        return *actor.get();
    }

    /*
     *  \func destroyActor
     *  \brief Destroys an existing actor. The actor will actually stick
     *         around until the next frame
     *
     *  \param actor The actor to destroy
     */
    void destroyActor(const Actor<GameT>* actor)
    {
        mDestroyedActors.push_back(actor);
    }

    /*
     *  \func initialize
     *  \brief Called after the map has been loaded and all actors have
     *         been created.
     */
    void initialize()
    {
        sort();
        for (size_t ii = 0; ii < mActors.size(); ++ii)
        {
            mActors[ii].get()->initialize();
        }
    }

    /*
     *  \func getActor
     *  \brief Returns a named actor
     *
     *  \param name The provided name of the actor
     *  \return The actor object
     */
    static Actor<GameT>& getActor(const std::string& name)
    {
        return *mMap->mActorMap.at(name);
    }

    /*
     *  \func getMap
     *  \brief Gets the global map object
     *
     *  \return The map singleton
     */
    static Map<GameT>& getMap()
    {
        return *mMap;
    }

private:
    void sort()
    {
        std::sort(mActors.begin(), mActors.end());
    }

    std::vector<ActorPtr<GameT>> mActors;
    std::unordered_map<std::string, Actor<GameT>*> mActorMap;
    std::vector<const Actor<GameT>*> mDestroyedActors;
    std::vector<ActorPtr<GameT>> mSpawnedActors;
    const game::Input<GameT>& mInput;
    const graphics::RenderTarget& mTarget;
    typename GameT::Physics::World mWorld;
    static Map<GameT>* mMap;
};

template <typename GameT>
Map<GameT>* Map<GameT>::mMap = nullptr;
}

namespace core
{
/*
 *  \func read
 *  \brief Reads an map from file.
 *
 *  \param pathname The location to save to.
 *  \param actor The map to load
 */
template <typename GameT>
void read(const std::string& pathname,
          game::Map<GameT>& map)
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
            map.spawnActor(filename, name, false);
        }
    }
    map.initialize();
}
}
}

#endif
