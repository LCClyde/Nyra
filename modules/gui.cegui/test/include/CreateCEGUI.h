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
#ifndef __NYRA_TEST_CREATE_CEGUI_H__
#define __NYRA_TEST_CREATE_CEGUI_H__

#include <nyra/gui/cegui/Gui.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/win/sfml/Window.h>
#include <nyra/input/sfml/Mouse.h>
#include <nyra/core/FPS.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace test
{
class CreateCEGUI
{
public:
    CreateCEGUI() :
        mWindow("Test CEGUI",
                math::Vector2U(256.0f, 128.0f),
                math::Vector2I(0, 0)),
        mTarget(mWindow),
        mMouse(mWindow),
        mGUI(mMouse)
    {
    }

    template <typename T>
    T* create(const std::string& text,
              const std::string& name = "widget")
    {
        T* widget = new T(text);
        mGUI[name] = widget;
        return widget;
    }

    img::Image update()
    {
        mWindow.update();
        mMouse.update();
        mTarget.clear(img::Color::WHITE);
        mGUI.update(mFPS());
        mGUI.render();
        mTarget.flush();
        return mTarget.getPixels();
    }

    void saveBuffer(const std::string& pathname)
    {
        core::write(update(), pathname);
    }

private:
    win::sfml::Window mWindow;
    graphics::sfml::RenderTarget mTarget;
    input::sfml::Mouse mMouse;
    core::FPS mFPS;
    gui::cegui::Gui mGUI;
};
}
}

#endif
