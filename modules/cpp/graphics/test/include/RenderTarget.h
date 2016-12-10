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
#ifndef __NYRA_TEST_GRAPHICS_H__
#define __NYRA_TEST_GRAPHICS_H__

#include <nyra/test/Test.h>
#include <nyra/graphics/RenderTarget.h>
#include <nyra/time/System.h>

namespace nyra
{
namespace test
{
/*
 *  \class RenderTarget
 *  \brief Class used to test common functionality across all Render Targets.
 *
 *  \tparam RenderT The render target to test
 *  \tparam WindowT The window to render to.
 */
template <typename RenderT, typename WindowT>
class RenderTarget : public ::testing::Test
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default render target based on some selected testable
     *         values.
     */
    RenderTarget() :
        defaultSize(320, 240),
        resizeSize(800, 600),
        renderColor(0x56, 0x78, 0x9A),
        resizeColor(0x12, 0x34, 0x56),
        expectedStdout("Render Target: x=320 y=240"),
        mWindow("Render Target Test",
                defaultSize,
                math::Vector2I(0, 0)),
        mRenderTarget(mWindow),
        mOffscreen(defaultSize),
        expectedRender(defaultSize),
        expectedResizeRender(resizeSize)
    {
        update();
        for (size_t ii = 0; ii < defaultSize.product(); ++ii)
        {
            expectedRender(ii) = renderColor;
        }
        for (size_t ii = 0; ii < resizeSize.product(); ++ii)
        {
            expectedResizeRender(ii) = resizeColor;
        }
    }

    /*
     *  \func render
     *  \brief Tests the basic render functionality
     *
     *  \return The rendered pixels..
     */
    img::Image render()
    {
        mRenderTarget.clear(renderColor);
        mRenderTarget.flush();
        update();
        return mRenderTarget.getPixels();
    }

    /*
     *  \func renderOffscreen
     *  \brief Tests the basic render functionality
     *
     *  \return The rendered pixels..
     */
    img::Image renderOffscreen()
    {
        mOffscreen.clear(renderColor);
        mOffscreen.flush();
        return mOffscreen.getPixels();
    }

    /*
     *  \func resize
     *  \brief Tests resize and rendering
     *
     *  \return The rendered pixels.
     */
    img::Image resize()
    {
        mRenderTarget.resize(resizeSize);
        mRenderTarget.clear(resizeColor);
        mRenderTarget.flush();
        update();
        const img::Image pixels = mRenderTarget.getPixels();
        return pixels;
    }

    /*
     *  \func stdout
     *  \brief Gets the standard out for a render target
     *
     *  \return The output that would be written to screen
     */
    std::string stdout()
    {
        mRenderTarget.resize(defaultSize);
        return test::stdout(mRenderTarget);
    }

    const math::Vector2U defaultSize;
    const math::Vector2U resizeSize;
    const img::Color renderColor;
    const img::Color resizeColor;
    const std::string expectedStdout;
    WindowT mWindow;
    RenderT mRenderTarget;
    RenderT mOffscreen;
    img::Image expectedRender;
    img::Image expectedResizeRender;

private:
    void update()
    {
        // Give the window some time to animate in case the operating system
        // has it enabled
        for (size_t ii = 0; ii < 5; ++ii)
        {
            time::sleep(5);
            mWindow.update();
        }
    }
};
}
}

#endif
