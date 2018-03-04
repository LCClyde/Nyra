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
#ifndef __NYRA_GAME_GUI_H__
#define __NYRA_GAME_GUI_H__

#include <nyra/gui/cegui/Gui.h>
#include <nyra/gui/cegui/Widget.h>
#include <nyra/graphics/Renderable.h>

namespace nyra
{
namespace game
{
/*
 *  \class Gui
 *  \brief Creates a game specific GUI.
 */
class Gui : public graphics::Renderable2D
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a GUI
     *
     *  \param mouse The mouse object
     */
    Gui(const input::Mouse& mouse);

    /*
     *  \func update
     *  \brief Updates the actor object
     *
     *  \param delta The time in seconds since the last update
     */
    void update(float delta);

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override;

    /*
     *  \func addWidget
     *  \brief Adds a new widget
     *
     *  \param type The widget type
     *  \param param The constructor parameter (often text)
     *  \param name The name of the widget in the tree
     *  \param gui The tree to add the widget to
     */
    static gui::cegui::Widget* addWidget(const std::string& type,
                                         const std::string& param,
                                         const std::string& name,
                                         mem::Tree<gui::Widget>& gui);

    /*
     *  \func get
     *  \brief Gets the underlying tree
     *
     *  \return The GUI tree
     */
    mem::Tree<gui::Widget>& get()
    {
        return mGUI;
    }

    /*
     *  \func finalize
     *  \brief Sets up the size and position. Call after initialization.
     */
    void finalize();

    gui::Widget& getWidget(const std::string& name);

private:
    gui::cegui::Gui mGUI;
    bool mSizeSet;
};
}
}

#endif
