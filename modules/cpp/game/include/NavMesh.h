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
#ifndef __NYRA_GAME_NAV_MESH_H__
#define __NYRA_GAME_NAV_MESH_H__

#include <nyra/graphics/TileMap.h>
#include <nyra/math/Graph.h>

namespace nyra
{
namespace game
{
template <typename GameT>
class NavMesh : public GameT::Graphics::Renderable
{
private:
    typedef graphics::TileMap<typename GameT::Graphics::Sprite> TileMapT;
public:
    NavMesh(const TileMapT& map,
            const std::vector<size_t>& collision)
    {
        const math::Vector2U& size = map.getNumTiles();
        for (size_t y = 0; y < size.y; ++y)
        {
            for (size_t x = 0; x < size.x; ++x)
            {
                addTile(map, collision, x, y, 1, -1);
                addTile(map, collision, x, y, 1, 0);
                addTile(map, collision, x, y, 1, 1);
                addTile(map, collision, x, y, 0, 1);
            }
        }
    }

    void render(graphics::RenderTarget& target) override
    {
    }


private:
    void addTile(const TileMapT& map,
                 const std::vector<size_t>& collision,
                 size_t x, size_t y,
                 int32_t dx, int32_t dy)
    {
        if (dx > 0 && dy > 0 &&
            dx < map.getNumTiles().x &&
            dy < map.getNumTiles().y)
        {
            if (std::find(collision.begin(),
                          collision.end(),
                          map.getTile(dx, dy)) == collision.end())
            {
                mMesh.addEdge(typename GameT::Graphics::Vector(x, y),
                              typename GameT::Graphics::Vector(x + dx, y + dy));
            }
        }
    }

    math::Graph<typename GameT::Graphics::Vector> mMesh;
};
}
}

#endif
