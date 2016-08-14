/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <stdexcept>
#include <nyra/pattern/GlobalHandler.h>

namespace nyra
{
namespace pattern
{
//===========================================================================//
void GlobalHandler::initialize(const void* handle)
{
    // Early out if passing in nullptr
    if (!handle)
    {
        throw std::runtime_error(
            "Attempting to initialize a GlobalHandler with a nullptr");
    }

    if (mHandles.size() == 0)
    {
        intializeGlobal();
    }

    if (mHandles.find(handle) == mHandles.end())
    {
        mHandles.insert(handle);
    }
}

//===========================================================================//
void GlobalHandler::shutdown(const void* handle)
{
    if (!handle)
    {
        throw std::runtime_error(
            "Attempting to shutdown a GlobalHandler with a nullptr");
    }

    auto iter = mHandles.find(handle);
    if (iter == mHandles.end())
    {
        throw std::runtime_error(
            "Removing an unknown handle from a GlobalHandler");
    }

    mHandles.erase(iter);

    if (mHandles.size() == 0)
    {
        shutdownGlobal();
    }
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalHandler& handler)
{
    os << "Abstract Global Handler";
    return os;
}
}
}
