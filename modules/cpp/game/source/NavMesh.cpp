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
#include <nyra/game/NavMesh.h>

namespace nyra
{
namespace game
{
NavMesh::NavMesh(const TileMapT& map,
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
    mEvent = [](const math::Vector2F& v1,
                const math::Vector2F& v2)->double
    {
        static const double diag = math::Vector2F(1, 1).length();
        const int32_t x = std::abs(static_cast<int32_t>(v1.x) -
                                   static_cast<int32_t>(v2.x));
        const int32_t y = std::abs(static_cast<int32_t>(v1.y) -
                                   static_cast<int32_t>(v2.y));
        const int32_t max = std::max(x, y);
        const int32_t min = std::min(x, y);
        return diag * min + (max - min);
    };
}

void NavMesh::addTile(const TileMapT& map,
                      const std::unordered_set<size_t>& collision,
                      size_t x, size_t y,
                      int32_t dx, int32_t dy)
{
    const int32_t targetX = x + dx;
    const int32_t targetY = y + dy;
    if (targetX >= 0 && targetY >= 0 &&
        static_cast<size_t>(targetX) < map.getNumTiles().x &&
        static_cast<size_t>(targetY) < map.getNumTiles().y)
    {
        if (collision.find(map.getTile(targetX, targetY)) == collision.end())
        {
            const math::Vector2F tile(x, y);
            const math::Vector2F target(targetX, targetY);
            mGraph.addEdge(tile, target);
        }
    }
}
}
}
