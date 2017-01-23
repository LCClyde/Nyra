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
#include <nyra/img/Vector.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace img
{
TEST(Vector, Empty)
{
    Vector svg(math::Vector2U(128, 128));
    Image image = core::read<Image>(core::path::join(
            core::DATA_PATH, "textures/test_empty_svg.png"));
    EXPECT_EQ(image, svg.getImage());
}

TEST(Vector, Triangle)
{
    Vector svg(math::Vector2U(128, 128));
    std::vector<BlobInstruction> blob;
    blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
    blob.push_back(createBlobLine(math::Vector2F(32.0f, 32.0f)));
    blob.push_back(createBlobLine(math::Vector2F(-32.0f, 32.0f)));
    svg.draw(blob,
             math::Vector2F(64.0f, 32.0f),
             Color(0, 255, 255),
             Color(255, 0, 255));
    Image image = core::read<Image>(core::path::join(
            core::DATA_PATH, "textures/test_triangle_svg.png"));
    EXPECT_EQ(image, svg.getImage());
}

TEST(Vector, HelloWorld)
{
    Vector svg(math::Vector2U(300, 128));
    {
        std::vector<BlobInstruction> blob;
        // Add 'H"'
        blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(0.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 40.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 40.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 32.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 32.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 0.0f)));
        svg.draw(blob,
                 math::Vector2F(32.0f, 16.0f),
                 Color(0, 0, 255),
                 Color(255, 0, 0));
    }
    {
        std::vector<BlobInstruction> blob;
        // Add 'E'
        blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 8.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 8.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 24.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 24.0f)));
        blob.push_back(createBlobLine(math::Vector2F(32.0f, 32.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 32.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(0.0f, 64.0f)));
        svg.draw(blob,
                 math::Vector2F(80.0f, 16.0f),
                 Color(0, 0, 255),
                 Color(255, 0, 0));
    }
    {
        std::vector<BlobInstruction> blob;
        // Add 'L'
        blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(0.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 0.0f)));
        svg.draw(blob,
                 math::Vector2F(128.0f, 16.0f),
                 Color(0, 0, 255),
                 Color(255, 0, 0));
    }
    {
        std::vector<BlobInstruction> blob;
        // Add 'L'
        blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
        blob.push_back(createBlobLine(math::Vector2F(0.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 64.0f)));
        blob.push_back(createBlobLine(math::Vector2F(40.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 56.0f)));
        blob.push_back(createBlobLine(math::Vector2F(8.0f, 0.0f)));
        svg.draw(blob,
                 math::Vector2F(180.0f, 16.0f),
                 Color(0, 0, 255),
                 Color(255, 0, 0));
    }
    {
        std::vector<BlobInstruction> blob;
        // Add 'O'
        blob.push_back(createBlobStart(math::Vector2F(0.0f, 0.0f)));
        blob.push_back(createBlobCurve(math::Vector2F(20.0f, 32.0f),
                                       math::Vector2F(20.0f, 0.0f),
                                       math::Vector2F(20.0f, 16.0f)));

        blob.push_back(createBlobCurve(math::Vector2F(00.0f, 64.0f),
                                       math::Vector2F(20.0f, 48.0f),
                                       math::Vector2F(16.0f, 64.0f)));

        blob.push_back(createBlobCurve(math::Vector2F(-20.0f, 32.0f),
                                       math::Vector2F(-20.0f, 64.0f),
                                       math::Vector2F(-20.0f, 48.0f)));

        blob.push_back(createBlobCurve(math::Vector2F(0.0f, 0.0f),
                                       math::Vector2F(-20.0f, 16.0f),
                                       math::Vector2F(-20.0f, 0.0f)));
        svg.draw(blob,
                 math::Vector2F(256.0f, 16.0f),
                 Color(0, 0, 255),
                 Color(255, 0, 0));
    }
    Image image = core::read<Image>(core::path::join(
            core::DATA_PATH, "textures/test_hello_world_svg.png"));
    EXPECT_EQ(image, svg.getImage());
}
}
}

NYRA_TEST()
