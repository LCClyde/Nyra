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
#include <nyra/json/JSON.h>
#include <nyra/game/Input.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace game
{
Input* Input::mInput = nullptr;

Input::Input(nyra::win::Window& window,
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

void Input::update()
{
    mMouse.update();
    mKeyboard.update();
    for (auto& map : mInputMap)
    {
        map.second->update(mMouse, mKeyboard);
    }
}

bool Input::isPressed(const std::string& name)
{
    const auto& values = mInput->mInputMap.at(name);
    return values->isPressed();
}

bool Input::isDown(const std::string& name)
{
    const auto& values = mInput->mInputMap.at(name);
    return values->isDown();
}

bool Input::isReleased(const std::string& name)
{
    const auto& values = mInput->mInputMap.at(name);
    return values->isReleased();
}

float Input::getValue(const std::string& name)
{
    const auto& values = mInput->mInputMap.at(name);
    return values->getValue();
}
}
}

