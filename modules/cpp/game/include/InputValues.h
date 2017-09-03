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
#ifndef __NYRA_GAME_INPUT_VALUES_H__
#define __NYRA_GAME_INPUT_VALUES_H__

#include <vector>
#include <nyra/input/Keyboard.h>
#include <nyra/input/Mouse.h>

namespace nyra
{
namespace game
{
/*
 *  \class InputValue
 *  \brief Holds information about a single bound input. The idea is that
 *         instead of referring to a key by it's hardware name, it is instead
 *         mapped to a string that can be changed dynamically.
 */
class InputValue
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the input value.
     *
     *  \param keys The values to map this Input to.
     */
    InputValue(const std::vector<std::string>& keys);

    /*
     *  \func update
     *  \brief Updates the input state.
     *
     *  \param mouse The global mouse object
     *  \param keyboard The global keyboard object
     */
    void update(const input::Mouse& mouse,
                const input::Keyboard& keyboard);

    /*
     *  \func isPressed
     *  \brief Checks if the input is pressed
     *
     *  \return True if the button is pressed
     */
    bool isPressed() const
    {
        return mIsPressed;
    }

    /*
     *  \func isDown
     *  \brief Checks if the input is down
     *
     *  \return True if the button is down
     */
    bool isDown() const
    {
        return mIsDown;
    }

    /*
     *  \func isReleased
     *  \brief Checks if the input was released
     *
     *  \return True if the button was released
     */
    bool isReleased() const
    {
        return mIsReleased;
    }

private:
    bool mIsPressed;
    bool mIsDown;
    bool mIsReleased;
    std::vector<input::KeyCode> mKeyCodes;
    std::vector<size_t> mMouseCodes;
};
}
}

#endif
