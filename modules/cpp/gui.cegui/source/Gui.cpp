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
#include <nyra/gui/cegui/Gui.h>
#include <nyra/gui/cegui/Widget.h>
#include <nyra/mem/GlobalUpdate.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <iostream>

namespace nyra
{
namespace gui
{
namespace cegui
{
//===========================================================================//
Gui::Gui()
{
}

//===========================================================================//
void Gui::update(double deltaTime)
{
}

//===========================================================================//
void Gui::render()
{
    static mem::GlobalUpdate updater;
    if (updater.tryUpdate(this))
    {
        getGlobalInstance().getSystem()->renderAllGUIContexts();
    }
}

//===========================================================================//
void Gui::addChild(gui::Widget& child)
{
    getGlobalInstance().getRoot()->addChild(
            reinterpret_cast<CEGUI::Window*>(child.getNative()));
}
}
}
}
