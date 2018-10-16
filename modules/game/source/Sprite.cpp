/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/game/Sprite.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace game
{
//===========================================================================//
Sprite::Sprite(const std::string& filename,
               const math::Vector2F& pivot,
               const math::Vector2U& frames)
{
    initialize(filename, pivot, frames);
}

//===========================================================================//
void Sprite::initialize(const std::string& filename,
                        const math::Vector2F& pivot,
                        const math::Vector2U& frames)
{
    mFrames = frames;

    if (filename.empty())
    {
        return;
    }

    if (filename != mFilename)
    {
        mFilename = filename;
        mSprite = SpriteT(core::path::join(
                core::DATA_PATH, "textures/" + mFilename));
    }

    mSprite.setPivot(pivot);
}

//===========================================================================//
void Sprite::initialize(const json::JSON& tree)
{
    const std::string filename = tree["filename"].get();

    math::Vector2F pivot(0.5, 0.5);
    if (tree.has("pivot"))
    {
        pivot.x = core::str::toType<float>(tree["pivot"]["x"].get());
        pivot.y = core::str::toType<float>(tree["pivot"]["y"].get());
    }

    math::Vector2U frames(1, 1);
    if (tree.has("frames"))
    {
        frames.x = core::str::toType<float>(tree["frames"]["x"].get());
        frames.y = core::str::toType<float>(tree["frames"]["y"].get());
    }

    initialize(filename, pivot, frames);
}

//===========================================================================//
void Sprite::render(graphics::RenderTarget& target)
{
    if (!mFilename.empty())
    {
        mSprite.render(target);
    }
}

//===========================================================================//
void Sprite::updateTransform(const math::Transform2D& parent)
{
    mSprite.updateTransform(parent);
}
}

namespace core
{
//===========================================================================//
template <>
void write<game::Sprite>(const game::Sprite& data,
                         const std::string& pathname,
                         core::ArchiveType type)
{
    json::JSON tree;
    tree["filename"] = data.getFilename();
    tree["pivot"]["x"] = core::str::toString(data.getPivot().x);
    tree["pivot"]["y"] = core::str::toString(data.getPivot().y);
    tree["frames"]["x"] = core::str::toString(data.getFrames().x);
    tree["frames"]["y"] = core::str::toString(data.getFrames().y);
    write(tree, pathname, type);
}

//===========================================================================//
template <>
void read<game::Sprite>(const std::string& pathname,
                        game::Sprite& data,
                        core::ArchiveType type)
{
    const json::JSON tree(pathname);
    data.initialize(tree);
}
}
}
