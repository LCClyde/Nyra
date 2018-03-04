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
#include <nyra/test/Stdout.h>

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
}

namespace nyra
{
namespace mem
{
TEST(GlobalHandler, InitShutdown)
{
    MockGlobalHandler global;
    EXPECT_EQ(global.initCalled, static_cast<size_t>(0));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(0));
    EXPECT_FALSE(global.isInitialized());

    global.initialize();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(1));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(0));
    EXPECT_TRUE(global.isInitialized());

    global.initialize();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(1));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(0));
    EXPECT_TRUE(global.isInitialized());

    global.shutdown();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(1));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(0));
    EXPECT_TRUE(global.isInitialized());

    global.shutdown();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(1));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(1));
    EXPECT_FALSE(global.isInitialized());

    global.initialize();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(2));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(1));
    EXPECT_TRUE(global.isInitialized());

    global.shutdown();
    EXPECT_EQ(global.initCalled, static_cast<size_t>(2));
    EXPECT_EQ(global.shutdownCalled, static_cast<size_t>(2));
    EXPECT_FALSE(global.isInitialized());
}

TEST(GlobalHandler, Throw)
{
    MockGlobalHandler global;
    EXPECT_THROW(global.shutdown(), std::runtime_error);
}

TEST(GlobalHandler, Stdout)
{
    MockGlobalHandler global;
    EXPECT_EQ(test::stdout(global), "Abstract Global Handler");
}
}
}

NYRA_TEST()
