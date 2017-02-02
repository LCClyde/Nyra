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
#include <nyra/graphics/ogre/Mesh.h>
#include <nyra/test/Image.h>
#include <nyra/graphics/Collada.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
TEST(RenderTarget, RenderSquare)
{
    RenderTarget target(math::Vector2U(256, 256));
    graphics::Collada collada(core::path::join(
            core::DATA_PATH, "models/teapot.dae"));
    Mesh mesh(collada.getVertices(), collada.getIndices());

    target.clear(img::Color(128, 0, 128));
    mesh.render(target);
    target.flush();

    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_collada.png"));
}
}
}
}

NYRA_TEST()
