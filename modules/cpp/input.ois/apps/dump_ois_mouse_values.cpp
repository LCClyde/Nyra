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
#include <nyra/win/qt/Window.h>
#include <nyra/win/ogre/Window.h>
#include <nyra/input/ois/Mouse.h>
#include <nyra/gui/qt/Gui.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/time/System.h>

using namespace nyra;

int main()
{
    // TODO: This does not work with a QT window. I only want to use it
    //       with Ogre windows at the moment so I am not tracking it down
    //       right now.
    win::qt::Window qWindow("Values",
                            math::Vector2U(400, 270),
                            math::Vector2I(50, 50));
    win::ogre::Window window("Test Mouse / Ogre Window",
                             math::Vector2U(1280, 720),
                             math::Vector2I(450, 50));

    gui::qt::Gui gui(qWindow);
    gui::qt::Label* position = new gui::qt::Label("Position");
    gui["Position"] = position;

    gui::qt::Label* delta = new gui::qt::Label("Delta");
    delta->setPosition(math::Vector2F(0.0f, 30.0f));
    gui["Delta"] = delta;

    gui::qt::Label* scroll = new gui::qt::Label("Scroll");
    scroll->setPosition(math::Vector2F(0.0f, 60.0f));
    gui["Scroll"] = scroll;

    gui::qt::Label* leftTitle = new gui::qt::Label("Left Click:");
    leftTitle->setPosition(math::Vector2F(0.0f, 90.0f));
    gui["LeftTitle"] = leftTitle;

    gui::qt::Label* left = new gui::qt::Label("    -   -   -");
    left->setPosition(math::Vector2F(0.0f, 120.0f));
    gui["Left"] = left;

    gui::qt::Label* rightTitle = new gui::qt::Label("Right Click:");
    rightTitle->setPosition(math::Vector2F(0.0f, 150.0f));
    gui["RightTitle"] = rightTitle;

    gui::qt::Label* right = new gui::qt::Label("    -   -   -");
    right->setPosition(math::Vector2F(0.0f, 180.0f));
    gui["Right"] = right;

    gui::qt::Label* middleTitle = new gui::qt::Label("Middle Click:");
    middleTitle->setPosition(math::Vector2F(0.0f, 210.0f));
    gui["MiddleTitle"] = middleTitle;

    gui::qt::Label* middle = new gui::qt::Label("    -   -   -");
    middle->setPosition(math::Vector2F(0.0f, 240.0f));
    gui["Middle"] = middle;

    input::ois::Mouse mouse(window);

    while (window.isOpen() && qWindow.isOpen())
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

        qWindow.update();

        // Fake 30 FPS, just to slow down the updates.
        time::sleep(33);
    }
}
