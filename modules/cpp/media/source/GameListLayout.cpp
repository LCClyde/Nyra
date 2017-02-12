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
#include <nyra/media/GameListLayout.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
std::string layoutToString(nyra::media::GameListLayout::BoxLayout layout)
{
    switch (layout)
    {
    case nyra::media::GameListLayout::HORIZONTAL:
        return "HORIZONTAL";
    case nyra::media::GameListLayout::VERTICAL:
        return "VERTICAL";
    default:
        throw std::runtime_error("Unknown box layout");
    }
}

//===========================================================================//
nyra::media::GameListLayout::BoxLayout stringToLayout(
        const std::string& layout)
{
    if (layout == "HORIZONTAL")
    {
        return nyra::media::GameListLayout::HORIZONTAL;
    }
    if (layout == "VERTICAL")
    {
        return nyra::media::GameListLayout::VERTICAL;
    }
    throw std::runtime_error("Unknown box layout: " + layout);
}
}

//===========================================================================//
namespace nyra
{
namespace media
{
//===========================================================================//
GameListLayout::GameListLayout() :
    boxSize(200.0),
    boxLayout(HORIZONTAL),
    boxPosition(800.0),
    boxSpacing(10.0)
{
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GameListLayout& layout)
{
    os << "Box Size:      " << layout.boxSize << "\n"
       << "Box Layout:    " << layoutToString(layout.boxLayout) << "\n"
       << "Box Position:  " << layout.boxPosition << "\n"
       << "Box Spacing:   " << layout.boxSpacing;
    return os;
}
}

namespace core
{
//===========================================================================//
template <>
void write<media::GameListLayout>(const media::GameListLayout& layout,
                                  const std::string& pathname,
                                  core::ArchiveType type)
{
    json::JSON tree;
    tree["box_size"] = core::str::toString(layout.boxSize);
    tree["box_layout"] = layoutToString(layout.boxLayout);
    tree["box_position"] =
            core::str::toString(layout.boxPosition);
    core::write<json::JSON>(tree, pathname);
}

//===========================================================================//
template <>
void read<media::GameListLayout>(const std::string& pathname,
                                 media::GameListLayout& layout,
                                 core::ArchiveType type)
{
    // The idea behind checking for values before setting them is that we
    // could allow a user to create platform specific layouts that inherit
    // from a base. Only set values would be updated.
    json::JSON tree = core::read<json::JSON>(pathname);

    if (tree.has("box_size"))
    {
        layout.boxSize = core::str::toType<double>(tree["box_size"].get());
    }

    if (tree.has("box_layout"))
    {
        layout.boxLayout = stringToLayout(tree["box_layout"].get());
    }

    if (tree.has("box_position"))
    {
        layout.boxPosition = core::str::toType<double>(
                tree["box_position"].get());
    }


    if (tree.has("box_spacing"))
    {
        layout.boxSpacing = core::str::toType<double>(
                tree["box_spacing"].get());
    }
}
}
}
