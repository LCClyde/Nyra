/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/gui/qt/GroupBox.h>

namespace nyra
{
namespace gui
{
namespace qt
{
//===========================================================================//
GroupBox::GroupBox(const math::Vector2F& size,
                   const math::Vector2F& position,
                   const std::string& text) :
    Widget(new QGroupBox())
{
    Widget::setPosition(position);
    Widget::setSize(size);
    setText(text);

    const QString style =
            "QGroupBox"
            "{"
                "border: 1px solid gray;"
                "border-radius: 9px;"
                "margin-top: 0.5em;"
            "}"

            "QGroupBox::title"
            "{"
                "subcontrol-origin: margin;"
                "left: 10px;"
                "padding: 0 3px 0 3px;"
            "}";

    Widget::getQWidget<QGroupBox>()->setStyleSheet(style);
}
}
}
}
