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
#include <nyra/editor/SystemMessage.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/gui/qt/Button.h>

namespace nyra
{
namespace editor
{
//===========================================================================//
SystemMessage::SystemMessage(const std::string& msg) :
    DialogWindow("Message",
                 math::Vector2U(512, 128),
                 math::Vector2I(30, 30))
{
    gui::Widget* widget = new gui::qt::Label(math::Vector2U(16, 16),
                                             msg);
    mGui["message"] = widget;

    widget = new gui::qt::Button(math::Vector2U(64, 40),
                                 math::Vector2I(256 - 32, 60),
                                 "OK");
    widget->activated = std::bind(&SystemMessage::ok, this);
    mGui["ok"] = widget;
}

//===========================================================================//
void SystemMessage::run()
{
    while (update())
    {
    }
}

//===========================================================================//
void SystemMessage::ok()
{
    mWindow.close();
}
}
}
