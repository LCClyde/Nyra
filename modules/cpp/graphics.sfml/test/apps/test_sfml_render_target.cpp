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
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/win/sfml/Window.h>

namespace nyra
{
namespace graphics
{
namespace sfml
{
class TestSFMLRenderTarget :
        public test::RenderTarget<RenderTarget, win::sfml::Window>
{
};

TEST_F(TestSFMLRenderTarget, Render)
{
    img::Image renderWindow(defaultSize);
    for (size_t ii = 0; ii < defaultSize.product(); ++ii)
    {
        renderWindow(ii) = renderColor;
    }
    EXPECT_EQ(renderWindow, render());

    renderWindow.resize(resizeSize);
    for (size_t ii = 0; ii < resizeSize.product(); ++ii)
    {
        renderWindow(ii) = resizeColor;
    }
    EXPECT_EQ(renderWindow, resize());
}

TEST_F(TestSFMLRenderTarget, Stdout)
{
    EXPECT_EQ(stdout(), expectedStdout);
}
}
}
}

NYRA_TEST()
