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
#ifndef __NYRA_GAME_TYPES_H__
#define __NYRA_GAME_TYPES_H__

#include <nyra/win/sfml/Window.h>
#include <nyra/graphics/TileMap.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/Camera.h>
#include <nyra/physics/box2d/World.h>
#include <nyra/script/py3/Include.h>
#include <nyra/script/py3/Object.h>

namespace nyra
{
namespace game
{
typedef win::sfml::Window WindowT;

typedef graphics::sfml::RenderTarget RenderTargetT;
typedef graphics::sfml::Sprite SpriteT;
typedef graphics::TileMap<SpriteT> TileMapT;
typedef graphics::sfml::Camera CameraT;

typedef physics::box2d::World WorldT;

typedef script::py3::Include IncludeT;
typedef script::py3::Object ObjectT;

}
}

#endif
