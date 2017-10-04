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
template <typename GameT>
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
    Input(const nyra::win::Window& window,
          const std::string& filename) :
        mMouse(window),
        mKeyboard(window)
    {
        mInput = this;
        const json::JSON tree = core::read<json::JSON>(
                core::path::join(core::DATA_PATH, "input/" + filename));

        if (tree.has("input"))
        {
            for (size_t ii = 0; ii < tree["input"].loopSize(); ++ii)
            {
                const auto& inputJSON = tree["input"][ii];
                const std::string name = inputJSON["name"].get();
                std::vector<std::string> values;
                for (size_t jj = 0; jj < inputJSON["values"].loopSize(); ++jj)
                {
                    values.push_back(inputJSON["values"][jj].get());
                }
                mInputMap[name].reset(new InputValue(values));
            }
        }
    }

    /*
     *  \func update
     *  \brief Updates the input object.
     */
    void update()
    {
        mMouse.update();
        mKeyboard.update();
        for (auto& map : mInputMap)
        {
            map.second->update(mMouse, mKeyboard);
        }
    }

    /*
     *  \func isPressed
     *  \brief Checks if the input is pressed
     *
     *  \param name The name of the input map
     *  \return True if the button is pressed
     */
    static bool isPressed(const std::string& name)
    {
        const auto& values = mInput->mInputMap.at(name);
        return values->isPressed();
    }

    /*
     *  \func isDown
     *  \brief Checks if the input is down
     *
     *  \param name The name of the input map
     *  \return True if the button is down
     */
    static bool isDown(const std::string& name)
    {
        const auto& values = mInput->mInputMap.at(name);
        return values->isDown();
    }

    /*
     *  \func isReleased
     *  \brief Checks if the input was released
     *
     *  \param name The name of the input map
     *  \return True if the button was released
     */
    static bool isReleased(const std::string& name)
    {
        const auto& values = mInput->mInputMap.at(name);
        return values->isReleased();
    }

    /*
     *  \func getValue
     *  \brief Gets the value of the input
     *
     *  \param name The name of the input map
     *  \return The value
     */
    static float getValue(const std::string& name)
    {
        const auto& values = mInput->mInputMap.at(name);
        return values->getValue();
    }

    /*
     *  \func getMouse
     *  \brief Gets the mouse object. Users should not use this, but instead
     *         use the is* and getValue functions.
     *
     *  \return The mouse
     */
    const typename GameT::Input::Mouse& getMouse() const
    {
        return mMouse;
    }

private:
    typename GameT::Input::Mouse mMouse;
    typename GameT::Input::Keyboard mKeyboard;
    std::unordered_map<std::string, std::unique_ptr<InputValue>> mInputMap;
    static Input* mInput;
};

template <typename GameT>
Input<GameT>* Input<GameT>::mInput = nullptr;
}
}

#endif
