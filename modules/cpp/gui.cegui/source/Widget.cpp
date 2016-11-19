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
#include <nyra/gui/cegui/Widget.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
//===========================================================================//
Widget::Widget(const std::string& type) :
    mWidget(getGlobalInstance().createWidget(type))
{
}

//===========================================================================//
Widget::~Widget()
{
}

//===========================================================================//
void Widget::setSize(const math::Vector2F& size)
{
    mWidget.setSize(CEGUI::USize(
            CEGUI::UDim(0.0f, size.x()),
            CEGUI::UDim(0.0f, size.y())));
}

//===========================================================================//
void Widget::setPosition(const math::Vector2F& position)
{
    mWidget.setPosition(CEGUI::UVector2(
            CEGUI::UDim(0.0f, position.x()),
            CEGUI::UDim(0.0f, position.y())));
}

//===========================================================================//
math::Vector2F Widget::getPosition() const
{
    const CEGUI::UVector2& position = mWidget.getPosition();
    return math::Vector2F(position.d_x.d_offset, position.d_y.d_offset);
}

//===========================================================================//
math::Vector2F Widget::getSize() const
{
    const CEGUI::USize& size = mWidget.getSize();
    return math::Vector2F(size.d_width.d_offset, size.d_height.d_offset);
}

//===========================================================================//
void Widget::addChild(gui::Widget& child)
{
    mWidget.addChild(&dynamic_cast<Widget&>(child).mWidget);
}
}
}
}
