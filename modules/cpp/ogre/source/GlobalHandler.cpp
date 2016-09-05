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
#include <nyra/ogre/GlobalHandler.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace ogre
{
//===========================================================================//
void GlobalHandler::initializeGlobal()
{
    Ogre::LogManager* logMgr = OGRE_NEW Ogre::LogManager;
    logMgr->createLog("DefaultLog", true, false, false);
    mRoot.reset(new Ogre::Root(
        core::path::join(core::INSTALL_PATH, "share/OGRE/plugins.cfg"),
        core::path::join(core::INSTALL_PATH, "share/OGRE/resources.cfg")));

    Ogre::RenderSystemList::const_iterator renderers =
            mRoot->getAvailableRenderers().begin();

    while(renderers != mRoot->getAvailableRenderers().end())
    {
        Ogre::String rName = (*renderers)->getName();

        if (rName == "OpenGL Rendering Subsystem")
        {
            break;
        }

        renderers++;
    }

    Ogre::RenderSystem* renderSystem = *renderers;
    renderSystem->setConfigOption("Full Screen","No");
    renderSystem->setConfigOption("Video Mode","320 x 240 @ 32-bit colour");
    renderSystem->setConfigOption("FSAA","8");
    renderSystem->setConfigOption("Fixed Pipeline Enabled","Yes");
    renderSystem->setConfigOption("RTT Preferred Mode","FBO");
    renderSystem->setConfigOption("VSync","No");
    renderSystem->setConfigOption("sRGB Gamma Conversion","No");

    mRoot->setRenderSystem(renderSystem);
    mRoot->initialise(false);

    // Add a hidden window to ensure that the OpenGL object is always
    // valid
    Ogre::NameValuePairList misc;
    misc["hidden"] = "true";
    mRoot->createRenderWindow("Proxy Window", 1, 1, false, &misc);
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    mRoot.reset(nullptr);
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& app)
{
    os << "Ogre Root: ";
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
