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
#ifndef __NYRA_PATTERN_GLOBAL_DEPENDENCY_H__
#define __NYRA_PATTERN_GLOBAL_DEPENDENCY_H__

#include <nyra/pattern/GlobalHandler.h>
#include <nyra/pattern/Singleton.h>

namespace nyra
{
namespace pattern
{
/*
 *  \class GlobalDependency
 *  \brief A base class to allow easy integration of a GlobalHandler
 *         dependency. For simple cases, a class can inherit from this
 *         privately to automagically add itself to the GlobalHandler.
 *         This also provides access to the GlobalHandler singleton. Classes
 *         wish to integrate this logic without a singleton should avoid
 *         this class.
 *         NOTE: This class does not archive as it does not have any state
 *               on its own.
 *         NOTE: This class does not write to stdout as it will never live
 *               outside of inheritance.
 *
 *  \tparam HandlerT The GlobalHandler that will be interacted with.
 */
template <typename HandlerT>
class GlobalDependency
{
public:
    /*
     *  \type GlobalInstance
     *  \brief The typedef for the underlying singleton.
     */
    typedef Singleton<HandlerT> GlobalInstance;

    /*
     *  \func Constructor
     *  \brief Adds the dependency to the global handler.
     */
    GlobalDependency()
    {
        GlobalInstance::get().initialize();
    }

    /*
     *  \func Destructor
     *  \brief Removes the dependency from the global handler.
     */
    virtual ~GlobalDependency()
    {
        GlobalInstance::get().shutdown();
    }

    /*
     *  \func getGlobalInstance
     *  \brief Gets the underlying global handler.
     *
     *  \return The global handler
     */
    HandlerT& getGlobalInstance()
    {
        return GlobalInstance::get();
    }

    /*
     *  \func getGlobalInstance
     *  \brief Gets the underlying global handler.
     *
     *  \return The global handler
     */
    const HandlerT& getGlobalInstance() const
    {
        return GlobalInstance::get();
    }
};
}
}

#endif
