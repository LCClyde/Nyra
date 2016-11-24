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
#ifndef __NYRA_GUI_QT_SLIDER_H__
#define __NYRA_GUI_QT_SLIDER_H__

#include <QSlider>
#include <nyra/gui/qt/Widget.h>
#include <nyra/gui/Slider.h>

namespace nyra
{
namespace gui
{
namespace qt
{
/*
 *  \class Slider
 *  \brief Represents a moveable slider widget that scales from 0-1
 */
class Slider : public QObject, public gui::Slider, public Widget
{
    Q_OBJECT

public:
    /*
     *  \func Constructor
     *  \brief Sets up a default Slider object.
     */
    Slider();

    /*
     *  \func getValue
     *  \brief Gets the current value of the slider between 0-1.
     *
     *  \return The current value.
     */
    double getValue() const override;

    /*
     *  \func setValue
     *  \brief Sets the position of the slider.
     *
     *  \param value The desired value. Valid values are 0-1.
     */
    void setValue(double value) override;

private slots:
    void valueChanged(int value) const;

private:
    double normalizeValue(int value) const;

    QSlider mSlider;
};
}
}
}

#endif
