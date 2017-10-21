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
#ifndef __NYRA_GUI_WIDGET_H__
#define __NYRA_GUI_WIDGET_H__

#include <nyra/math/Vector2.h>
#include <nyra/core/Event.h>
#include <string>

namespace nyra
{
namespace gui
{
/*
 *  \class Widget
 *  \brief Base class for all Gui widgets.
 */
class Widget
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    virtual ~Widget();

    /*
     *  \func setSize
     *  \brief Sets the size of the widget in pixels.
     *
     *  \param size The desired size.
     */
    virtual void setSize(const math::Vector2F& size) = 0;

    /*
     *  \func setPosition
     *  \brief Sets the position of the widget in pixels.
     *
     *  \param position The desired position.
     */
    virtual void setPosition(const math::Vector2F& position) = 0;

    /*
     *  \func getPosition
     *  \brief Gets the current position.
     *
     *  \return The value of the position.
     */
    virtual math::Vector2F getPosition() const = 0;

    /*
     *  \func getSize
     *  \brief Gets the current size.
     *
     *  \return The value of the size.
     */
    virtual math::Vector2F getSize() const = 0;

    /*
     *  \func addChild
     *  \brief Adds a new child widget to this widget.
     *
     *  \param child The widget to add.
     */
    virtual void addChild(Widget& child) = 0;

    /*
     *  \func getNative
     *  \brief Gets the underlying native object for the widget.
     *
     *  \return A pointer to the native object.
     */
    virtual void* getNative() =  0;

    /*
     *  \func setText
     *  \brief Sets the text of the widget.
     *
     *  \param text The desired text.
     */
    virtual void setText(const std::string& text)
    {
    }

    /*
     *  \func getText
     *  \brief Gets the current text.
     *
     *  \return The value of the text.
     */
    virtual std::string getText() const
    {
        return std::string();
    }

    /*
     *  \func setVisible
     *  \brief Sets if a widget is rendered
     *
     *  \param value True if the widget should be rendered
     */
    virtual void setVisible(bool value) = 0;

    /*
     *  \func getVisible
     *  \brief Is the widget being rendered?
     *
     *  \return True if the widget is visible
     */
    virtual bool getVisible() const = 0;

    /*
     *  \var activated
     *  \brief Occurs when the widget has some sort of activation.
     */
    core::Event<void()> activated;
};
}
}

#endif
