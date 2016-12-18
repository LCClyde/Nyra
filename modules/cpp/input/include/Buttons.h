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
#ifndef __NYRA_INPUT_BUTTONS_H__
#define __NYRA_INPUT_BUTTONS_H__

#include <bitset>

namespace nyra
{
namespace input
{
/*
 *  \class Buttons
 *  \brief Class to abstract away binary buttons from input devices.
 *
 *  \tparam NumButtons The number of buttons supported by the device.
 */
template <size_t NumButtons>
class Buttons
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for inheritance.
     */
    virtual ~Buttons() = default;

    /*
     *  \func getNumButtons
     *  \brief Gets the number of buttons supported by the device
     *
     *  \return The number of buttons.
     */
    size_t getNumButtons() const
    {
        return NumButtons;
    }

    /*
     *  \func getButtonPressed
     *  \brief Checks if the button was just pressed this frame and not
     *         pressed the previous frame.
     *
     *  \param index The index of the button
     *  \return True if the button is pressed.
     */
    bool getButtonPressed(size_t index) const
    {
        return (!mPreviousState[index]) && mCurrentState[index];
    }

    /*
     *  \func getButtonReleased
     *  \brief Checks if the button was released this frame and pressed
     *         the previous frame.
     *
     *  \param index The index of the button.
     *  \return True if the button was released.
     */
    bool getButtonReleased(size_t index) const
    {
        return mPreviousState[index] && (!mCurrentState[index]);
    }

    /*
     *  \func getButtonDown
     *  \brief Check if the button is currently being held down.
     *
     *  \param index The index of the button
     *  \return True if the button down.
     */
    bool getButtonDown(size_t index) const
    {
        return mCurrentState[index];
    }

protected:
    void updateButtons(const std::bitset<NumButtons>& newState)
    {
        mPreviousState = mCurrentState;
        mCurrentState = newState;
    }

private:
    std::bitset<NumButtons> mCurrentState;
    std::bitset<NumButtons> mPreviousState;
};
}
}

#endif
