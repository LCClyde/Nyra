/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <nyra/test/Test.h>
#include <nyra/process/Hijack.h>
#include <nyra/core/Time.h>
#include <nyra/win/native/Window.h>

namespace nyra
{
namespace process
{
TEST(Hijack, Find)
{
    const std::string windowName = "Hijack Window Test";
    win::native::Window target(windowName);

    for (size_t ii = 0; ii < 10; ++ii)
    {
        core::sleep(10);
        target.update();
    }


    std::shared_ptr<win::Window> found = hijack(windowName);
    found->setSize(math::Vector2U(500, 500));

    for (size_t ii = 0; ii < 10; ++ii)
    {
        core::sleep(10);
        target.update();
    }

    EXPECT_EQ(math::Vector2U(500, 500), found->getSize());
    EXPECT_EQ(target.getName(), found->getName());
    EXPECT_EQ(target.getPosition(), found->getPosition());
    EXPECT_EQ(target.getSize(), found->getSize());
    EXPECT_EQ(target.getID(), found->getID());
    EXPECT_EQ(target.getNative(), found->getNative());
}
}
}

NYRA_TEST()
