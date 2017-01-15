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
#include <nyra/win/native/PosixGlobalHandler.h>

namespace
{
int GlobalErrorHandler(Display* display, XErrorEvent* event)
{
    char buffer[1024];
    XGetErrorText(display, event->error_code, buffer, 1024);
    throw std::runtime_error(buffer);
}
}

namespace nyra
{
namespace win
{
namespace native
{
//===========================================================================//
PosixGlobalHandler::PosixGlobalHandler() :
    mDisplay(nullptr),
    mScreen(0)
{
}

//===========================================================================//
void PosixGlobalHandler::initializeGlobal()
{
    mDisplay = XOpenDisplay(0);
    mScreen = DefaultScreen(mDisplay);
    XSetErrorHandler(GlobalErrorHandler);
}

//===========================================================================//
void PosixGlobalHandler::shutdownGlobal()
{
    XCloseDisplay(mDisplay);
    mDisplay = nullptr;
    mScreen = 0;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const PosixGlobalHandler& handler)
{
    if (handler.get())
    {
        os << "X11 is running";
    }
    else
    {
        os << "X11 is shutdown";
    }
    return os;
}
}
}
}
