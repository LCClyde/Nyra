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
#ifndef __NYRA_EVENT_EVENT_H__
#define __NYRA_EVENT_EVENT_H__

#include <boost/signals2/signal.hpp>
#include <memory>
#include <functional>

namespace nyra
{
namespace event
{
/*
 *  \class Event
 *  \brief A generic Event class that can take in any callable and run it.
 *         TODO: Add disconnection logic.
 */
class Event
{
private:
    template <typename T>
    struct identity
    {
        typedef T type;
    };

public:
    /*
     *  \func add
     *  \brief Adds a function as an event.
     *
     *  \tparam ArgsT The parameter types
     *  \param func The function to add.
     */
    template <typename ...ArgsT>
    void add(void func(ArgsT...))
    {
        create<ArgsT...>();
        reinterpret_cast<boost::signals2::signal<void(ArgsT...)>*>(
                mFunction.get())->connect(func);
    }

    /*
     *  \func add
     *  \brief Adds an std::function as an event.
     *
     *  \tparam ArgsT The parameter types
     *  \param func The function to add.
     */
    template <typename ...ArgsT>
    void add(typename identity<std::function<void(ArgsT...)> >::type func)
    {
        create<ArgsT...>();
        reinterpret_cast<boost::signals2::signal<void(ArgsT...)>*>(
                mFunction.get())->connect(func);
    }

    /*
     *  \func add
     *  \brief Adds a functor as an event.
     *
     *  \tparam ArgsT The parameter types
     *  \tparam FunctorT The functor type.
     *  \param functor The function to add.
     */
    template <typename ...ArgsT, typename FunctorT>
    void add(const FunctorT& functor)
    {
        create<ArgsT...>();
        reinterpret_cast<boost::signals2::signal<void(ArgsT...)>*>(
                mFunction.get())->connect(functor);

    }

    /*
     *  \func call
     *  \brief Calls all added functions.
     *
     *  \tparam ArgsT The parameter types
     *  \param args The parameters
     */
    template <typename ...ArgsT>
    void call(ArgsT... args)
    {
        (*reinterpret_cast<boost::signals2::signal<void(ArgsT...)>*>(
                mFunction.get()))(args...);
    }

private:
    template <typename ...ArgsT>
    void create()
    {
        if (!mFunction.get())
        {
            mFunction.reset(new boost::signals2::signal<void(ArgsT...)>());
        }
    }

    std::shared_ptr<void> mFunction;
};
}
}

#endif
