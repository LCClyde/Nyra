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
#include <nyra/input/Buttons.h>

namespace
{
class MockButtons : public nyra::input::Buttons<5>
{
public:
    void update(const std::bitset<5>& buttons)
    {
        updateButtons(buttons);
    }
};
}

namespace nyra
{
namespace input
{
TEST(Buttons, Values)
{
    MockButtons buttons;
    std::bitset<5> values;

    // Everything should start unset
    for (size_t ii = 0; ii < 5; ++ii)
    {
         EXPECT_FALSE(buttons.getButtonPressed(ii));
         EXPECT_FALSE(buttons.getButtonDown(ii));
         EXPECT_FALSE(buttons.getButtonReleased(ii));
    }

    values[2] = true;
    values[4] = true;
    buttons.update(values);

    // All released should be false
    for (size_t ii = 0; ii < 5; ++ii)
    {
         EXPECT_FALSE(buttons.getButtonReleased(ii));
    }

    // Button 2 and 4 should be pressed
    EXPECT_FALSE(buttons.getButtonPressed(0));
    EXPECT_FALSE(buttons.getButtonPressed(1));
    EXPECT_TRUE(buttons.getButtonPressed(2));
    EXPECT_FALSE(buttons.getButtonPressed(3));
    EXPECT_TRUE(buttons.getButtonPressed(4));

    // Button 2 and 4 should be down
    EXPECT_FALSE(buttons.getButtonDown(0));
    EXPECT_FALSE(buttons.getButtonDown(1));
    EXPECT_TRUE(buttons.getButtonDown(2));
    EXPECT_FALSE(buttons.getButtonDown(3));
    EXPECT_TRUE(buttons.getButtonDown(4));

    buttons.update(values);

    // All released and pressed should be false
    for (size_t ii = 0; ii < 5; ++ii)
    {
         EXPECT_FALSE(buttons.getButtonPressed(ii));
         EXPECT_FALSE(buttons.getButtonReleased(ii));
    }

    // Button 2 and 4 should be down
    EXPECT_FALSE(buttons.getButtonDown(0));
    EXPECT_FALSE(buttons.getButtonDown(1));
    EXPECT_TRUE(buttons.getButtonDown(2));
    EXPECT_FALSE(buttons.getButtonDown(3));
    EXPECT_TRUE(buttons.getButtonDown(4));

    values[2] = false;
    values[4] = false;
    buttons.update(values);

    // All down and pressed should be false
    for (size_t ii = 0; ii < 5; ++ii)
    {
         EXPECT_FALSE(buttons.getButtonPressed(ii));
         EXPECT_FALSE(buttons.getButtonDown(ii));
    }

    // Button 2 and 4 should be released
    EXPECT_FALSE(buttons.getButtonReleased(0));
    EXPECT_FALSE(buttons.getButtonReleased(1));
    EXPECT_TRUE(buttons.getButtonReleased(2));
    EXPECT_FALSE(buttons.getButtonReleased(3));
    EXPECT_TRUE(buttons.getButtonReleased(4));

    buttons.update(values);

    // All released should be false
    for (size_t ii = 0; ii < 5; ++ii)
    {
         EXPECT_FALSE(buttons.getButtonReleased(ii));
    }
}
}
}

NYRA_TEST()
