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
#ifndef __NYRA_GUI_TGUI_GUI_H__
#define __NYRA_GUI_TGUI_GUI_H__

#include <nyra/gui/Gui.h>
#include <nyra/win/sfml/Window.h>
#include <TGUI/TGUI.hpp>

namespace nyra
{
namespace gui
{
namespace tgui
{
/*
 *  \class Gui
 *  \brief A base class that holds a Qt Gui.
 */
class Gui : public gui::Gui
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a blank Gui.
     *
     *  \param window The window object associated with this Gui.
     */
    Gui(win::Window& window);

    /*
     *  \func update
     *  \brief Updates all the elements in the Gui.
     *
     *  \param deltaTime The time in seconds that has passed since the
     *         last update.
     */
    void update(double deltaTime) override;

    /*
     *  \func render
     *  \brief Renders all the widgets in the Gui.
     */
    void render() override;

private:
    void sfmlUpdate(sf::Event& event);

    void addChild(gui::Widget& child) override;

    win::sfml::Window& mWindow;
    ::tgui::Theme mTheme;
    ::tgui::Gui mGui;
};
}
}
}

#endif
