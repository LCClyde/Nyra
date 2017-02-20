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
#include <nyra/net/Browser.h>
#include <nyra/core/Path.h>
#include <nyra/core/File.h>
#include <nyra/core/String.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace net
{
//===========================================================================//
TEST(Browser, Get)
{
    Browser browser;
    const std::string results = browser.get(
            "file://" + core::DATA_PATH + "/docs/hello_world.txt");
    EXPECT_EQ("Hello World!", results);
}

//===========================================================================//
TEST(Browser, Cache)
{
    const std::string cacheDir = core::path::join(
            core::INSTALL_PATH, "browser_cache_test");

    if (core::path::exists(cacheDir))
    {
        throw std::runtime_error(
                "Cannot test browser caching, " +
                cacheDir + " already exists");
    }

    Browser browser(10, cacheDir, 0);
    const std::string results = browser.get(
            "file://" + core::DATA_PATH + "/docs/hello_world.txt");

    // Now there should be a cached file
    // TODO: This goes into too much implementation details.
    const std::string expectedCache = core::path::join(
            cacheDir, core::DATA_PATH.substr(1, std::string::npos) +
                    "/docs/hello_world.txt");
    const std::string expectedTimestamp = expectedCache + ".timestamp";

    EXPECT_TRUE(core::path::exists(expectedCache));
    EXPECT_TRUE(core::path::exists(expectedTimestamp));

    EXPECT_EQ("Hello World!", core::readFile(expectedCache));
    EXPECT_LT(core::epoch(), core::str::toType<size_t>(
            core::readFile(expectedTimestamp)));

    core::path::removeAll(cacheDir);

}
}
}

NYRA_TEST()
