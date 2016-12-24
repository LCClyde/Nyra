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
#include <nyra/graphics/ogre/RenderTarget.h>
#include <nyra/win/ogre/Window.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
class TestOgreRenderTarget :
        public test::RenderTarget<RenderTarget, win::ogre::Window>
{
};

TEST_F(TestOgreRenderTarget, Render)
{
    EXPECT_EQ(expectedRender, render());
    EXPECT_EQ(expectedRender, renderOffscreen());
    EXPECT_EQ(expectedResizeRender, resize());
}

TEST_F(TestOgreRenderTarget, Stdout)
{
    EXPECT_EQ(stdout(), expectedStdout);
}

/*TEST(OgreRenderTarget, RealTimeRender)
{
    win::ogre::Window window("temp",
                             math::Vector2U(200, 200),
                             math::Vector2I(300, 300));
    RenderTarget target(window);

    while (window.isOpen())
    {
        window.update();
        target.clear(img::Color(255, 0, 0));
        target.flush();
    }
    core::writeArchive(target.getPixels(), "test.png");
}*/
}
}
}

NYRA_TEST()