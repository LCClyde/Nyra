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
#ifndef __NYRA_MEDIA_BOX_ART_LIST_H__
#define __NYRA_MEDIA_BOX_ART_LIST_H__

#include <vector>
#include <nyra/math/Vector2.h>
#include <nyra/media/Game.h>
#include <nyra/media/GameListLayout.h>
#include <nyra/graphics/RenderTarget.h>

namespace nyra
{
namespace media
{
/*
 *  \class BoxArtList
 *  \brief Handles positioning the box art based on the user defined
 *         settings.
 */
class BoxArtList
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the box art list.
     *
     *  \param layout The layout to represent this list. This is held onto
     *         by reference.
     *  \param games The list of games to display. This is held onto by
     *         reference.
     */
    BoxArtList(const GameListLayout& layout,
               std::vector<Game>& games);

    /*
     *  \func resetLayout
     *  \brief Resets the layout with a new window size.
     *
     *  \param size The window size.
     */
    void resetLayout(const math::Vector2U& size);

    /*
     *  \func updateIndex
     *  \brief Updates the list position based on a user selected index
     *         into the list.
     *
     *  \param index The selected game by index.
     */
    void updateIndex(size_t index);

    /*
     *  \func render
     *  \brief Renders the games to screen.
     *
     *  \param target The target to render to.
     */
    void render(graphics::RenderTarget& target);

private:
    void updateIndexImpl(size_t index, double center, double centerSpriteSize);

    void updatePosition(size_t ii,
                        double screenScale,
                        double direction,
                        double& position);

    void updatePositionHorizontal(size_t ii,
                                  double screenScale,
                                  double direction,
                                  double& position);

    void updatePositionVertical(size_t ii,
                                double screenScale,
                                double direction,
                                double& position);

    double getScreenScale() const;

    const math::Transform2D mParent;
    const GameListLayout& mLayout;
    std::vector<Game>& mGames;
    math::Vector2U mSize;
    size_t mMinIndex;
    size_t mMaxIndex;
};
}
}

#endif
