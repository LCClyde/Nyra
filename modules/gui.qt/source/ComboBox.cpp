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
#include <nyra/gui/qt/ComboBox.h>
#include <QAbstractItemView>
#include <Qt>

namespace nyra
{
namespace gui
{
namespace qt
{
//===========================================================================//
ComboBox::ComboBox(const math::Vector2F& size,
                   const math::Vector2F& position,
                   const std::vector<std::string>& text) :
    Widget(new QComboBox())
{
    Widget::setPosition(position);
    Widget::setSize(size);

    for (const std::string& s : text)
    {
        getQWidget<QComboBox>()->addItem(s.c_str());
    }

    getQWidget<QComboBox>()->view()->setVerticalScrollBarPolicy(
            Qt::ScrollBarAsNeeded);
}

//===========================================================================//
void ComboBox::setText(const std::string& text)
{
    const QString qText(text.c_str());
    const int index = getQWidget<QComboBox>()->findText(qText);

    if (index < 0)
    {
        throw std::runtime_error(text + " is not in combo box");
    }

    getQWidget<QComboBox>()->setCurrentIndex(index);
}

//===========================================================================//
std::string ComboBox::getText() const
{
    return getQWidget<QComboBox>()->currentText().toUtf8().constData();
}
}
}
}
