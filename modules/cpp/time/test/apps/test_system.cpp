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
#include <nyra/time/System.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace time
{
TEST(System, Sleep)
{
    const size_t wait = 150;
    const size_t tick = epoch();
    sleep(wait);
    const size_t tock = epoch();
    const size_t elapsed = tock - tick;
    EXPECT_LT(elapsed, wait + 2);
    EXPECT_GT(elapsed, wait - 2);
}

TEST(System, Epoch)
{
    const size_t mills = epoch();
    // TODO: This is a really bad test
    EXPECT_NE(mills, static_cast<size_t>(0));
}
}
}

NYRA_TEST()
