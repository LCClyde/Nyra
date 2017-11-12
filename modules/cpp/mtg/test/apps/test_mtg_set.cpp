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
#include <nyra/mtg/Set.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

//===========================================================================//
nyra::mtg::Set getBeta()
{
    return nyra::mtg::Set(nyra::core::path::join(
            nyra::core::DATA_PATH, "docs/beta.json"));
}

namespace nyra
{
namespace mtg
{
//===========================================================================//
TEST(Set, FromJSON)
{
    Set set(getBeta());
    EXPECT_EQ(static_cast<size_t>(302), set.getAllCards().size());
}

//===========================================================================//
TEST(Card, Archive)
{
    Set set(getBeta());
    Set archived = test::archive(set);
    EXPECT_EQ(set.getAllCards(), archived.getAllCards());
}

//===========================================================================//
TEST(Set, Merge)
{
    Set a(getBeta());
    Set b(getBeta());
    a.addSet(b);
    EXPECT_EQ(static_cast<size_t>(604), a.getAllCards().size());
}

//===========================================================================//
TEST(Set, Filter)
{
    Set beta(getBeta());
    Set redBlue(beta.filterEDHColor({RED, BLUE}));
    EXPECT_EQ(static_cast<size_t>(142), redBlue.getAllCards().size());

    Set colorless(beta.filterEDHColor(COLORLESS));
    EXPECT_EQ(static_cast<size_t>(41), colorless.getAllCards().size());

    Set rare(beta.filterRarity(RARE));
    EXPECT_EQ(static_cast<size_t>(117), rare.getAllCards().size());

    Set commonUncommon(beta.filterRarity({COMMON, UNCOMMON}));
    EXPECT_EQ(static_cast<size_t>(170), commonUncommon.getAllCards().size());
}

//===========================================================================//
TEST(Set, Stdout)
{
    Set set(getBeta());
    const std::string results = test::stdout(set);
    EXPECT_EQ(static_cast<size_t>(302), core::str::split(results, "\n").size());
}
}
}

NYRA_TEST()
