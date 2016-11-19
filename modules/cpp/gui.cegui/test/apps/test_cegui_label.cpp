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
#include <nyra/gui/cegui/Gui.h>
#include <nyra/test/Test.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/win/sfml/Window.h>
#include <nyra/gui/cegui/Label.h>
#include <nyra/img/Image.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
TEST(Event, Call)
{
    // Currently, CEGUI will only render to a Window.
    // It does not work with an offscreen target by itself.
    win::sfml::Window window("test_cegui_gui",
                             math::Vector2U(256, 32),
                             math::Vector2I(0, 0));
    graphics::sfml::RenderTarget target(window.getID());

    Gui gui;
    Label* label = new Label("Hello World");

    // TODO: I should not have to set the size for a label.
    label->setSize(math::Vector2F(256.0f, 32.0f));
    gui["A"] = label;

    window.update();
    target.clear(img::Color::WHITE);
    gui.render();
    target.flush();

    // TODO: This looks incorrect. It needs to be fixed.
    img::Image truth = core::readArchive<img::Image>(core::path::join(
            core::DATA_PATH, "textures/test_cegui_label.png"));
    EXPECT_EQ(truth, target.getPixels());
}
}
}
}

NYRA_TEST()
