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
    Map()
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

        for (size_t ii = 0; ii < mActors.size(); ++ii)
        {
            mActors[ii].get()->updateTransform();
        }
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
     *  \func addActor
     *  \brief Adds an actor to the map
     *
     *  \param actor The actor to add
     */
    void addActor(const ActorPtr<GameT>& actor,
                  const std::string& name = "")
    {
        mActors.push_back(actor);

        if (!name.empty())
        {
            mActorMap[name] = actor.get();
        }
    }

    /*
     *  \func initialize
     *  \brief Called after the map has been loaded and all actors have
     *         been created.
     */
    void initialize()
    {
        for (const auto& actor : mActors)
        {
            actor.get()->initialize();
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

private:
    std::vector<ActorPtr<GameT>> mActors;
    std::unordered_map<std::string, Actor<GameT>*> mActorMap;
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
          const graphics::RenderTarget& target,
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

            game::ActorPtr<GameT> actor(filename, target);
            map.addActor(actor, name);
        }
    }
    map.initialize();
}
}
}

#endif
