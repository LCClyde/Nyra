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
#include <nyra/win/qt/Window.h>
#include <nyra/win/qt/Application.h>

namespace nyra
{
namespace win
{
namespace qt
{
//===========================================================================//
Window::Window(const std::string& name,
               const math::Vector2U& size,
               const math::Vector2I& position)
{
    load(name, size, position);
}

//===========================================================================//
void Window::update()
{
    if (mWindow.get())
    {
        getGlobalInstance().get()->sendPostedEvents(mWindow.get());
    }
}

//===========================================================================//
void Window::load(const std::string& name,
                  const math::Vector2U& size,
                  const math::Vector2I& position)
{
    mWindow.reset(new QMainWindow());
    mWindow->show();
    setName(name);
    setSize(size);
    setPosition(position);
}

//===========================================================================//
void Window::close()
{
    if (mWindow.get())
    {
        mWindow->close();
        mWindow.reset(nullptr);
    }
}
}
}
}

