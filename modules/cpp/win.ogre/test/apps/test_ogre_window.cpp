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
#include <nyra/win/ogre/Window.h>
#include <nyra/test/Test.h>
#include <nyra/test/Window.h>

namespace nyra
{
namespace win
{
namespace ogre
{
class TestOgreWindow : public test::Window<Window>
{
};

TEST_F(TestOgreWindow, GetSet)
{
    // TODO: Temp comment: Does not crash
    EXPECT_EQ(name(), defaultName);
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre does not allow changing the window title\n";
    std::cout << "======================================================\n";
    EXPECT_EQ(size(), expectedSize);
    EXPECT_NE(position(), expectedPosition);
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre get window position is incorrect\n";
    std::cout << "======================================================\n";
    time::sleep(1000);
}

TEST_F(TestOgreWindow, Id)
{
#ifdef NYRA_WIN32
    EXPECT_NE(id(), previousID);
#else
    EXPECT_EQ(id(), previousID);
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre winId is always 0 on Linux\n";
    std::cout << "======================================================\n";
#endif
    time::sleep(1000);
}

TEST_F(TestOgreWindow, Close)
{
    // TODO: Opening and closing windows inside a single test can sometimes
    //       cause Ogre to throw. This happens maybe 1 out of 4 times.
    //       Add this test back in to test closing, but note that you may
    //       need to ignore some failures.
    EXPECT_TRUE(close());
    time::sleep(1000);
}

TEST_F(TestOgreWindow, ArchiveOpen)
{
    ogre::Window window = archiveOpen();
    EXPECT_EQ(window.getName(), defaultName);
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre does not allow changing the window title\n";
    std::cout << "======================================================\n";
    EXPECT_EQ(window.getSize(), expectedSize);
    EXPECT_NE(window.getPosition(), expectedPosition);
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre get window position is incorrect\n";
    std::cout << "======================================================\n";
    time::sleep(1000);
}

TEST_F(TestOgreWindow, ArchiveClosed)
{
    EXPECT_FALSE(archiveClosed().isOpen());
    time::sleep(1000);
}

TEST_F(TestOgreWindow, Stdout)
{
    EXPECT_EQ(stdoutOpen().substr(0, 37), expectedStdoutOpen.substr(0, 37));
    std::cout << "======================================================\n";
    std::cout << "WARNING: Ogre get window position is incorrect\n";
    std::cout << "======================================================\n";
    EXPECT_NE(stdoutOpen(), expectedStdoutOpen);
    EXPECT_EQ(stdoutClosed(), expectedStdoutClosed);
    time::sleep(1000);
}
}
}
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
