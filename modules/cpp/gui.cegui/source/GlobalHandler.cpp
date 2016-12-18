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
#include <nyra/gui/cegui/GlobalHandler.h>
#include <nyra/core/Path.h>
#include <CEGUI/System.h>
#include <CEGUI/DefaultResourceProvider.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/Font.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/Scheme.h>
#include <CEGUI/falagard/WidgetLookManager.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/ScriptModule.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
//===========================================================================//
GlobalHandler::GlobalHandler() :
    mRenderer(nullptr),
    mWindowManager(nullptr),
    mRoot(nullptr),
    mScheme("WindowsLook")
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
    mRenderer->enableExtraStateSettings(true);
    mSystem = CEGUI::System::getSingletonPtr();

    // TODO: Find a generic way to specify these.
    // initialize the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* resourceProvider =
            static_cast<CEGUI::DefaultResourceProvider*>(
                    mSystem->getResourceProvider());
    const std::string baseDir = core::DATA_PATH + "/../share/cegui-0/";
    resourceProvider->setResourceGroupDirectory("schemes",
                                                baseDir + "schemes/");
    resourceProvider->setResourceGroupDirectory("imagesets",
                                                baseDir + "imagesets/");
    resourceProvider->setResourceGroupDirectory("fonts",
                                                baseDir + "fonts/");
    resourceProvider->setResourceGroupDirectory("layouts",
                                                baseDir + "layouts/");
    resourceProvider->setResourceGroupDirectory("looknfeels",
                                                baseDir + "looknfeel/");
    resourceProvider->setResourceGroupDirectory("lua_scripts",
                                                baseDir + "lua_scripts/");

    // set the default resource groups to be used
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    // create (load) the TaharezLook scheme file
    // (this auto-loads the TaharezLook looknfeel and imageset files)
    CEGUI::SchemeManager::getSingleton().createFromFile(mScheme + ".scheme");

    // create (load) a font.
    // The first font loaded automatically becomes the default font, but note
    // that the scheme might have already loaded a font, so there may already
    // be a default set - if we want the "DejaVuSans-10" font to definitely
    // be the default, we should set the default explicitly afterwards.
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

    CEGUI::GUIContext& context = mSystem->getDefaultGUIContext();
    context.setDefaultFont("DejaVuSans-10");
    context.getMouseCursor().setDefaultImage(mScheme + "/MouseArrow");
    context.setDefaultTooltipType(mScheme + "/Tooltip");

    mWindowManager = CEGUI::WindowManager::getSingletonPtr();
    mRoot = mWindowManager->createWindow("DefaultWindow", "root");
    context.setRootWindow(mRoot);
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    CEGUI::System::destroy();
    CEGUI::OpenGLRenderer::destroy(
            static_cast<CEGUI::OpenGLRenderer&>(*mRenderer));
    mRenderer = nullptr;
    mWindowManager = nullptr;
    mRoot = nullptr;
    mSystem = nullptr;
}

//===========================================================================//
CEGUI::Window& GlobalHandler::createWidget(const std::string& type) const
{
    return *mWindowManager->createWindow(mScheme + "/" + type);
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& app)
{
    os << "CEGUI ";
    if (app.getRenderer())
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
