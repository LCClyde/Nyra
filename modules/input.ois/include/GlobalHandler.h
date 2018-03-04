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
#ifndef __NYRA_INPUT_OIS_GLOBAL_HANDLER_H__
#define __NYRA_INPUT_OIS_GLOBAL_HANDLER_H__

#include <unordered_map>
#include <OIS/OISInputManager.h>
#include <nyra/mem/GlobalHandler.h>

namespace nyra
{
namespace input
{
namespace ois
{
/*
 *  \class GlobalHandler
 *  \brief Global objects for OIS. Because we need multiple global objects
 *         for multiple windows, you must call get to initialize the system
 *         with your winID.
 *         When destroying devices, be sure to check that the global instance
 *         is running as it will be destroyed first and shutdown the devices
 *         under the hood.
 */
class GlobalHandler : public mem::GlobalHandler
{
public:
    /*
     *  \func get
     *  \brief Gets the OIS InputManager. This must be called once up front
     *         to initialize the InputManager with the winID.
     */
    OIS::InputManager* get(size_t winID);

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    std::unordered_map<size_t,  OIS::InputManager*> mMap;
};
}
}
}

#endif
