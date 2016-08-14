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
#include <nyra/win/Window.h>
#include <nyra/test/Test.h>
#include <nyra/test/Window.h>

namespace
{
class MockWindow : public nyra::win::Window
{
public:
    MockWindow() :
        mOpen(false),
        mHandle(1)
    {
        close();
    }

    MockWindow(const std::string& name,
               const nyra::math::Vector2U& size,
               const nyra::math::Vector2I& position)
    {
        load(name, size, position);
    }

    void load(const std::string& name,
              const nyra::math::Vector2U& size,
              const nyra::math::Vector2I& position) override
    {
        setName(name);
        setSize(size);
        setPosition(position);
        mOpen = true;
        mHandle += 1;
    }

    void update()
    {
    }

    void close() override
    {
        mOpen = false;
    }

    bool isOpen() const
    {
        return mOpen;
    }

    std::string getName() const override
    {
        return mName;
    }

    nyra::math::Vector2U getSize() const override
    {
        return mSize;
    }

    nyra::math::Vector2I getPosition() const override
    {
        return mPosition;
    }

    size_t getID() const override
    {
        return mHandle;
    }

    void setName(const std::string& name) override
    {
        mName = name;
    }

    void setSize(const nyra::math::Vector2U& size) override
    {
        mSize = size;
    }

    void setPosition(const nyra::math::Vector2I& position) override
    {
        mPosition = position;
    }

private:
    std::string mName;
    nyra::math::Vector2U mSize;
    nyra::math::Vector2I mPosition;
    bool mOpen;
    size_t mHandle;
};
}

namespace nyra
{
namespace win
{
class TestMockWindow : public test::Window<MockWindow>
{
};

TEST_F(TestMockWindow, GetSet)
{
    EXPECT_EQ(name(), expectedName);
    EXPECT_EQ(size(), expectedSize);
    EXPECT_EQ(position(), expectedPosition);
}

TEST_F(TestMockWindow, Close)
{
    EXPECT_NE(id(), previousID);
    EXPECT_TRUE(close());
}

TEST_F(TestMockWindow, Archive)
{

    MockWindow window = archiveOpen();
    EXPECT_EQ(window.getName(), expectedName);
    EXPECT_EQ(window.getSize(), expectedSize);
    EXPECT_EQ(window.getPosition(), expectedPosition);

    EXPECT_FALSE(archiveClosed().isOpen());
}

TEST_F(TestMockWindow, Stdout)
{
    EXPECT_EQ(stdoutOpen(), expectedStdoutOpen);
    EXPECT_EQ(stdoutClosed(), expectedStdoutClosed);
}
}
}

NYRA_TEST()
