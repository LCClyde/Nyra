/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <nyra/media/GameListLayout.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(GameListLayout, Defaults)
{
    GameListLayout layout;

    // I don't want to force defaults. Let's just make sure they are set
    // and set to something greater than 0.
    EXPECT_GT(layout.boxSize, 0.0);
    EXPECT_EQ(GameListLayout::HORIZONTAL, layout.boxLayout);
    EXPECT_GT(layout.boxPosition, 0.0);
    EXPECT_GT(layout.boxSpacing, 0.0);
}

//===========================================================================//
TEST(GameListLayout, Archive)
{
    GameListLayout layout;
    layout.boxSize = 100.0;
    layout.boxLayout = GameListLayout::HORIZONTAL;
    layout.boxPosition = 250.0;
    layout.boxSpacing = 10.0;

    GameListLayout archived = test::archive(layout);
    EXPECT_EQ(layout.boxSize, archived.boxSize);
    EXPECT_EQ(layout.boxLayout, archived.boxLayout);
    EXPECT_EQ(layout.boxPosition, archived.boxPosition);
    EXPECT_EQ(layout.boxSpacing, archived.boxSpacing);

}

//===========================================================================//
TEST(GameListLayout, Stdout)
{
    GameListLayout layout;
    layout.boxSize = 100.0;
    layout.boxLayout = GameListLayout::HORIZONTAL;
    layout.boxPosition = 250.0;
    layout.boxSpacing = 10.0;

    const std::string expected =
            "Box Size:      100\n"
            "Box Layout:    HORIZONTAL\n"
            "Box Position:  250\n"
            "Box Spacing:   10";

    EXPECT_EQ(test::stdout(layout), expected);
}
}
}

NYRA_TEST()
