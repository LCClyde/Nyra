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
#ifndef __NYRA_GUI_QT_SPINNER_H__
#define __NYRA_GUI_QT_SPINNER_H__

#include <nyra/gui/qt/Widget.h>

namespace nyra
{
namespace gui
{
namespace qt
{
/*
 *  \class Spinner
 *  \brief A class used to spinner used to set numbers.
 */
class Spinner : public QObject, public Widget
{
    Q_OBJECT

public:
    enum Type
    {
        INTEGER,
        DOUBLE
    };

    /*
     *  \func Constructor
     *  \brief Creates a default Button.
     *
     *  \param size The size of the Widget
     *  \param position The position of the Widget
     *  \param text The beginning text for the Widget.
     */
    Spinner(const math::Vector2F& size,
            const math::Vector2F& position,
            Type type,
            double startingValue,
            double min,
            double max,
            double increment);

    Spinner(const math::Vector2F& size,
            const math::Vector2F& position,
            Type type,
            double startingValue);

    /*
     *  \func getValue
     *  \brief Gets the current value.
     *
     *  \return The current value.
     */
    double getValue() const override;

    /*
     *  \func setValue
     *  \brief Sets the position.
     *
     *  \param value The desired value.
     */
    void setValue(double value);

private:
    const Type mType;
};
}
}
}

#endif
