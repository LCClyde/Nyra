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
#include <nyra/gui/qt/Spinner.h>
#include <QSpinBox>
#include <QAbstractSpinBox>
#include <QDoubleSpinBox>

namespace nyra
{
namespace gui
{
namespace qt
{
//===========================================================================//
Spinner::Spinner(const math::Vector2F& size,
                 const math::Vector2F& position,
                 Type type,
                 double startingValue,
                 double min,
                 double max,
                 double increment) :
    Widget(type == INTEGER ? static_cast<QWidget*>(new QSpinBox()) :
                             static_cast<QWidget*>(new QDoubleSpinBox())),
    mType(type)
{
    if (type == INTEGER)
    {
        getQWidget<QSpinBox>()->setRange(min, max);
        getQWidget<QSpinBox>()->setSingleStep(increment);
        connect(Widget::getQWidget<QSpinBox>(),
                SIGNAL(valueChanged(int)),
                this, SLOT(valueChanged(int)));
    }
    else
    {
        getQWidget<QDoubleSpinBox>()->setRange(min, max);
        getQWidget<QDoubleSpinBox>()->setSingleStep(increment);
        getQWidget<QDoubleSpinBox>()->setDecimals(3);
        connect(Widget::getQWidget<QDoubleSpinBox>(),
                SIGNAL(valueChanged(double)),
                this, SLOT(valueChanged(double)));
    }

    setPosition(position);
    setSize(size);
    setValue(startingValue);
}

//===========================================================================//
double Spinner::getValue() const
{
    if (mType == INTEGER)
    {
        return getQWidget<QSpinBox>()->value();
    }
    else
    {
        return getQWidget<QDoubleSpinBox>()->value();
    }
}

//===========================================================================//
void Spinner::setValue(double value)
{
    if (mType == INTEGER)
    {
        getQWidget<QSpinBox>()->setValue(value);
    }
    else
    {
        getQWidget<QDoubleSpinBox>()->setValue(value);
    }
}

//===========================================================================//
void Spinner::valueChanged(int value) const
{
    onValueChanged();
}

//===========================================================================//
void Spinner::valueChanged(double value) const
{
    std::cout << "On value changed was called\n";
    onValueChanged();
}
}
}
}
