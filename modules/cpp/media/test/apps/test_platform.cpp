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
#include <nyra/media/Platform.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(Platform, Archive)
{
    Platform platform;
    platform.name = "Nintendo Entertainment System";
    platform.keyName = "nes";
    platform.extensions = {".nes", ".unf", ".unif"};
    platform.goodTool = "GoodNES.exe";
    platform.goodMerge = "NES 3.14";
    platform.gamesDbPlatforms = {"NES", "SNES"};
    platform.commandLine = "play";
    platform.commandArgs = {"{GAME}", "--fullscreen"};

    Platform archived = test::archive(platform);
    EXPECT_EQ(platform.name, archived.name);
    EXPECT_EQ(platform.extensions, archived.extensions);
    EXPECT_EQ(platform.goodTool, archived.goodTool);
    EXPECT_EQ(platform.goodMerge, archived.goodMerge);
    EXPECT_EQ(platform.gamesDbPlatforms, archived.gamesDbPlatforms);
}

//===========================================================================//
TEST(Platform, Stdout)
{
    Platform platform;
    platform.name = "Nintendo Entertainment System";
    platform.keyName = "nes";
    platform.extensions = {".nes", ".unf", ".unif"};
    platform.goodTool = "GoodNES.exe";
    platform.goodMerge = "NES 3.14";
    platform.gamesDbPlatforms = {"NES", "SNES"};
    platform.commandLine = "play";
    platform.commandArgs = {"{GAME}", "--fullscreen"};

    const std::string expected =
            "Name:          Nintendo Entertainment System\n"
            "Key Name:      nes\n"
            "Extensions:    .nes,.unf,.unif\n"
            "GoodTool:      GoodNES.exe\n"
            "GoodMerge:     NES 3.14\n"
            "Command Line:  play\n"
            "Command Line Arguments:\n"
            "    {GAME}\n"
            "    --fullscreen\n"
            "TheGamesDb Platforms:\n"
            "    NES\n"
            "    SNES";

    EXPECT_EQ(test::stdout(platform), expected);
}
}
}

NYRA_TEST()
