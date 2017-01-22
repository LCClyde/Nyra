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
#ifndef __NYRA_GUI_CEGUI_WIDGET_H__
#define __NYRA_GUI_CEGUI_WIDGET_H__

#include <nyra/gui/Widget.h>
#include <CEGUI/Window.h>
#include <nyra/gui/cegui/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
/*
 *  \class Widget
 *  \brief A base class for CEGUI widgets.
 */
class Widget : public virtual gui::Widget,
        protected mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a base CEGUI widget.
     *
     *  \param type The CEGUI type from the data on disk.
     */
    Widget(const std::string& type);

    /*
     *  \func Destructor
     *  \brief Necessary for inheritance.
     */
    virtual ~Widget();

    /*
     *  \func setSize
     *  \brief Sets the size of the widget in pixels.
     *
     *  \param size The desired size.
     */
    void setSize(const math::Vector2F& size) override;

    /*
     *  \func setPosition
     *  \brief Sets the position of the widget in pixels.
     *
     *  \param position The desired position.
     */
    void setPosition(const math::Vector2F& position) override;

    /*
     *  \func getPosition
     *  \brief Gets the current position.
     *
     *  \return The value of the position.
     */
    math::Vector2F getPosition() const override;

    /*
     *  \func getSize
     *  \brief Gets the current size.
     *
     *  \return The value of the size.
     */
    math::Vector2F getSize() const override;

    /*
     *  \func addChild
     *  \brief Adds a new child widget to this widget.
     *
     *  \param child The widget to add.
     */
    void addChild(gui::Widget& child) override;

    /*
     *  \func getNative
     *  \brief Returns the underlying CEGUI object.
     *
     *  \return The CEGUI Window.
     */
    void* getNative() override
    {
        return &mWidget;
    }

protected:
    CEGUI::Window& mWidget;
};
}
}
}

#endif
