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
#include <nyra/cegui/GlobalHandler.h>
#include <CEGUI/System.h>

namespace nyra
{
namespace cegui
{
//===========================================================================//
GlobalHandler::GlobalHandler() :
    mRenderer(nullptr)
{
}

//===========================================================================//
void GlobalHandler::initializeGlobal()
{
    // Bootstrap CEGUI::System with an OpenGLRenderer object that uses the
    // current GL viewport, the DefaultResourceProvider, and the default
    // ImageCodec.
    //
    // NB: Your OpenGL context must already be initialised when you call this; CEGUI
    // will not create the OpenGL context itself.
    mRenderer = &CEGUI::OpenGLRenderer::bootstrapSystem();
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    CEGUI::System::destroy();
    CEGUI::OpenGLRenderer::destroy(
            static_cast<CEGUI::OpenGLRenderer&>(*mRenderer));
    mRenderer = nullptr;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& app)
{
    os << "CEGUI ";
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
