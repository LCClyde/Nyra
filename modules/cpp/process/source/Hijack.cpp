/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <iostream>
#include <nyra/process/Hijack.h>
#include <nyra/win/native/Window.h>

namespace
{
//===========================================================================//
class FindWindow : private nyra::pattern::GlobalDependency<
        nyra::win::native::PosixGlobalHandler>
{
public:
    FindWindow(const std::string& target) :
        mTarget(target)
    {
    }

    std::shared_ptr<nyra::win::Window> find()
    {
        ::Window root = XDefaultRootWindow(getGlobalInstance().get());
        find(root);

        if (!mWindow.get())
        {
            throw std::runtime_error("Unable to find window for: " + mTarget);
        }

        return mWindow;
    }

private:
    void find(::Window window)
    {
        nyra::win::native::Window testWindow(window);
        if (!mWindow.get() && testWindow.getName() == mTarget)
        {
            mWindow.reset(new nyra::win::native::Window(window));
            return;
        }

        ::Window root;
        ::Window parent;
        ::Window* child;
        unsigned int numChildren;

        if (!mWindow.get() && XQueryTree(getGlobalInstance().get(),
                                         window,
                                         &root,
                                         &parent,
                                         &child,
                                         &numChildren) > 0)
        {
            for(size_t ii = 0; ii < numChildren; ++ii)
            {
                if (!mWindow.get())
                {
                    find(child[ii]);
                }
            }

            XFree(child);
        }
    }

    const std::string mTarget;
    std::shared_ptr<nyra::win::Window> mWindow;
};
}

namespace nyra
{
namespace process
{
//===========================================================================//
std::shared_ptr<win::Window> hijack(const std::string& windowName)
{
    FindWindow findWindow(windowName);
    return findWindow.find();
}
}
}
