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
#include <ostream>

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
 *         NOTE: This class does not have the ability to archive as it should
 *         instead recreate itself as its dependencies are built back up
 *         during a deserialize.
 */
class GlobalHandler
{
public:
    GlobalHandler();

    /*
     *  \func Destructor
     *  \brief Required for proper inheritance.
     */
    virtual ~GlobalHandler() = default;

    /*
     *  \func initialize
     *  \brief Objects accessing this global object for the first time
     *         should call this to add themselves as dependent objects.
     */
    void initialize();

    /*
     *  \func shutdown
     *  \brief Objects destroying their dependent parts of the global
     *         object should call this to remove themselves as dependencies.
     *         When the last object is removed the global object will
     *         receive its shutdown command.
     *
     *  \throw std::runtime_error If this is called when the number of known
     *         handlers is zero.
     */
    void shutdown();

    /*
     *  \func isInitialized
     *  \brief Checks if the global handler has been initialized.
     *
     *  \return True if the handler is initialized
     */
    bool isInitialized() const
    {
        return mHandles > 0;
    }

protected:
    /*
     *  \func initializeGlobal
     *  \brief This should call all the global 3rd party initialization code.
     */
    virtual void initializeGlobal() = 0;

    /*
     *  \func shutdownGlobal
     *  \brief This should call the shutdown commands for the global 3rd
     *         party objects.
     */
    virtual void shutdownGlobal() = 0;

private:
    // There is nothing meaningful here. It would be recommended to override
    // this functionality in super classes.
    friend std::ostream& operator<<(std::ostream& os,
                                    const GlobalHandler& handler);

    size_t mHandles;
};
}
}

#endif
