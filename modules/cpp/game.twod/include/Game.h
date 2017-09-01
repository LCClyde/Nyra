/*
 * Copyright (c) 2016 Clyde Stanfield
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
#ifndef __NYRA_GAME_TWOD_GAME_H__
#define __NYRA_GAME_TWOD_GAME_H__

#include <nyra/win/sfml/Window.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/input/sfml/Mouse.h>
#include <nyra/input/sfml/Keyboard.h>
#include <nyra/game/Game.h>
#include <nyra/game/Types.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/script/py3/Object.h>
#include <nyra/script/py3/Variable.h>
#include <nyra/script/py3/Include.h>

namespace nyra
{
namespace game
{
namespace twod
{
typedef game::WindowType<win::sfml::Window> WindowType;
typedef game::GraphicsType<graphics::sfml::RenderTarget,
                           math::Transform2D,
                           graphics::sfml::Sprite>
                           GraphicsType;
typedef game::InputType<input::sfml::Mouse,
                        input::sfml::Keyboard> InputType;
typedef game::ScriptType<script::py3::Include,
                         script::py3::Variable,
                         script::py3::Object> ScriptType;
typedef game::GameType<WindowType,
                       GraphicsType,
                       InputType,
                       ScriptType> GameType;
typedef game::Game<GameType> Game;
}
}
}

#endif
