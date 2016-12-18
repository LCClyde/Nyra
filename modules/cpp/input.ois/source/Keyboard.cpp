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
 #include <nyra/input/ois/Keyboard.h>

namespace nyra
{
namespace input
{
namespace ois
{
//===========================================================================//
Keyboard::Keyboard(const win::Window& window) :
    mWinID(window.getID()),
    mKeyboard(*static_cast<OIS::Keyboard*>(getGlobalInstance().get(mWinID)->
            createInputObject(OIS::OISKeyboard, false)))
{
}

//===========================================================================//
Keyboard::~Keyboard()
{
    if (getGlobalInstance().isInitialized())
    {
        getGlobalInstance().get(mWinID)->destroyInputObject(&mKeyboard);
    }
}

//===========================================================================//
void Keyboard::update()
{
    mKeyboard.capture();

    mKeyBits[KEY_1] = mKeyboard.isKeyDown(OIS::KC_1);
    mKeyBits[KEY_2] = mKeyboard.isKeyDown(OIS::KC_2);
    mKeyBits[KEY_3] = mKeyboard.isKeyDown(OIS::KC_3);
    mKeyBits[KEY_4] = mKeyboard.isKeyDown(OIS::KC_4);
    mKeyBits[KEY_5] = mKeyboard.isKeyDown(OIS::KC_5);
    mKeyBits[KEY_6] = mKeyboard.isKeyDown(OIS::KC_6);
    mKeyBits[KEY_7] = mKeyboard.isKeyDown(OIS::KC_7);
    mKeyBits[KEY_8] = mKeyboard.isKeyDown(OIS::KC_8);
    mKeyBits[KEY_9] = mKeyboard.isKeyDown(OIS::KC_9);
    mKeyBits[KEY_0] = mKeyboard.isKeyDown(OIS::KC_0);

    mKeyBits[KEY_Q] = mKeyboard.isKeyDown(OIS::KC_Q);
    mKeyBits[KEY_W] = mKeyboard.isKeyDown(OIS::KC_W);
    mKeyBits[KEY_E] = mKeyboard.isKeyDown(OIS::KC_E);
    mKeyBits[KEY_R] = mKeyboard.isKeyDown(OIS::KC_R);
    mKeyBits[KEY_T] = mKeyboard.isKeyDown(OIS::KC_T);
    mKeyBits[KEY_Y] = mKeyboard.isKeyDown(OIS::KC_Y);
    mKeyBits[KEY_U] = mKeyboard.isKeyDown(OIS::KC_U);
    mKeyBits[KEY_I] = mKeyboard.isKeyDown(OIS::KC_I);
    mKeyBits[KEY_O] = mKeyboard.isKeyDown(OIS::KC_O);
    mKeyBits[KEY_P] = mKeyboard.isKeyDown(OIS::KC_P);
    mKeyBits[KEY_A] = mKeyboard.isKeyDown(OIS::KC_A);
    mKeyBits[KEY_S] = mKeyboard.isKeyDown(OIS::KC_S);
    mKeyBits[KEY_D] = mKeyboard.isKeyDown(OIS::KC_D);
    mKeyBits[KEY_F] = mKeyboard.isKeyDown(OIS::KC_F);
    mKeyBits[KEY_G] = mKeyboard.isKeyDown(OIS::KC_G);
    mKeyBits[KEY_H] = mKeyboard.isKeyDown(OIS::KC_H);
    mKeyBits[KEY_J] = mKeyboard.isKeyDown(OIS::KC_J);
    mKeyBits[KEY_K] = mKeyboard.isKeyDown(OIS::KC_K);
    mKeyBits[KEY_L] = mKeyboard.isKeyDown(OIS::KC_L);
    mKeyBits[KEY_Z] = mKeyboard.isKeyDown(OIS::KC_Z);
    mKeyBits[KEY_X] = mKeyboard.isKeyDown(OIS::KC_X);
    mKeyBits[KEY_C] = mKeyboard.isKeyDown(OIS::KC_C);
    mKeyBits[KEY_V] = mKeyboard.isKeyDown(OIS::KC_V);
    mKeyBits[KEY_B] = mKeyboard.isKeyDown(OIS::KC_B);
    mKeyBits[KEY_N] = mKeyboard.isKeyDown(OIS::KC_N);
    mKeyBits[KEY_M] = mKeyboard.isKeyDown(OIS::KC_M);

    mKeyBits[KEY_SPACE] = mKeyboard.isKeyDown(OIS::KC_SPACE);
    mKeyBits[KEY_ENTER] = mKeyboard.isKeyDown(OIS::KC_RETURN);
    mKeyBits[KEY_ESCAPE] = mKeyboard.isKeyDown(OIS::KC_ESCAPE);
    mKeyBits[KEY_BACKSPACE] = mKeyboard.isKeyDown(OIS::KC_BACK);
    mKeyBits[KEY_TAB] = mKeyboard.isKeyDown(OIS::KC_TAB);
    mKeyBits[KEY_MINUS] = mKeyboard.isKeyDown(OIS::KC_MINUS);
    mKeyBits[KEY_EQUALS] = mKeyboard.isKeyDown(OIS::KC_EQUALS);
    mKeyBits[KEY_LEFT_BRACKET] = mKeyboard.isKeyDown(OIS::KC_LBRACKET);
    mKeyBits[KEY_RIGHT_BRACKET] = mKeyboard.isKeyDown(OIS::KC_RBRACKET);
    mKeyBits[KEY_SEMICOLON] = mKeyboard.isKeyDown(OIS::KC_SEMICOLON);
    mKeyBits[KEY_APOSTROPHE] = mKeyboard.isKeyDown(OIS::KC_APOSTROPHE);
    mKeyBits[KEY_TILDE] = mKeyboard.isKeyDown(OIS::KC_GRAVE);
    mKeyBits[KEY_BACKSLASH] = mKeyboard.isKeyDown(OIS::KC_BACKSLASH);
    mKeyBits[KEY_COMMA] = mKeyboard.isKeyDown(OIS::KC_COMMA);
    mKeyBits[KEY_PERIOD] = mKeyboard.isKeyDown(OIS::KC_PERIOD);
    mKeyBits[KEY_FORWARD_SLASH] = mKeyboard.isKeyDown(OIS::KC_SLASH);
    mKeyBits[KEY_RIGHT_SHIFT] = mKeyboard.isKeyDown(OIS::KC_RSHIFT);
    mKeyBits[KEY_LEFT_SHIFT] = mKeyboard.isKeyDown(OIS::KC_LSHIFT);
    mKeyBits[KEY_RIGHT_CONTROL] = mKeyboard.isKeyDown(OIS::KC_RCONTROL);
    mKeyBits[KEY_LEFT_CONTROL] = mKeyboard.isKeyDown(OIS::KC_LCONTROL);
    mKeyBits[KEY_RIGHT_ALT] = mKeyboard.isKeyDown(OIS::KC_RMENU);
    mKeyBits[KEY_LEFT_ALT] = mKeyboard.isKeyDown(OIS::KC_LMENU);
    mKeyBits[KEY_LEFT_SYSTEM] = mKeyboard.isKeyDown(OIS::KC_LWIN);
    mKeyBits[KEY_RIGHT_SYSTEM] = mKeyboard.isKeyDown(OIS::KC_RWIN);
    mKeyBits[KEY_INSERT] = mKeyboard.isKeyDown(OIS::KC_INSERT);
    mKeyBits[KEY_DELETE] = mKeyboard.isKeyDown(OIS::KC_DELETE);
    mKeyBits[KEY_CAPS_LOCK] = mKeyboard.isKeyDown(OIS::KC_CAPITAL);
    mKeyBits[KEY_NUM_LOCK] = mKeyboard.isKeyDown(OIS::KC_NUMLOCK);
    mKeyBits[KEY_SCROLL_LOCK] = mKeyboard.isKeyDown(OIS::KC_SCROLL);

    mKeyBits[KEY_F1] = mKeyboard.isKeyDown(OIS::KC_F1);
    mKeyBits[KEY_F2] = mKeyboard.isKeyDown(OIS::KC_F2);
    mKeyBits[KEY_F3] = mKeyboard.isKeyDown(OIS::KC_F3);
    mKeyBits[KEY_F4] = mKeyboard.isKeyDown(OIS::KC_F4);
    mKeyBits[KEY_F5] = mKeyboard.isKeyDown(OIS::KC_F5);
    mKeyBits[KEY_F6] = mKeyboard.isKeyDown(OIS::KC_F6);
    mKeyBits[KEY_F7] = mKeyboard.isKeyDown(OIS::KC_F7);
    mKeyBits[KEY_F8] = mKeyboard.isKeyDown(OIS::KC_F8);
    mKeyBits[KEY_F9] = mKeyboard.isKeyDown(OIS::KC_F9);
    mKeyBits[KEY_F10] = mKeyboard.isKeyDown(OIS::KC_F10);
    mKeyBits[KEY_F11] = mKeyboard.isKeyDown(OIS::KC_F11);
    mKeyBits[KEY_F12] = mKeyboard.isKeyDown(OIS::KC_F12);
    mKeyBits[KEY_F13] = mKeyboard.isKeyDown(OIS::KC_F13);
    mKeyBits[KEY_F14] = mKeyboard.isKeyDown(OIS::KC_F14);
    mKeyBits[KEY_F15] = mKeyboard.isKeyDown(OIS::KC_F15);

    mKeyBits[KEY_NUMPAD_1] = mKeyboard.isKeyDown(OIS::KC_NUMPAD1);
    mKeyBits[KEY_NUMPAD_2] = mKeyboard.isKeyDown(OIS::KC_NUMPAD2);
    mKeyBits[KEY_NUMPAD_3] = mKeyboard.isKeyDown(OIS::KC_NUMPAD3);
    mKeyBits[KEY_NUMPAD_4] = mKeyboard.isKeyDown(OIS::KC_NUMPAD4);
    mKeyBits[KEY_NUMPAD_5] = mKeyboard.isKeyDown(OIS::KC_NUMPAD5);
    mKeyBits[KEY_NUMPAD_6] = mKeyboard.isKeyDown(OIS::KC_NUMPAD6);
    mKeyBits[KEY_NUMPAD_7] = mKeyboard.isKeyDown(OIS::KC_NUMPAD7);
    mKeyBits[KEY_NUMPAD_8] = mKeyboard.isKeyDown(OIS::KC_NUMPAD8);
    mKeyBits[KEY_NUMPAD_9] = mKeyboard.isKeyDown(OIS::KC_NUMPAD9);
    mKeyBits[KEY_NUMPAD_0] = mKeyboard.isKeyDown(OIS::KC_NUMPAD0);
    mKeyBits[KEY_NUMPAD_SUBTRACT] = mKeyboard.isKeyDown(OIS::KC_SUBTRACT);
    mKeyBits[KEY_NUMPAD_ADD] = mKeyboard.isKeyDown(OIS::KC_ADD);
    mKeyBits[KEY_NUMPAD_DECIMAL] = mKeyboard.isKeyDown(OIS::KC_DECIMAL);
    mKeyBits[KEY_NUMPAD_MULTIPLY] = mKeyboard.isKeyDown(OIS::KC_MULTIPLY);
    mKeyBits[KEY_NUMPAD_ENTER] = mKeyboard.isKeyDown(OIS::KC_NUMPADENTER);
    mKeyBits[KEY_NUMPAD_COMMA] = mKeyboard.isKeyDown(OIS::KC_NUMPADCOMMA);
    mKeyBits[KEY_NUMPAD_DIVIDE] = mKeyboard.isKeyDown(OIS::KC_DIVIDE);
    mKeyBits[KEY_NUMPAD_EQUALS] = mKeyboard.isKeyDown(OIS::KC_NUMPADEQUALS);

    mKeyBits[KEY_PAUSE] = mKeyboard.isKeyDown(OIS::KC_PAUSE);
    mKeyBits[KEY_HOME] = mKeyboard.isKeyDown(OIS::KC_HOME);
    mKeyBits[KEY_END] = mKeyboard.isKeyDown(OIS::KC_END);
    mKeyBits[KEY_PAGE_UP] = mKeyboard.isKeyDown(OIS::KC_PGUP);
    mKeyBits[KEY_PAGE_DOWN] = mKeyboard.isKeyDown(OIS::KC_PGDOWN);
    mKeyBits[KEY_UP] = mKeyboard.isKeyDown(OIS::KC_UP);

    mKeyBits[KEY_LEFT] = mKeyboard.isKeyDown(OIS::KC_LEFT);
    mKeyBits[KEY_RIGHT] = mKeyboard.isKeyDown(OIS::KC_RIGHT);
    mKeyBits[KEY_DOWN] = mKeyboard.isKeyDown(OIS::KC_DOWN);

    updateButtons(mKeyBits);
}
}
}
}
