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
#include <nyra/editor/NewContent.h>
#include <nyra/gui/qt/EditBox.h>
#include <nyra/gui/qt/Button.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/core/Path.h>
#include <nyra/editor/SystemMessage.h>

namespace nyra
{
namespace editor
{
//===========================================================================//
NewContent::NewContent(const std::string& subDirectory,
                       const std::string& extension) :
    mSubDirectory(subDirectory),
    mExtension(extension),
    mWindow("New " + mSubDirectory,
            math::Vector2F(512, 256),
            math::Vector2F(200, 200)),
    mGui(mWindow)
{
    // Make sure the subdirectory exists
    const std::string fullDirectory =
            core::path::join(core::DATA_PATH, mSubDirectory);
    if (!core::path::exists(fullDirectory))
    {
        core::path::makeDirectory(fullDirectory);
    }

    gui::Widget* widget = new gui::qt::Label(math::Vector2F(16, 16),
                                             mSubDirectory + " name");
    mGui["name label"] = widget;

    widget = new gui::qt::EditBox(math::Vector2F(490, 48),
                                  math::Vector2F(16, 64));
    mGui["edit"] = widget;

    widget = new gui::qt::Button(math::Vector2F(100, 48),
                                 math::Vector2F(100, 200),
                                 "OK");
    widget->activated = std::bind(&NewContent::ok, this);
    mGui["ok"] = widget;

    widget = new gui::qt::Button(math::Vector2F(100, 48),
                                 math::Vector2F(250, 200),
                                 "Cancel");
    widget->activated = std::bind(&NewContent::cancel, this);
    mGui["cancel"] = widget;
}

//===========================================================================//
std::string NewContent::run()
{
    while (mWindow.isOpen())
    {
        mWindow.update();
    }

    return mPathname;
}

//===========================================================================//
void NewContent::cancel()
{
    mWindow.close();
}

//===========================================================================//
void NewContent::ok()
{
    const std::string name = mGui["edit"].get().getText();

    if (!name.empty())
    {
        mPathname = core::path::join(
                core::path::join(core::DATA_PATH, mSubDirectory),
                name + "." + mExtension);

        if (core::path::exists(mPathname))
        {
            SystemMessage(name + " already exists").run();
            mPathname = "";
        }
    }

    mWindow.close();
}
}
}
