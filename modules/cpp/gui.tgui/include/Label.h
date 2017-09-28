/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_GUI_TGUI_LABEL_H__
#define __NYRA_GUI_TGUI_LABEL_H__

#include <nyra/gui/tgui/Widget.h>
#include <nyra/gui/Label.h>

namespace nyra
{
namespace gui
{
namespace tgui
{
/*
 *  \class Label
 *  \brief A class used to render text to the screen.
 */
class Label : public gui::Label, public Widget,
        private mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default Label.
     *
     *  \param text The beginning text for the Label.
     */
    Label(const std::string& text);

    /*
     *  \func setText
     *  \brief Sets the text of the widget.
     *
     *  \param text The desired text.
     */
    void setText(const std::string& text) override;

    /*
     *  \func getText
     *  \brief Gets the current text.
     *
     *  \return The value of the text.
     */
    std::string getText() const override;

private:
    ::tgui::Label::Ptr mLabel;
};
}
}
}

#endif
