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
#include <nyra/win/gl/Window.h>

#ifdef NYRA_POSIX
#define GLFW_EXPOSE_NATIVE_X11
#endif
#define GLFW_EXPOSE_NATIVE_GLX

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace nyra
{
namespace win
{
namespace gl
{
//===========================================================================//
Window::Window() :
    mWindow(nullptr)
{
}

//===========================================================================//
Window::~Window()
{
    close();
}

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
    glfwPollEvents();
}

//===========================================================================//
void Window::load(const std::string& name,
                  const math::Vector2U& size,
                  const math::Vector2I& position)
{
    mName = name;
    mWindow = glfwCreateWindow(size.x,
                               size.y,
                               name.c_str(),
                               nullptr,
                               nullptr);
    if (!mWindow)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }
    setPosition(position);

    glfwMakeContextCurrent(mWindow);
}

//===========================================================================//
size_t Window::getID() const
{
#ifdef NYRA_POSIX
    // TODO: Verify this is correct.
    return  reinterpret_cast<size_t>(glfwGetX11Window(mWindow));
#endif
}
}
}
}

