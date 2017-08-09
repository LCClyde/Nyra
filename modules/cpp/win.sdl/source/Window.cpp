/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <nyra/win/sdl/Window.h>

namespace nyra
{
namespace win
{
namespace sdl
{
//===========================================================================//
Window::Window() :
    mWindow(nullptr)
{
}

//===========================================================================//
Window::Window(const std::string& name,
               const math::Vector2U& size,
               const math::Vector2I& position) :
    mWindow(nullptr)
{
    load(name, size, position);
}

//===========================================================================//
Window::~Window()
{
    close();
}

//===========================================================================//
void Window::load(const std::string& name,
                  const math::Vector2U& size,
                  const math::Vector2I& position)
{
    mWindow = SDL_CreateWindow(name.c_str(),
                               position.x,
                               position.y,
                               size.x,
                               size.y,
                               SDL_WINDOW_SHOWN);
}

//===========================================================================//
void Window::close()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

//===========================================================================//
void Window::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            close();
        }
    }
}
}
}
}
