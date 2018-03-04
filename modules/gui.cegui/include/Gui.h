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
#ifndef __NYRA_GUI_CEGUI_GUI_H__
#define __NYRA_GUI_CEGUI_GUI_H__

#include <nyra/gui/Gui.h>
#include <nyra/gui/cegui/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>
#include <nyra/input/Mouse.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
/*
 *  \class Gui
 *  \brief A base class that holds a CEGUI Gui.
 */
class Gui : public gui::Gui,
        private mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a CEGUI that does not respond to input. This is only
     *         used if you want a static GUI.
     */
    Gui();

    /*
     *  \func Constructor
     *  \brief Creates a GUI that responds to input.
     *
     *  \param mouse The mouse object. The GUI does not take ownership
     *         it must stay in scope for the lifetime of the GUI.
     */
    Gui(const input::Mouse& mouse);

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
    void addChild(gui::Widget& child) override;
    const input::Mouse* const mMouse;
};
}
}
}

#endif
