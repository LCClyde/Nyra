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
#ifndef __NYRA_GAME_INPUT_H__
#define __NYRA_GAME_INPUT_H__

#include <vector>
#include <unordered_map>
#include <nyra/json/JSON.h>
#include <nyra/game/InputValues.h>
#include <nyra/input/sfml/Mouse.h>
#include <nyra/input/sfml/Keyboard.h>

namespace nyra
{
namespace game
{
/*
 *  \class Input
 *  \brief Creates a single location for input to be handled.
 *
 *  \tparam GameT The game type
 */
class Input
{
public:
    /*
     *  \func Constructor
     *  \brief Setups up the Input object
     *
     *  \param window The primary window associated with the mouse / keyboard
     *  \param filename The name of the input.json file.
     */
    Input(nyra::win::Window& window,
          const std::string& filename);

    /*
     *  \func update
     *  \brief Updates the input object.
     */
    void update();

    /*
     *  \func isPressed
     *  \brief Checks if the input is pressed
     *
     *  \param name The name of the input map
     *  \return True if the button is pressed
     */
    static bool isPressed(const std::string& name);

    /*
     *  \func isDown
     *  \brief Checks if the input is down
     *
     *  \param name The name of the input map
     *  \return True if the button is down
     */
    static bool isDown(const std::string& name);

    /*
     *  \func isReleased
     *  \brief Checks if the input was released
     *
     *  \param name The name of the input map
     *  \return True if the button was released
     */
    static bool isReleased(const std::string& name);

    /*
     *  \func getValue
     *  \brief Gets the value of the input
     *
     *  \param name The name of the input map
     *  \return The value
     */
    static float getValue(const std::string& name);

    /*
     *  \func getMouse
     *  \brief Gets the mouse object. Users should not use this, but instead
     *         use the is* and getValue functions.
     *
     *  \return The mouse
     */
    const input::Mouse& getMouse() const
    {
        return mMouse;
    }

private:
    input::sfml::Mouse mMouse;
    input::sfml::Keyboard mKeyboard;
    std::unordered_map<std::string, std::unique_ptr<InputValue>> mInputMap;
    static Input* mInput;
};
}
}

#endif
