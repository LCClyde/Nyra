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
#include <nyra/test/Required.h>

namespace
{
class TestWindow : public nyra::win::Window
{
public:
    TestWindow()
    {
        close();
    }

    TestWindow(const std::string& name,
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
        mHandle = 1;
    }

    void update()
    {
    }

    void close() override
    {
        mOpen = false;
        mHandle = 0;
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

TEST(Window, Archive)
{
    TestWindow input("Test",
                     nyra::math::Vector2U(1280, 720),
                     nyra::math::Vector2I(512, 256));
    TestWindow output = nyra::test::testArchive(input);
    EXPECT_EQ(input.getName(), output.getName());
    EXPECT_EQ(input.getSize(), output.getSize());
    EXPECT_EQ(input.getPosition(), output.getPosition());
}

TEST(Required, Stdout)
{
    TestWindow input("Test",
                     nyra::math::Vector2U(1280, 720),
                     nyra::math::Vector2I(512, 256));
    const std::string out = nyra::test::testStdout(input);
    EXPECT_EQ(out, "Name: Test\nSize: x=1280 y=720\nPosition: x=512 y=256");
}

NYRA_TEST()
