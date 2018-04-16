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
#include <nyra/gui/qt/Label.h>

namespace nyra
{
namespace gui
{
namespace qt
{
//===========================================================================//
Label::Label(const std::string& text) :
    TextWidget(new QLabel())
{
    setText(text);
}

//===========================================================================//
Label::Label(const math::Vector2F& position,
             const std::string& text) :
    Label(text)
{
    Widget::setPosition(position);
}

//===========================================================================//
void Label::setText(const std::string& text)
{
    const QString qText(text.c_str());
    Widget::getQWidget<QLabel>()->setText(qText);

    const QFontMetrics metric(Widget::getQWidget<QLabel>()->font());
    Widget::setSize(math::Vector2F(metric.width(qText), metric.height()));
}
}
}
}
