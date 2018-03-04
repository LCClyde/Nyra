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
#ifndef __NYRA_GUI_TGUI_GLOBAL_HANDLER_H__
#define __NYRA_GUI_TGUI_GLOBAL_HANDLER_H__

#include <TGUI/TGUI.hpp>
#include <nyra/mem/GlobalHandler.h>

namespace nyra
{
namespace gui
{
namespace tgui
{
/*
 *  \class GlobalHandler
 *  \brief Handles the TGUI global init and shutdown commands.
 */
class GlobalHandler : public mem::GlobalHandler
{
public:
    /*
     *  \func getTheme
     *  \brief Creates a CEGUI Window object.
     *
     *  \param type The type that represents the widget in the XML.
     *  \return The created object.
     */
    ::tgui::Theme::Ptr getTheme() const
    {
        return mTheme;
    }

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    ::tgui::Theme::Ptr mTheme;
};
}
}
}

#endif
