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
#ifndef __NYRA_GUI_SLIDER_H__
#define __NYRA_GUI_SLIDER_H__

#include <nyra/gui/Widget.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace gui
{
/*
 *  \class Slider
 *  \brief Represents a moveable slider widget that scales from 0-1
 */
class Slider : public virtual Widget
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    ~Slider();

    /*
     *  \func getValue
     *  \brief Gets the current value of the slider between 0-1.
     *
     *  \return The current value.
     */
    virtual double getValue() const = 0;

    /*
     *  \func setValue
     *  \brief Sets the position of the slider.
     *
     *  \param value The desired value. Valid values are 0-1.
     */
    virtual void setValue(double value) = 0;

    /*
     *  \var onValueChanged
     *  \brief Called when the slider value changes.
     */
    core::Event<void(double)> onValueChanged;
};
}
}

#endif
