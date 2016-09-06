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
#ifndef __NYRA_TEST_GRAPHICS_H__
#define __NYRA_TEST_GRAPHICS_H__

#include <nyra/test/Test.h>
#include <nyra/graphics/RenderTarget.h>

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
        mWindow("Render Target Test",
                defaultSize,
                math::Vector2I(0, 0)),
        mRenderTarget(mWindow.getID())
    {
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
        return mRenderTarget.getPixels();
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
        const img::Image pixels = mRenderTarget.getPixels();
        mRenderTarget.resize(defaultSize);
        return pixels;
    }

    const math::Vector2U defaultSize;
    const math::Vector2U resizeSize;
    const img::Color renderColor;
    const img::Color resizeColor;
    WindowT mWindow;
    RenderT mRenderTarget;
};
}
}

#endif
