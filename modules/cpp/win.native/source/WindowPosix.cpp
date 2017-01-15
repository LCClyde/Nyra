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
#include <iostream>
#include <nyra/win/native/WindowPosix.h>

namespace nyra
{
namespace win
{
namespace native
{
//===========================================================================//
WindowPosix::WindowPosix() :
    mWindow(0)
{
}

//===========================================================================//
WindowPosix::WindowPosix(const std::string& name,
                         const math::Vector2U& size,
                         const math::Vector2I& position) :
    mWindow(0)
{
    load(name, size, position);
}

//===========================================================================//
void WindowPosix::load(const std::string& name,
                       const math::Vector2U& size,
                       const math::Vector2I& position)
{
    Display* display = getGlobalInstance().get();
    const int screen = getGlobalInstance().getScreen();
    mWindow = XCreateSimpleWindow(display,
                                  RootWindow(display, screen),
                                  position.x(),
                                  position.y(),
                                  size.x(),
                                  size.y(),
                                  1,
                                  BlackPixel(display, screen),
                                  WhitePixel(display, screen));
    XSelectInput(display, mWindow, ExposureMask | KeyPressMask);
    XMapWindow(display, mWindow);

    mDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, mWindow, &mDeleteMessage, 1);

    setName(name);
}

//===========================================================================//
void WindowPosix::update()
{
    if (!mWindow)
    {
        return;
    }

    Display* display = getGlobalInstance().get();
    XEvent event;
    while (XPending(display))
    {
        XNextEvent(display, &event);

        if(event.type == ClientMessage)
        {
            if (static_cast<Atom>(event.xclient.data.l[0]) == mDeleteMessage)
            {
                XDestroyWindow(display, event.xclient.window);
                break;
            }
        }
    }
}

//===========================================================================//
bool WindowPosix::isOpen() const
{
    try
    {
        char* name = nullptr;
        if (XFetchName(getGlobalInstance().get(), mWindow, &name) > 0)
        {
            XFree(name);
            return true;
        }

        return false;
    }
    catch (...)
    {
        return false;
    }
}

//===========================================================================//
void WindowPosix::close()
{
    if (mWindow)
    {
        XDestroyWindow(getGlobalInstance().get(), mWindow);
        mWindow = 0;
    }
}

//===========================================================================//
void WindowPosix::setName(const std::string& name)
{
    XStoreName(getGlobalInstance().get(), mWindow, name.c_str());
}

//===========================================================================//
void WindowPosix::setSize(const math::Vector2U& size)
{
    XWindowChanges changes;
    changes.width = size.x();
    changes.height = size.y();

    XConfigureWindow(getGlobalInstance().get(),
                     mWindow,
                     (CWWidth | CWHeight),
                     &changes);
}

//===========================================================================//
void WindowPosix::setPosition(const math::Vector2I& position)
{
    XWindowChanges changes;
    changes.x = position.x();
    changes.y = position.y();

    XConfigureWindow(getGlobalInstance().get(),
                     mWindow,
                     (CWX | CWY),
                     &changes);
}

//===========================================================================//
std::string WindowPosix::getName() const
{
    char* name = nullptr;
    if (XFetchName(getGlobalInstance().get(), mWindow, &name) > 0)
    {
        const std::string strName(name);
        XFree(name);
        return strName;
    }

    return "";
}

//===========================================================================//
math::Vector2U WindowPosix::getSize() const
{
    Display* display = getGlobalInstance().get();
    XWindowAttributes attributes;

    if (XGetWindowAttributes(display, mWindow, &attributes) > 0)
    {
        return math::Vector2U(attributes.width,
                              attributes.height);
    }

    return math::Vector2U();
}

//===========================================================================//
math::Vector2I WindowPosix::getPosition() const
{
    Display* display = getGlobalInstance().get();
    const int screen = getGlobalInstance().getScreen();
    XWindowAttributes attributes;

    int x;
    int y;
    ::Window child;

    XTranslateCoordinates(display,
                          mWindow,
                          RootWindow(display, screen),
                          0, 0, &x, &y,
                          &child);

    if (XGetWindowAttributes(display, mWindow, &attributes) > 0)
    {
        return math::Vector2I(x - attributes.x,
                              y - attributes.y);
    }

    return math::Vector2I();
}
}
}
}
