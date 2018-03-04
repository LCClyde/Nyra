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
#include <nyra/test/Test.h>
#include <nyra/mem/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace
{
class MockGlobalHandler : public nyra::mem::GlobalHandler
{
public:
    MockGlobalHandler() :
        initCalled(0),
        shutdownCalled(0)
    {
    }

    size_t initCalled;
    size_t shutdownCalled;

protected:
    void initializeGlobal()
    {
        ++initCalled;
    }

    void shutdownGlobal()
    {
        ++shutdownCalled;
    }
};

class MockGlobalDependency :
    public nyra::mem::GlobalDependency<MockGlobalHandler>
{
public:
    MockGlobalHandler& get()
    {
        return getGlobalInstance();
    }
};


typedef nyra::mem::Singleton<MockGlobalHandler> GlobalInstance;

}

namespace nyra
{
namespace mem
{
TEST(GlobalHandler, InitShutdown)
{
    EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(0));
    EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(0));

    {
        MockGlobalDependency dep1;
        EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(1));
        EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(0));

        MockGlobalDependency dep2;
        EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(1));
        EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(0));
    }

    EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(1));
    EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(1));

    {
        MockGlobalDependency dep1;
        EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(2));
        EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(1));
    }

    EXPECT_EQ(GlobalInstance::get().initCalled, static_cast<size_t>(2));
    EXPECT_EQ(GlobalInstance::get().shutdownCalled, static_cast<size_t>(2));
}
}
}

NYRA_TEST()
