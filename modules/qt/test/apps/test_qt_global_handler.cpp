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
#include <nyra/test/Stdout.h>
#include <nyra/qt/GlobalHandler.h>

namespace nyra
{
namespace qt
{
TEST(GlobalHandler, Application)
{
    GlobalHandler app;
    EXPECT_EQ(app.get(), nullptr);
    app.initialize();
    EXPECT_NE(app.get(), nullptr);
    app.shutdown();
    EXPECT_EQ(app.get(), nullptr);
    app.initialize();
    EXPECT_NE(app.get(), nullptr);
    app.initialize();
    EXPECT_NE(app.get(), nullptr);
    app.shutdown();
    EXPECT_NE(app.get(), nullptr);
    app.shutdown();
    EXPECT_EQ(app.get(), nullptr);
}

TEST(GlobalHandler, Stdout)
{
    GlobalHandler app;
    EXPECT_EQ(test::stdout(app), "Application state: stopped");
    app.initialize();
    EXPECT_EQ(test::stdout(app), "Application state: running");
    app.shutdown();
    EXPECT_EQ(test::stdout(app), "Application state: stopped");
}
}
}

NYRA_TEST()
