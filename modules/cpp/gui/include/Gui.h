/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_GUI_GUI_H__
#define __NYRA_GUI_GUI_H__

#include <mem/Tree.h>

namespace nyra
{
namespace gui
{
/*
 *  \class Gui
 *  \brief The top level class for graphical user interface.
 */
class Gui : mem::Tree<Widget>
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    virtual ~Gui();

    /*
     *  \func init
     *  \brief Initializes a Gui.
     *
     *  \param winId The window ID that is associated with this Gui.
     */
    virtual void init(size_t winId) = 0;

    /*
     *  \func update
     *  \brief Updates all the elements in the Gui.
     *
     *  \param deltaTime The time in seconds that has passed since the
     *         last update.
     */
    virtual void update(double deltaTime) = 0;

    /*
     *  \func render
     *  \brief Renders all the widgets in the Gui.
     */
    virtual void render() = 0;
};
}
}

#endif
