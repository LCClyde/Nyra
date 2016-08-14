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
#ifndef __NYRA_PATTERN_GLOBAL_HANDLER_H__
#define __NYRA_PATTERN_GLOBAL_HANDLER_H__

#include <unordered_set>

namespace nyra
{
namespace pattern
{
/*
 *  \class GlobalHandler
 *  \brief An interface class used to simplify controlling the a 3rd party
 *         library with global init and shutdown calls. The common interface
 *         should not be required to call these. They should be hidden from
 *         user.
 */
class GlobalHandler
{
public:
    /*
     *  \func Destructor
     *  \brief Required for proper inheritance.
     */
    virtual ~GlobalHandler() = default;

    /*
     *  \func initialize
     *  \brief Objects accessing this global object for the first time
     *         should call this to add themselves as dependent objects.
     *
     *  \param handle The pointer representing the object.
     *  \throw std::runtime_error If a nullptr is passed in.
     */
    void initialize(const void* handle);

    /*
     *  \func shutdown
     *  \brief Objects destroying their dependent parts of the global
     *         object should call this to remove themselves as dependencies.
     *         When the last object is removed the global object will
     *         receive its shutdown command.
     *
     *  \param handle The pointer representing the object. This should match
     *         the same handle that was used during initialize.
     *  \throw std::runtime_error If a nullptr is passed in.
     *  \throw std::runtime_error If an unknown pointer is passed.
     */
    void shutdown(const void* handle);

protected:
    /*
     *  \func initializeGlobal
     *  \brief This should call all the global 3rd party initialization code.
     */
    virtual void intializeGlobal() = 0;

    /*
     *  \func shutdownGlobal
     *  \brief This should call the shutdown commands for the global 3rd
     *         party objects.
     */
    virtual void shutdownGlobal() = 0;

private:
    std::unordered_set<const void*> mHandles;
};
}
}

#endif
