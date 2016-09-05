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
#include <nyra/pattern/GlobalUpdate.h>

namespace nyra
{
namespace pattern
{
//===========================================================================//
bool GlobalUpdate::tryUpdate(const void* data)
{
    bool ret = false;

    // If there is nothing in the data list (meaning it has not been used) or
    // if the data is already in the list then we have done a loop and should
    // update.
    if (mData.empty() || mData.find(data) != mData.end())
    {
        ret = true;
        mData.clear();
    }

    mData.insert(data);
    return ret;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const GlobalUpdate& update)
{
    os << "Global Update";
    return os;
}
}
}
