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
#ifndef __NYRA_GAME_ACTOR_H__
#define __NYRA_GAME_ACTOR_H__

#include <memory>
#include <vector>
#include <nyra/json/JSON.h>
#include <nyra/core/String.h>
#include <nyra/mem/Buffer2D.h>
#include <nyra/graphics/TileMap.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace game
{
/*
 *  \class Actor
 *  \brief Generic class for anything that interacts with the game
 *
 *  \tparam GameT The game type
 */
template <typename GameT>
class Actor : public GameT::Graphics::Renderable
{
private:
    typedef typename GameT::Graphics::RenderTarget RenderTargetT;
    typedef typename GameT::Graphics::Renderable RenderableT;
    typedef std::vector<std::unique_ptr<RenderableT>> RenderList;
    typedef typename GameT::Script::Object ObjectT;

public:
    /*
     *  \func addRenderable
     *  \brief Adds a new renderable to the actor
     *
     *  \param renderable The object to add
     */
    void addRenderable(RenderableT* renderable)
    {
        mRenderables.push_back(
                std::unique_ptr<RenderableT>(renderable));
    }

    /*
     *  \func render
     *  \brief Renders the actor to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override
    {
        for (size_t ii = 0; ii < mRenderables.size(); ++ii)
        {
            mRenderables[ii]->render(target);
        }
    }

    /*
     *  \func setScript
     *  \brief Sets the script that is used to control the actor
     *
     *  \param script The script object
     */
    void setScript(ObjectT* script)
    {
        mScript.reset(script);
        mScript->variable("_nyra_ptr")->set(reinterpret_cast<size_t>(this));
        (*mScript->function("update"))();
    }

private:
    RenderList mRenderables;
    std::unique_ptr<ObjectT> mScript;
};
}

namespace core
{
/*
 *  \func read
 *  \brief Reads an actor from file.
 *
 *  \param pathname The location to save to.
 *  \param actor The actor to load
 */
template <typename GameT>
void read(const std::string& pathname,
          game::Actor<GameT>& actor)
{
    const json::JSON tree = core::read<json::JSON>(pathname);

    if (tree.has("tile_map"))
    {
        for (size_t ii = 0; ii < tree["tile_map"].loopSize(); ++ii)
        {
            const auto& tileMap = tree["tile_map"][ii];
            const std::string filename = tileMap["filename"].get();

            math::Vector2U tileSize(
                    core::str::toType<size_t>(tileMap["tile_size"]["width"].get()),
                    core::str::toType<size_t>(tileMap["tile_size"]["height"].get()));
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

            graphics::TileMap<typename GameT::Graphics::Sprite>* mapPtr =
                    new graphics::TileMap<typename GameT::Graphics::Sprite>(
                            filename,
                            tiles,
                            tileSize);
            actor.addRenderable(mapPtr);
        }
    }

    if (tree.has("script"))
    {
        const auto& scriptXML = tree["script"];
        const std::string filename = scriptXML["filename"].get();
        const std::string className = scriptXML["class"].get();
        typename GameT::Script::Include include(filename);
        typename GameT::Script::Object* script =
                new typename GameT::Script::Object(include, className);
        actor.setScript(script);
    }
}
}
}

#endif
