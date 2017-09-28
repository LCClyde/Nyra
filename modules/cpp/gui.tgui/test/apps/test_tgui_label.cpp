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
#include <nyra/gui/tgui/Gui.h>
#include <nyra/test/Test.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/win/sfml/Window.h>
#include <nyra/gui/tgui/Label.h>
#include <nyra/img/Image.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace gui
{
namespace tgui
{
TEST(TGUI, Label)
{
    win::sfml::Window window("test_tgui_gui",
                             math::Vector2U(512, 256),
                             math::Vector2I(0, 0));
    graphics::sfml::RenderTarget target(window);

    Gui gui(window);
    Label* label = new Label("Hello World");
    gui["A"] = label;

    //while (true)
    {
        window.update();
        target.clear(img::Color::GRAY);
        gui.render();
        target.flush();
    }

    // TOOD: This does not work
    core::write(target.getPixels(), "test_tgui_label.png");
}
}
}

NYRA_TEST()
