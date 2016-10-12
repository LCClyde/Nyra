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
#ifndef __NYRA_CORE_EVENT_H__
#define __NYRA_CORE_EVENT_H__

#include <boost/signals2/signal.hpp>

namespace nyra
{
namespace core
{
/*
 *  \class Event
 *  \brief DO NOT USE. This is to allow template specialization.
 *
 *  \tparam T The function type.
 */
template <typename T>
class Event;

/*
 *  \class Event
 *  \brief A generic Event class that can take in any callable and run it.
 *
 *  \tparam RetT The return type of the function
 *  \tparam ArgsT The parameter types of the function
 */
template <typename RetT, typename ...ArgsT>
class Event <RetT(ArgsT...)>
{
public:
    /*
     *  \func Assignment Operator
     *  \brief Adds a function as an event.
     *
     *  \tparam T The function type. Known supported types are:
     *          std::function
     *          lambda
     *          free functions
     *          functor
     *          member functions can be wrapped in a functor or use std::bind
     *  \param func The function to add.
     */
    template <typename T>
    void operator=(const T& func);

    /*
     *  \func Functor
     *  \brief Calls all added functions. It is safe to call this if no
     *         function is assigned.
     *
     *  \param args The parameters
     *  \return The return of the function. This will be default constructed
     *          if the function is not valid.
     */
    RetT operator()(ArgsT... args) const;

    /*
     *  \func reset
     *  \brief Resets the function, meaning nothing is set.
     */
    void reset();

private:
    boost::signals2::signal<RetT(ArgsT...)> mFunction;
};
}
}

#include <nyra/core/Event.hpp>

#endif
