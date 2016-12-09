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
#include <nyra/win/ogre/Window.h>
#include <nyra/pattern/GlobalUpdate.h>
#include <OgreWindowEventUtilities.h>

namespace nyra
{
namespace win
{
namespace ogre
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
Window::Window(Window&& other) :
    mWindow(other.mWindow),
    mName(other.mName)
{
    other.mWindow = nullptr;
}

//===========================================================================//
Window::~Window()
{
    if (isOpen())
    {
        close();
    }
}

//===========================================================================//
void Window::load(const std::string& name,
                  const math::Vector2U& size,
                  const math::Vector2I& position)
{
    Ogre::NameValuePairList misc;
    misc["title"] = name.c_str();
    misc["left"] = std::to_string(position.x()).c_str();
    misc["top"] = std::to_string(position.y()).c_str();
    mName = name;

    // This ensures that every window has a unique ID outside of its title.
    static size_t winId = 0;
    ++winId;

    mWindow = getGlobalInstance().getRoot()->createRenderWindow(
            ("Window: " + std::to_string(winId)).c_str(),
            size.x(),
            size.y(),
            false,
            &misc);
}

//===========================================================================//
void Window::update()
{
    static pattern::GlobalUpdate updater;
    if (updater.tryUpdate(this))
    {
        Ogre::WindowEventUtilities::messagePump();
    }
}
}
}
}
