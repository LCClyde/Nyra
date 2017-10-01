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
#include <iostream>
#include <nyra/gui/cegui/Gui.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/win/sfml/Window.h>
#include <nyra/input/sfml/Mouse.h>
#include <nyra/core/FPS.h>
#include <nyra/gui/cegui/Panel.h>
#include <nyra/gui/cegui/Label.h>
#include <nyra/gui/cegui/Button.h>
#include <nyra/gui/cegui/Image.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

using namespace nyra;

namespace
{
static gui::cegui::Label* label = nullptr;
static int32_t timesPushed = -1;

void setButtonText()
{
    label->setText("Button Pushed " +
            core::str::toString(++timesPushed) +
            " times.");
}
}

int main(int argc, char** argv)
{
    try
    {
        win::sfml::Window window("Sample CEGUI",
                                 math::Vector2U(1280, 720),
                                 math::Vector2I());
        graphics::sfml::RenderTarget target(window);
        input::sfml::Mouse mouse(window);
        core::FPS fps;
        gui::cegui::Gui gui(mouse);

        gui::cegui::Panel* panel = new gui::cegui::Panel("Panel");
        panel->setSize(math::Vector2F(1000.0f, 650.0f));
        panel->setPosition(math::Vector2F(140.0f, 35.0f));
        gui["panel"] = panel;

        label = new gui::cegui::Label("");
        label->setSize(math::Vector2F(256.0f, 32.0f));
        label->setPosition(math::Vector2F(10.0f, 10.0f));
        setButtonText();
        gui["panel"]["label"] = label;

        gui::cegui::Button* button = new gui::cegui::Button("Button");
        button->setSize(math::Vector2F(160.0f, 32.0f));
        button->setPosition(math::Vector2F(10.0f, 50.0f));
        button->activated = setButtonText;
        gui["panel"]["button"] = button;

        gui::cegui::Image* image = new gui::cegui::Image(core::path::join(
                core::DATA_PATH, "textures/test_gui_image.png"));
        image->setPosition(math::Vector2F(400.0f, 50.0f));
        gui["panel"]["image"] = image;

        while (window.isOpen())
        {
            window.update();
            mouse.update();
            gui.update(fps());

            target.clear(img::Color::BLACK);
            gui.render();
            target.flush();
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
        return 1;
    }

    return 0;
}
