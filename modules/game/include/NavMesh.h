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
#include <nyra/math/Graph.h>
#include <nyra/game/Types.h>

namespace nyra
{
namespace game
{
/*
 *  \class NavMesh
 *  \brief Creates a navigation mesh that can be used for pathfinding.
 */
class NavMesh
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a NavMesh from a tilemap
     *
     *  \param map The tilemap to use as nodes
     *  \param collision The list of tiles that should be considered collision
     */
    NavMesh(const TileMapT& map,
            const std::unordered_set<size_t>& collision);

    /*
     *  \func getPath
     *  \brief Gets a shortest path from the nav mesh
     *
     *  \param start The starting node
     *  \param end The ending node
     *  \return The shortest available path
     */
    math::PathResults<math::Vector2F> getPath(
            const math::Vector2F& start,
            const math::Vector2F& end) const
    {
        return mGraph.getPath(start, end, mEvent);
    }


private:
    void addTile(const TileMapT& map,
                 const std::unordered_set<size_t>& collision,
                 size_t x, size_t y,
                 int32_t dx, int32_t dy);

    math::Graph<math::Vector2F> mGraph;
    typename math::Graph<math::Vector2F>::HeuristicEvent mEvent;
};
}
}

#endif
