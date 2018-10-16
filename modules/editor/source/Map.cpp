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
#include <nyra/editor/Map.h>
#include <nyra/core/Path.h>
#include <nyra/game/Sprite.h>

namespace nyra
{
namespace editor
{
//===========================================================================//
Map::Map() :
    mWindow("Nyra Map Editor",
            math::Vector2U(1920, 1080),
            math::Vector2I(30, 30)),
    mTarget(mWindow),
    mInput(mWindow, "empty.json"),
    mMap(mInput, mTarget)
{
    core::read(core::path::join(core::DATA_PATH, "maps/sprite_editor.json"), mMap);
}

//===========================================================================//
bool Map::update()
{
    if (mWindow.isOpen())
    {
        mWindow.update();
        mInput.update();
        mMap.update(0.0);

        mTarget.clear(img::Color(192, 192, 192));
        mMap.render(mTarget);
        mTarget.flush();
    }

    return mWindow.isOpen();
}
}
}
