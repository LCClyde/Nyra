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
#ifndef __NYRA_MEDIA_GAME_LIST_LAYOUT_H__
#define __NYRA_MEDIA_GAME_LIST_LAYOUT_H__

#include <nyra/math/Vector2.h>

namespace nyra
{
namespace media
{
/*
 *  \class GameListLayout
 *  \brief Holds data about the screen layout when displaying available roms.
 */
struct GameListLayout
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a default layout.
     */
    GameListLayout();

    /*
     *  \enum BoxLayout
     *  \brief How the box art should be displayed.
     */
    enum BoxLayout
    {
        HORIZONTAL,
        VERTICAL
    };

    /*
     *  \var boxSize
     *  \brief The size of the box along its normal axis in pixels.
     */
    double boxSize;

    /*
     *  \var boxLayout
     *  \brief The layout to use for the box art.
     */
    BoxLayout boxLayout;

    /*
     *  \var boxPosition
     *  \brief The position of the box list in normalized pixels along its axis.
     */
    double boxPosition;

    /*
     *  \var boxSpacing
     *  \brief The spacing between each box in normalized pixels.
     */
    double boxSpacing;

    /*
     *  \var videoPosition
     *  \brief The video position in pixels on the DEFAULT_SIZE
     */
    math::Vector2F videoPosition;

    /*
     *  \var videoScale
     *  \brief The video scale.
     */
    double videoScale;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const GameListLayout& layout);
};
}

namespace core
{
/*
 *  \func write
 *  \brief Writes a layout to file.
 *
 *  \param layout The layout to save
 *  \param pathname The location to save to.
 *  \param type This will only write json, even if you select something
 *         else
 */
template <>
void write<media::GameListLayout>(const media::GameListLayout& layout,
                                  const std::string& pathname,
                                  core::ArchiveType type);

/*
 *  \func read
 *  \brief Reads a layout to file.
 *
 *  \param pathname The location to save to.
 *  \param layout The layout to load
 *  \param type This will only read json, even if you select something
 *         else
 */
template <>
void read<media::GameListLayout>(const std::string& pathname,
                                 media::GameListLayout& layout,
                                 core::ArchiveType type);
}
}

#endif
