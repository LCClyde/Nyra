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
#include <nyra/input/sfml/Keyboard.h>
#include <SFML/Window/Keyboard.hpp>

namespace nyra
{
namespace input
{
namespace sfml
{
//===========================================================================//
void Keyboard::update()
{
    mKeyBits[KEY_1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
    mKeyBits[KEY_2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
    mKeyBits[KEY_3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
    mKeyBits[KEY_4] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
    mKeyBits[KEY_5] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);
    mKeyBits[KEY_6] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num6);
    mKeyBits[KEY_7] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num7);
    mKeyBits[KEY_8] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num8);
    mKeyBits[KEY_9] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num9);
    mKeyBits[KEY_0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);

    mKeyBits[KEY_Q] = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    mKeyBits[KEY_W] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    mKeyBits[KEY_E] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    mKeyBits[KEY_R] = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    mKeyBits[KEY_T] = sf::Keyboard::isKeyPressed(sf::Keyboard::T);
    mKeyBits[KEY_Y] = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
    mKeyBits[KEY_U] = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
    mKeyBits[KEY_I] = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
    mKeyBits[KEY_O] = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
    mKeyBits[KEY_P] = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    mKeyBits[KEY_A] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    mKeyBits[KEY_S] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    mKeyBits[KEY_D] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    mKeyBits[KEY_F] = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    mKeyBits[KEY_G] = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
    mKeyBits[KEY_H] = sf::Keyboard::isKeyPressed(sf::Keyboard::H);
    mKeyBits[KEY_J] = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
    mKeyBits[KEY_K] = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
    mKeyBits[KEY_L] = sf::Keyboard::isKeyPressed(sf::Keyboard::L);
    mKeyBits[KEY_Z] = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    mKeyBits[KEY_X] = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    mKeyBits[KEY_C] = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    mKeyBits[KEY_V] = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
    mKeyBits[KEY_B] = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
    mKeyBits[KEY_N] = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
    mKeyBits[KEY_M] = sf::Keyboard::isKeyPressed(sf::Keyboard::M);

    mKeyBits[KEY_SPACE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    mKeyBits[KEY_ENTER] = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
    mKeyBits[KEY_ESCAPE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    mKeyBits[KEY_BACKSPACE] = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
    mKeyBits[KEY_TAB] = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    mKeyBits[KEY_MINUS] = sf::Keyboard::isKeyPressed(sf::Keyboard::Dash);
    mKeyBits[KEY_EQUALS] = sf::Keyboard::isKeyPressed(sf::Keyboard::Equal);
    mKeyBits[KEY_LEFT_BRACKET] = sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket);
    mKeyBits[KEY_RIGHT_BRACKET] = sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket);
    mKeyBits[KEY_SEMICOLON] = sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon);
    mKeyBits[KEY_APOSTROPHE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Quote);
    mKeyBits[KEY_TILDE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
    mKeyBits[KEY_BACKSLASH] = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash);
    mKeyBits[KEY_COMMA] = sf::Keyboard::isKeyPressed(sf::Keyboard::Comma);
    mKeyBits[KEY_PERIOD] = sf::Keyboard::isKeyPressed(sf::Keyboard::Period);
    mKeyBits[KEY_FORWARD_SLASH] = sf::Keyboard::isKeyPressed(sf::Keyboard::Slash);
    mKeyBits[KEY_RIGHT_SHIFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
    mKeyBits[KEY_LEFT_SHIFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    mKeyBits[KEY_RIGHT_CONTROL] = sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
    mKeyBits[KEY_LEFT_CONTROL] = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
    mKeyBits[KEY_RIGHT_ALT] = sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
    mKeyBits[KEY_LEFT_ALT] = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
    mKeyBits[KEY_LEFT_SYSTEM] = sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem);
    mKeyBits[KEY_RIGHT_SYSTEM] = sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
    mKeyBits[KEY_INSERT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Insert);
    mKeyBits[KEY_DELETE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Delete);

    // No locking keys for SFML
    //mKeyBits[KEY_CAPS_LOCK] = sf::Keyboard::isKeyPressed(sf::Keyboard::);
    //mKeyBits[KEY_NUM_LOCK] = sf::Keyboard::isKeyPressed(sf::Keyboard::);
    //mKeyBits[KEY_SCROLL_LOCK] = sf::Keyboard::isKeyPressed(sf::Keyboard::);

    mKeyBits[KEY_F1] = sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
    mKeyBits[KEY_F2] = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
    mKeyBits[KEY_F3] = sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
    mKeyBits[KEY_F4] = sf::Keyboard::isKeyPressed(sf::Keyboard::F4);
    mKeyBits[KEY_F5] = sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
    mKeyBits[KEY_F6] = sf::Keyboard::isKeyPressed(sf::Keyboard::F6);
    mKeyBits[KEY_F7] = sf::Keyboard::isKeyPressed(sf::Keyboard::F7);
    mKeyBits[KEY_F8] = sf::Keyboard::isKeyPressed(sf::Keyboard::F8);
    mKeyBits[KEY_F9] = sf::Keyboard::isKeyPressed(sf::Keyboard::F9);
    mKeyBits[KEY_F10] = sf::Keyboard::isKeyPressed(sf::Keyboard::F10);
    mKeyBits[KEY_F11] = sf::Keyboard::isKeyPressed(sf::Keyboard::F11);
    mKeyBits[KEY_F12] = sf::Keyboard::isKeyPressed(sf::Keyboard::F12);
    mKeyBits[KEY_F13] = sf::Keyboard::isKeyPressed(sf::Keyboard::F13);
    mKeyBits[KEY_F14] = sf::Keyboard::isKeyPressed(sf::Keyboard::F14);
    mKeyBits[KEY_F15] = sf::Keyboard::isKeyPressed(sf::Keyboard::F15);

    mKeyBits[KEY_NUMPAD_1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1);
    mKeyBits[KEY_NUMPAD_2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2);
    mKeyBits[KEY_NUMPAD_3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3);
    mKeyBits[KEY_NUMPAD_4] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4);
    mKeyBits[KEY_NUMPAD_5] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5);
    mKeyBits[KEY_NUMPAD_6] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6);
    mKeyBits[KEY_NUMPAD_7] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7);
    mKeyBits[KEY_NUMPAD_8] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8);
    mKeyBits[KEY_NUMPAD_9] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9);
    mKeyBits[KEY_NUMPAD_0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0);
    mKeyBits[KEY_NUMPAD_SUBTRACT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
    mKeyBits[KEY_NUMPAD_ADD] = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);

    // No numpad decimal
    //mKeyBits[KEY_NUMPAD_DECIMAL] = sf::Keyboard::isKeyPressed(sf::Keyboard::);
    mKeyBits[KEY_NUMPAD_MULTIPLY] = sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply);

    // No numpad enter
    //mKeyBits[KEY_NUMPAD_ENTER] = sf::Keyboard::isKeyPressed(sf::Keyboard::);

    // No numpad comma
    //mKeyBits[KEY_NUMPAD_COMMA] = sf::Keyboard::isKeyPressed(sf::Keyboard::);

    mKeyBits[KEY_NUMPAD_DIVIDE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Divide);

    // No numpad equals
    //mKeyBits[KEY_NUMPAD_EQUALS] = sf::Keyboard::isKeyPressed(sf::Keyboard::);

    mKeyBits[KEY_PAUSE] = sf::Keyboard::isKeyPressed(sf::Keyboard::Pause);
    mKeyBits[KEY_HOME] = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);
    mKeyBits[KEY_END] = sf::Keyboard::isKeyPressed(sf::Keyboard::End);
    mKeyBits[KEY_PAGE_UP] = sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp);
    mKeyBits[KEY_PAGE_DOWN] = sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown);
    mKeyBits[KEY_UP] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    mKeyBits[KEY_LEFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    mKeyBits[KEY_RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    mKeyBits[KEY_DOWN] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

    updateButtons(mKeyBits);
}
}
}
}
