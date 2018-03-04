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
#include <nyra/input/ois/GlobalHandler.h>

namespace
{
//===========================================================================//
}

namespace nyra
{
namespace input
{
namespace ois
{
//===========================================================================//
OIS::InputManager* GlobalHandler::get(size_t winID)
{
    const auto iter = mMap.find(winID);
    if (iter != mMap.end())
    {
        return iter->second;
    }

    OIS::ParamList paramList;
    paramList.insert(std::make_pair(std::string("WINDOW"),
                                    std::to_string(winID)));

#if defined NYRA_WIN32
    paramList.insert(std::make_pair(std::string("w32_mouse"),
                                    std::string("DISCL_FOREGROUND" )));
    paramList.insert(std::make_pair(std::string("w32_mouse"),
                                    std::string("DISCL_NONEXCLUSIVE")));
    paramList.insert(std::make_pair(std::string("w32_keyboard"),
                                    std::string("DISCL_FOREGROUND")));
    paramList.insert(std::make_pair(std::string("w32_keyboard"),
                                    std::string("DISCL_NONEXCLUSIVE")));
#elif defined NYRA_POSIX
    paramList.insert(std::make_pair(std::string("x11_mouse_grab"),
                                    std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_mouse_hide"),
                                    std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_keyboard_grab"),
                                    std::string("false")));
    paramList.insert(std::make_pair(std::string("XAutoRepeatOn"),
                                    std::string("true")));
#endif

    OIS::InputManager* manager =
            OIS::InputManager::createInputSystem(paramList);
    mMap[winID] = manager;
    return manager;
}

//===========================================================================//
void GlobalHandler::initializeGlobal()
{
}

//===========================================================================//
void GlobalHandler::shutdownGlobal()
{
    if (!isInitialized())
    {
        for (auto iter : mMap)
        {
            iter.second->destroyInputSystem(iter.second);
        }
        mMap.clear();
    }
}
}
}
}
