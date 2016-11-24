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
#include <limits>
#include <nyra/gui/qt/Slider.h>
#include <nyra/math/Interpolate.h>
#include <iostream>

namespace nyra
{
namespace gui
{
namespace qt
{
//===========================================================================//
Slider::Slider() :
    Widget(mSlider),
    mSlider(Qt::Horizontal)
{
    mSlider.setMinimum(0),
    mSlider.setMaximum(std::numeric_limits<int>::max());
    connect(&mSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(valueChanged(int)));
}

//===========================================================================//
double Slider::getValue() const
{
    return normalizeValue(mSlider.value());
}

//===========================================================================//
void Slider::setValue(double value)
{
    value = std::min(std::max(value, 0.0), 1.0);
    const int diff = mSlider.maximum() - mSlider.minimum();
    mSlider.setValue(static_cast<int>(mSlider.minimum() + (diff * value)));
}

//===========================================================================//
double Slider::normalizeValue(int value) const
{
    const int diff = mSlider.maximum() - mSlider.minimum();
    return static_cast<double>(value - mSlider.minimum()) /
            static_cast<double>(diff);
}

//===========================================================================//
void Slider::valueChanged(int value) const
{
    onValueChanged(normalizeValue(value));
}
}
}
}
