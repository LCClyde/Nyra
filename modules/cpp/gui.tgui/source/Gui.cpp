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
#include <nyra/gui/tgui/Gui.h>
#include <nyra/win/sfml/Window.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace gui
{
namespace tgui
{
//===========================================================================//
Gui::Gui(win::Window& window) :
    mWindow(dynamic_cast<win::sfml::Window&>(window)),
    mGui(*reinterpret_cast<sf::RenderWindow*>(mWindow.getNative()))
{
    mWindow.addSFMLEvent(core::Event<void(sf::Event&)>(
            std::bind(&Gui::sfmlUpdate, this, std::placeholders::_1)));
}

//===========================================================================//
void Gui::update(double deltaTime)
{
}

//===========================================================================//
void Gui::render()
{
    mGui.draw();
}

//===========================================================================//
void Gui::sfmlUpdate(sf::Event& event)
{
    mGui.handleEvent(event);
}

//===========================================================================//
void Gui::addChild(gui::Widget& child)
{
    std::cout <<  "Added widget\n";
    ::tgui::Widget::Ptr widget =
            *reinterpret_cast<::tgui::Widget::Ptr*>(child.getNative());
    mGui.add(widget);
}
}
}
}
