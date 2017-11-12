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

namespace nyra
{
namespace mtg
{
//===========================================================================//
TEST(Set, FromJSON)
{
    Set set(core::path::join(core::DATA_PATH, "docs/beta.json"));
    EXPECT_EQ(static_cast<size_t>(302), set.getAllCards().size());
}

//===========================================================================//
TEST(Card, Archive)
{
    Set set(core::path::join(core::DATA_PATH, "docs/beta.json"));
    Set archived = test::archive(set);
    EXPECT_EQ(set.getAllCards(), archived.getAllCards());
}


//===========================================================================//
TEST(Set, Stdout)
{
    Set set(core::path::join(core::DATA_PATH, "docs/beta.json"));
    const std::string results = test::stdout(set);
    EXPECT_EQ(static_cast<size_t>(302), core::str::split(results, "\n").size());
}
}
}

NYRA_TEST()
