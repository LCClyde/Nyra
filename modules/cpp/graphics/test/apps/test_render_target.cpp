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
#include <nyra/test/RenderTarget.h>
#include <nyra/graphics/RenderTarget.h>

namespace
{
class MockRenderTarget : public nyra::graphics::RenderTarget
{
public:
    MockRenderTarget(size_t winId) :
        nyra::graphics::RenderTarget(winId)
    {
    }

    nyra::math::Vector2U getSize() const override
    {
        return mSize;
    }

    void resize(const nyra::math::Vector2U& size) override
    {
        mSize = size;
        mPixels.resize(size);
    }

    void clear(const nyra::img::Color& color) override
    {
        for (size_t ii = 0; ii < mSize.product(); ++ii)
        {
            mPixels(ii) = color;
        }
    }

    void flush() override
    {
    }

    nyra::img::Image getPixels() const override
    {
        return mPixels;
    }

private:
    nyra::math::Vector2U mSize;
    nyra::img::Image mPixels;
};

class MockWindow
{
public:
    MockWindow(const std::string& name,
               const nyra::math::Vector2U& size,
               const nyra::math::Vector2I& position)
    {
    }

    size_t getID() const
    {
        return 0;
    }
};
}

namespace nyra
{
namespace graphics
{
class TestMockRenderTarget :
        public test::RenderTarget<MockRenderTarget, MockWindow>
{
};

TEST_F(TestMockRenderTarget, Render)
{
    // Normally this would be sized with the window information. Because
    // we don't have a real window we need to resize here.
    mRenderTarget.resize(defaultSize);

    img::Image renderWindow(defaultSize);
    for (size_t ii = 0; ii < defaultSize.product(); ++ii)
    {
        renderWindow(ii) = renderColor;
    }
    EXPECT_EQ(render(), renderWindow);

    renderWindow.resize(resizeSize);
    for (size_t ii = 0; ii < resizeSize.product(); ++ii)
    {
        renderWindow(ii) = resizeColor;
    }
    EXPECT_EQ(resize(), renderWindow);
}
}
}

NYRA_TEST()
