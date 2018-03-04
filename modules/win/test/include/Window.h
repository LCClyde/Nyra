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
#ifndef __NYRA_WIN_TEST_WINDOW_H__
#define __NYRA_WIN_TEST_WINDOW_H__

#include <nyra/math/Vector2.h>
#include <nyra/core/Time.h>
#include <nyra/test/Archive.h>
#include <nyra/test/Stdout.h>

namespace nyra
{
namespace test
{
/*
 *  \class TestWindow
 *  \func Class used for testing common Window interface functionality
 *
 *  \tparam T The window type to test
 */
template <typename T>
class Window : public ::testing::Test
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the TestWindow and the default and expected values
     */
    Window() :
        ::testing::Test(),
        defaultName("Default Name"),
        defaultSize(320, 240),
        defaultPosition(200, 100),
        previousID(0),
        expectedName("Expected Name"),
        expectedSize(800, 600),
        expectedPosition(512, 256),
        expectedStdoutOpen(
            "Name: Default Name\nSize: x=320 y=240\nPosition: x=200 y=100"),
        expectedStdoutClosed("Window is closed")
    {
    }

    /*
     *  \func SetUp
     *  \brief Called before each test. This should not be called manually.
     */
    void SetUp() override
    {
        reset();
    }

    /*
     *  \func reset
     *  \brief Resets the window to its original state. Meaning that it is open
     *         and set to all default* values.
     */
    void reset()
    {
        if (mWindow.isOpen())
        {
            mWindow.setName(defaultName);
            mWindow.setPosition(defaultPosition);
            mWindow.setSize(defaultSize);
        }
        else
        {
            mWindow.load(defaultName,
                         defaultSize,
                         defaultPosition);
        }
        update();
    }

    /*
     *  \func testName
     *  \brief Used to test changing the name of the Window. This calls
     *         set name and then get name.
     *         USE: EXPECT_EQ(testName(), expectedName);
     *
     *  \return The updated name of the window.
     */
    std::string name()
    {
        mWindow.setName(expectedName);

        // Just one update here should be enough
        mWindow.update();
        return mWindow.getName();
    }

    /*
     *  \func testSize
     *  \brief Used to test changing the size of the Window. This calls
     *         set size and then get size.
     *         USE: EXPECT_EQ(testSize(), expectedSize);
     *
     *  \return The updated size of the window.
     */
    math::Vector2U size()
    {
        mWindow.setSize(expectedSize);
        update();
        return mWindow.getSize();
    }

    /*
     *  \func testPosition
     *  \brief Used to test changing the position of the Window. This calls
     *         set position and then get position.
     *         USE: EXPECT_EQ(testPosition(), expectedPosition);
     *
     *  \return The updated name of the window.
     */
    math::Vector2I position()
    {
        mWindow.setPosition(expectedPosition);
        update();
        return mWindow.getPosition();
    }

    /*
     *  \func testClose
     *  \brief Tests if a Window can be closed. This only looks at the
     *         underlying variables.
     *         TODO: Take the window visibility into account.
     *         USE: EXPECT_TRUE(testClose());
     *
     *  \return True if the window was closed
     */
    bool close()
    {
        mWindow.close();
        const bool results = !(mWindow.isOpen());
        reset();
        return results;
    }

    /*
     *  \func testID
     *  \brief Used to tests if the window ID changes when the window is closed
     *         and reopened.
     *         USE: EXPECT_NE(testID(), previousID);
     *
     *  \param extraWait An extra wait after the window closes. Some window
     *         systems do not do a good job of rapid open/close.
     */
    size_t id(size_t extraWait = 0)
    {
        previousID = mWindow.getID();
        update();
        if (extraWait > 0)
        {
            core::sleep(extraWait);
        }
        mWindow.close();
        if (extraWait > 0)
        {
            core::sleep(extraWait);
        }
        reset();
        return mWindow.getID();
    }

    /*
     *  \func testArchiveOpen
     *  \brief Test archiving an open window.
     *         USE: T window = testArchiveOpen()
     *              EXPECT_EQ(window.getName(), expectedName);
     *              EXPECT_EQ(window.getSize(), expectedSize);
     *              EXPECT_EQ(window.getPosition(), expectedPosition);
     */
    T archiveOpen()
    {
        mWindow.setName(expectedName);
        mWindow.setSize(expectedSize);
        mWindow.setPosition(expectedPosition);
        update();
        return archive(mWindow);
    }

    /*
     *  \func testArchiveClosed
     *  \brief Test archiving a closed window.
     *         USE: EXPECT_FALSE(testArchiveClosed().isOpen());
     */
    T archiveClosed()
    {
        mWindow.close();
        T window = archive(mWindow);
        reset();
        return window;
    }

    /*
     *  \func testStdoutOpen
     *  \brief Test that the correct string is sent to stdout
     *         USE: EXPECT_EQ(testStdoutOpen(), expectedStdoutOpen);
     *
     */
    std::string stdoutOpen()
    {
        // Make sure the window is set to defaults
        reset();
        return stdout(mWindow);
    }

    /*
     *  \func testStdoutClosed
     *  \brief Test that the correct string is sent to stdout when the window
     *         is closed
     *         USE: EXPECT_EQ(testStdoutClosed(), expectedStdoutClosed)
     *
     */
    std::string stdoutClosed()
    {
        mWindow.close();
        const std::string results = stdout(mWindow);
        reset();
        return results;
    }

    /*
     *  \var defaultName
     *  \brief The name of the window whenever it is reset.
     */
    const std::string defaultName;

    /*
     *  \var defaultSize
     *  \brief The size of the window whenever it is reset.
     */
    const math::Vector2U defaultSize;

    /*
     *  \var defaultPosition
     *  \brief The position of the window whenever it is reset.
     */
    const math::Vector2I defaultPosition;

    /*
     *  \var previousID
     *  \brief The ID of the window before it was closed. This is only set
     *         in the testID function. It is undefined anywhere else.
     */
    size_t previousID;

    /*
     *  \var expectedName
     *  \brief The expected name after a call to testName. It is undefined
     *         anywhere else.
     */
    const std::string expectedName;

    /*
     *  \var expectedSize
     *  \brief The expected name after a call to testSize. It is undefined
     *         anywhere else.
     */
    const math::Vector2U expectedSize;

    /*
     *  \var expectedPosition
     *  \brief The expected name after a call to testPosition. It is undefined
     *         anywhere else.
     */
    const math::Vector2I expectedPosition;

    /*
     *  \var expectedStdoutOpen
     *  \brief The expected string to be sent to stdout when the window is
     *         set to its default values.
     */
    const std::string expectedStdoutOpen;

    /*
     *  \var expectedStdoutClosed
     *  \brief The expected string to be sent to stdout when the window is
     *         closed.
     */
    const std::string expectedStdoutClosed;

private:
    void update()
    {
        // Give the window some time to animate in case the operating system
        // has it enabled
        for (size_t ii = 0; ii < 10; ++ii)
        {
            core::sleep(10);
            mWindow.update();
        }
    }

    T mWindow;
};
}
}

#endif

