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

#include <unordered_set>
#include <nyra/graphics/TileMap.h>
#include <nyra/math/Graph.h>

namespace nyra
{
namespace game
{
/*
 *  \class NavMesh
 *  \brief Creates a navigation mesh that can be used for pathfinding.
 *
 *  \tparam GameT The game type
 */
template <typename GameT>
class NavMesh
{
private:
    typedef graphics::TileMap<typename GameT::Graphics::Sprite> TileMapT;
    typedef typename GameT::Graphics::Vector VectorT;
public:
    /*
     *  \func Constructor
     *  \brief Creates a NavMesh from a tilemap
     *
     *  \param map The tilemap to use as nodes
     *  \param collision The list of tiles that should be considered collision
     */
    NavMesh(const TileMapT& map,
            const std::unordered_set<size_t>& collision)
    {
        const math::Vector2U& size = map.getNumTiles();
        for (size_t y = 0; y < size.y; ++y)
        {
            for (size_t x = 0; x < size.x; ++x)
            {
                if (collision.find(map.getTile(x, y)) == collision.end())
                {
                    addTile(map, collision, x, y, 1, -1);
                    addTile(map, collision, x, y, 1, 0);
                    addTile(map, collision, x, y, 1, 1);
                    addTile(map, collision, x, y, 0, 1);
                }
            }
        }
        mEvent = [](const VectorT& v1, const VectorT& v2)->double
        {
            static const double diag = VectorT(1, 1).length();
            const int32_t x = std::abs(static_cast<int32_t>(v1.x) -
                                       static_cast<int32_t>(v2.x));
            const int32_t y = std::abs(static_cast<int32_t>(v1.y) -
                                       static_cast<int32_t>(v2.y));
            const int32_t max = std::max(x, y);
            const int32_t min = std::min(x, y);
            return diag * min + (max - min);
        };
    }

    /*
     *  \func getPath
     *  \brief Gets a shortest path from the nav mesh
     *
     *  \param start The starting node
     *  \param end The ending node
     *  \return The shortest available path
     */
    math::PathResults<VectorT> getPath(const VectorT& start,
                                       const VectorT& end) const
    {
        return mGraph.getPath(start, end, mEvent);
    }


private:
    void addTile(const TileMapT& map,
                 const std::unordered_set<size_t>& collision,
                 size_t x, size_t y,
                 int32_t dx, int32_t dy)
    {
        const int32_t targetX = x + dx;
        const int32_t targetY = y + dy;
        if (targetX >= 0 && targetY >= 0 &&
            targetX < map.getNumTiles().x &&
            targetY < map.getNumTiles().y)
        {
            if (collision.find(map.getTile(targetX, targetY)) == collision.end())
            {
                const VectorT tile(x, y);
                const VectorT target(targetX, targetY);
                mGraph.addEdge(tile, target);
            }
        }
    }

    math::Graph<VectorT> mGraph;
    typename math::Graph<VectorT>::HeuristicEvent mEvent;
};
}
}

#endif
