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
#include <nyra/win/qt/Application.h>

namespace nyra
{
namespace win
{
namespace qt
{
//===========================================================================//
Application::Application() :
    mArgv(2),
    mArgc(mArgv.size() - 1)
{
    // This const cast may look dangerous, but it will never realistically
    // change. In a "real" application, this would represent the name
    // of the application. The upside with this cast is that it suppresses
    // a warning.
    // WARNING: mArgv should not be changed after this. We could try to make
    //          them const, but QApplication takes in non-const values so
    //          we would need another awkward const_cast if we do that.
    mArgv.push_back(const_cast<char*>("NyraApplication"));
    mArgv.push_back(nullptr);
}

//===========================================================================//
void Application::initializeGlobal()
{
    mApplication.reset(new QApplication(mArgc, &mArgv[0]));
}

//===========================================================================//
void Application::shutdownGlobal()
{
    mApplication.reset(nullptr);
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const Application& app)
{
    os << "Application state: ";
    if (app.get())
    {
        os << "running";
    }
    else
    {
        os << "stopped";
    }
    return os;
}
}
}
}
