/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/test/Image.h>
#include <nyra/img/Draw.h>
#include <nyra/core/Path.h>
#include <nyra/math/Conversions.h>

namespace nyra
{
namespace img
{
//===========================================================================//
Image getInput()
{
    return core::read<Image>(core::path::join(
            core::DATA_PATH, "textures/lenna.png"));
}

//===========================================================================//
TEST(Draw, Text)
{
    {
        Image image = getInput();
        Font font;
        font.name = "Comic Sans MS";
        font.size = 36;
        font.color = Color(0, 255, 255);
        draw::text("Hello World!",
                   math::Vector2U(256, 256),
                   font, image);
        EXPECT_TRUE(test::compareImage(image, "test_draw_text_simple.png"));
    }

    {
        Image image = getInput();
        const std::string text =
            "We the People of the United States, in Order to form a more "
            "perfect Union, establish Justice, insure domestic Tranquility, "
            "provide for the common defence, promote the general Welfare, "
            "and secure the Blessings of Liberty to ourselves and our "
            "Posterity, do ordain and establish this Constitution for the "
            "United States of America.";
        Font font;
        font.size = 30;
        font.color = Color(255, 255, 255);
        font.maxWidth = 500;
        draw::text(text,
                   math::Vector2U(10, 10),
                   font, image);
        EXPECT_TRUE(test::compareImage(image, "test_draw_text_wrapped.png"));
    }

    // TODO: There are lots of other font options to test
    //       ie, bold, italic, offsets, etc.
}
}
}

NYRA_TEST()
