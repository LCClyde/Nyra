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
#include <nyra/gui/cegui/Panel.h>
#include <nyra/gui/cegui/Button.h>
#include <nyra/gui/cegui/Label.h>
#include <nyra/gui/cegui/Image.h>
#include <nyra/core/String.h>
#include <nyra/core/Path.h>

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
    Gui(const input::Mouse& mouse) :
        mGUI(mouse),
        mSizeSet(false)
    {
    }

    /*
     *  \func update
     *  \brief Updates the actor object
     *
     *  \param delta The time in seconds since the last update
     */
    void update(float delta)
    {
        mGUI.update(delta);
    }

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override
    {
        mGUI.render();
    }

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
                                         mem::Tree<gui::Widget>& gui)
    {
        gui::cegui::Widget* widget = nullptr;

        if (type == "panel")
        {
            widget = new gui::cegui::Panel(param);
        }
        else if (type == "label")
        {
            widget = new gui::cegui::Label(param);
        }
        else if (type == "button")
        {
            widget = new gui::cegui::Button(param);
        }
        else if (type == "image")
        {
            widget = new gui::cegui::Image(
                    core::path::join(core::DATA_PATH, "textures/" + param));
        }
        else
        {
            throw std::runtime_error("Unknown widget type: " + type);
        }

        gui[name] = widget;
        return widget;
    }

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
    void finalize()
    {
        math::Vector2F size;
        math::Vector2F position(std::numeric_limits<float>::max(),
                                std::numeric_limits<float>::max());

        const auto keys = mGUI.keys();

        for (size_t ii = 0; ii < keys.size(); ++ii)
        {
            const math::Vector2F wPos = mGUI[keys[ii]].get().getPosition();
            position.x = std::min(position.x, wPos.x);
            position.y = std::min(position.y, wPos.y);
        }

        for (size_t ii = 0; ii < keys.size(); ++ii)
        {
            const math::Vector2F wSize = mGUI[keys[ii]].get().getSize();
            const math::Vector2F wPos = mGUI[keys[ii]].get().getPosition();
            size.x = std::max(wSize.x, position.x - (wPos.x + size.x));
            size.y = std::max(wSize.y, position.y - (wPos.y + size.y));
        }

        setSize(size);
        setPosition(position);
    }

    gui::Widget& getWidget(const std::string& name)
    {
        const std::vector<std::string> parts = core::str::split(name, ":");

        mem::Tree<gui::Widget>* current = &mGUI;
        for (const std::string& p : parts)
        {
            current = &current->operator [](p);
        }

        return current->get();
    }

private:
    gui::cegui::Gui mGUI;
    bool mSizeSet;
};
}
}

#endif
