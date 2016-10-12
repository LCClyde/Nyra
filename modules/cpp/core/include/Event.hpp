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
#ifndef __NYRA_CORE_EVENT_HPP__
#define __NYRA_CORE_EVENT_HPP__

namespace nyra
{
namespace core
{
//===========================================================================//
template <typename RetT, typename ...ArgsT>
class EventCall
{
public:
    static RetT call(
            const boost::signals2::signal<RetT(ArgsT...)>& func,
            ArgsT... args)
    {
        auto optional = func(args...);
        if (optional)
        {
            return (*optional);
        }

        return RetT();
    }
};

//===========================================================================//
template <typename ...ArgsT>
class EventCall<void, ArgsT...>
{
public:
    static void call(
            const boost::signals2::signal<void(ArgsT...)>& func,
            ArgsT... args)
    {
        func(args...);
    }
};

//===========================================================================//
template <typename RetT, typename ...ArgsT>
RetT Event<RetT(ArgsT...)>::operator()(ArgsT... args) const
{
    return EventCall<RetT, ArgsT...>::call(mFunction, args...);
}

//===========================================================================//
template <typename RetT, typename ...ArgsT>
void Event<RetT(ArgsT...)>::reset()
{
    mFunction.disconnect_all_slots();
}

//===========================================================================//
template <typename RetT, typename ...ArgsT>
template <typename T>
void Event<RetT(ArgsT...)>::operator=(const T& func)
{
    mFunction.disconnect_all_slots();
    mFunction.connect(func);
}
}
}

#endif
