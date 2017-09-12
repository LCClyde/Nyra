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
#ifndef __NYRA_GRAPHICS_TILE_MAP_H__
#define __NYRA_GRAPHICS_TILE_MAP_H__

#include <nyra/graphics/Renderable.h>
#include <nyra/math/Transform.h>
#include <nyra/math/Vector2.h>
#include <nyra/mem/Buffer2D.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class TileMap
 *  \brief Class for rendering tiles.
 *
 *  \tparam The Sprite class to use. This makes this class generic for any
 *          graphics engine.
 */
template <typename SpriteT>
class TileMap : public Renderable<math::Transform2D>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a tilemap
     *
     *  \param spritePathname The pathname for the base sprite map
     *  \param tiles The frame index for each tile
     *  \param tileSize The size of each tile in pixels.
     */
    TileMap(const std::string& spritePathname,
            const mem::Buffer2D<size_t>& tiles,
            const math::Vector2U tileSize) :
        mTiles(tiles),
        mSprites(tiles.getSize()),
        mTileSize(tileSize)
    {
        const math::Vector2F pivot(0.0f, 0.0f);
        const math::Vector2U textureSize(SpriteT(spritePathname).getSize());
        const math::Vector2U tilesInImage(textureSize.x / mTileSize.x,
                                          textureSize.y / mTileSize.y);
        for (size_t row = 0; row < mTiles.getNumRows(); ++row)
        {
            for (size_t col = 0; col < mTiles.getNumCols(); ++col)
            {
                const size_t idRow = mTiles(col, row) / tilesInImage.x;
                const size_t idCol = mTiles(col, row) % tilesInImage.x;
                mSprites(col, row).load(spritePathname);
                mSprites(col, row).setPivot(pivot);
                mSprites(col, row).setFrame(math::Vector2U(
                        mTileSize.x * idCol,
                        mTileSize.y * idRow),
                        mTileSize);
                mSprites(col, row).setPosition(math::Vector2F(
                        mTileSize.x * col,
                        mTileSize.y * row));
                mSprites(col, row).updateTransform(*this);
            }
        }

        setSize(tileSize * tiles.getSize());
        std::cout << getSize() << "\n";
    }

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override
    {
        for (size_t ii = 0; ii < mSprites.getSize().product(); ++ii)
        {
            mSprites(ii).render(target);
        }
    }

    /*
     *  \func getTileSize
     *  \brief Gets the size of individual tiles
     *
     *  \return The tile size
     */
    const math::Vector2U getTileSize() const
    {
        return mTileSize;
    }

private:
    mem::Buffer2D<size_t> mTiles;
    mem::Buffer2D<SpriteT> mSprites;
    const math::Vector2U mTileSize;
};
}
}

#endif
