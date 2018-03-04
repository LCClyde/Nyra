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
#include <sstream>
#include <nyra/win/sfml/Window.h>
#include <nyra/input/sfml/Mouse.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/gui/cegui/Gui.h>
#include <nyra/gui/cegui/Label.h>
#include <nyra/core/Time.h>

namespace
{
class GuiCreator
{
public:
    GuiCreator(nyra::gui::Gui& gui) :
        mGui(gui),
        mSize(256.0f, 40.0f),
        mOffset(0.0f, mSize.y + 2.0f)
    {
    }

    nyra::gui::cegui::Label* operator()(const std::string& name,
                                        const std::string& text)
    {
        nyra::gui::cegui::Label* label = new nyra::gui::cegui::Label(text);
        label->setPosition(mPosition);
        label->setSize(mSize);
        mGui[name] = label;
        mPosition += mOffset;
        return label;
    }

private:
    nyra::gui::Gui& mGui;
    const nyra::math::Vector2F mSize;
    const nyra::math::Vector2F mOffset;
    nyra::math::Vector2F mPosition;

};
}

using namespace nyra;

int main()
{
    win::sfml::Window window("Test SFML Window",
                             math::Vector2U(1280, 720),
                             math::Vector2I(450, 50));
    graphics::sfml::RenderTarget target(window);

    gui::cegui::Gui gui;
    GuiCreator creator(gui);
    gui::cegui::Label* position = creator("Position", "Position");
    gui::cegui::Label* delta = creator("Delta", "Delta");
    gui::cegui::Label* scroll = creator("Scroll", "Scroll");
    creator("LeftTitle", "Left Click");
    gui::cegui::Label* left = creator("Left", "    -   -   -");
    creator("RightTitle", "Right Click");
    gui::cegui::Label* right = creator("Right", "    -   -   -");
    creator("MiddleTitle", "Middle Click");
    gui::cegui::Label* middle = creator("Middle", "    -   -   -");

    input::sfml::Mouse mouse(window);

    while (window.isOpen())
    {
        window.update();
        mouse.update();

        std::stringstream ss;
        ss << "Position: " << mouse.getPosition();
        position->setText(ss.str());

        ss.clear();
        ss.str("");
        ss << "Delta: " << mouse.getDelta();
        delta->setText(ss.str());

        ss.clear();
        ss.str("");
        ss << "Scroll: " << mouse.getScroll();
        scroll->setText(ss.str());

        std::string button = "    ";
        button += (mouse.getButtonPressed(input::MOUSE_LEFT)) ? "X" : "-";
        button += (mouse.getButtonDown(input::MOUSE_LEFT)) ? "   X" : "   -";
        button += (mouse.getButtonReleased(input::MOUSE_LEFT)) ? "   X" : "   -";
        left->setText(button);

        button = "    ";
        button += (mouse.getButtonPressed(input::MOUSE_RIGHT)) ? "X" : "-";
        button += (mouse.getButtonDown(input::MOUSE_RIGHT)) ? "   X" : "   -";
        button += (mouse.getButtonReleased(input::MOUSE_RIGHT)) ? "   X" : "   -";
        right->setText(button);

        button = "    ";
        button += (mouse.getButtonPressed(input::MOUSE_MIDDLE)) ? "X" : "-";
        button += (mouse.getButtonDown(input::MOUSE_MIDDLE)) ? "   X" : "   -";
        button += (mouse.getButtonReleased(input::MOUSE_MIDDLE)) ? "   X" : "   -";
        middle->setText(button);

        target.clear(img::Color::WHITE);
        gui.render();
        target.flush();

        // Fake 30 FPS, just to slow down the updates.
        core::sleep(33);
    }
}
