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
#include <nyra/game/Input.h>

namespace nyra
{
namespace game
{
/*
 *  \class Map
 *  \brief Represents a grouping of objects that corresponds to a single
 *         map / level. There is only one map loaded at a time.
 */
class Map
{
public:
    /*
     *  \func Constructor
     *  \brief Sets an empty map and assigns it to the global object.
     */
    Map(const game::Input& input,
        const graphics::RenderTarget& target);

    /*
     *  \func update
     *  \brief Updates everything on the map
     *
     *  \param delta The time in seconds since the last update
     */
    void update(double delta);

    /*
     *  \func render
     *  \brief Renders the map to the screen.
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target);

    /*
     *  \func spawnActor
     *  \brief Adds a new actor to the map
     *
     *  \param filename The filename of the Actor json
     *  \param name The name of the actor
     *  \param initialize Should the actor call initialize when loaded?
     *  \return The actor
     */
    game::Actor& spawnActor(const std::string& filename,
                            const std::string& name,
                            bool initalize);
    /*
     *  \func destroyActor
     *  \brief Destroys an existing actor. The actor will actually stick
     *         around until the next frame
     *
     *  \param actor The actor to destroy
     */
    void destroyActor(const Actor* actor);

    /*
     *  \func initialize
     *  \brief Called after the map has been loaded and all actors have
     *         been created.
     */
    void initialize();

    /*
     *  \func getActor
     *  \brief Returns a named actor
     *
     *  \param name The provided name of the actor
     *  \return The actor object
     */
    static Actor& getActor(const std::string& name)
    {
        return *mMap->mActorMap.at(name);
    }

    /*
     *  \func getMap
     *  \brief Gets the global map object
     *
     *  \return The map singleton
     */
    static Map& getMap()
    {
        return *mMap;
    }

private:
    void sort();

    std::vector<ActorPtr> mActors;
    std::unordered_map<std::string, Actor*> mActorMap;
    std::vector<const Actor*> mDestroyedActors;
    std::vector<ActorPtr> mSpawnedActors;
    const game::Input& mInput;
    const graphics::RenderTarget& mTarget;
    physics::box2d::World mWorld;
    bool mRenderCollision;
    const Actor* mCamera;
    static Map* mMap;
};
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
void read(const std::string& pathname,
          game::Map& map);
}
}

#endif
