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
#include <nyra/test/RenderTarget.h>
#include <nyra/graphics/gl/RenderTarget.h>
#include <nyra/win/gl/Window.h>

namespace nyra
{
namespace graphics
{
namespace gl
{
class TestOpenGLRenderTarget :
        public test::RenderTarget<RenderTarget, win::gl::Window>
{
};

TEST_F(TestOpenGLRenderTarget, Render)
{
    EXPECT_EQ(expectedRender, render());
    // TODO: Only render to screen works at the moment
    //EXPECT_EQ(expectedRender, renderOffscreen());
    //EXPECT_EQ(expectedResizeRender, resize());
}

TEST_F(TestOpenGLRenderTarget, Stdout)
{
    EXPECT_EQ(stdout(), expectedStdout);
}
}
}
}

NYRA_TEST()
