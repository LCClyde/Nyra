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
#ifndef __NYRA_CORE_TEST_ARCHIVE_H__
#define __NYRA_CORE_TEST_ARCHIVE_H__

#include <string>
#include <fstream>
#include <cstdio>
#include <nyra/core/Archive.h>

namespace nyra
{
namespace test
{
/*
 *  \func testArchive
 *  \brief Tests running a round trip on an object.
 *
 *  \tparam T The data to test. The object must default construct and allow
 *          return by value.
 *  \param input A filled out specialized input.
 *  \param output The pathname to save the archive to.
 *  \return The round trip object.
 */
template <typename T>
T archive(const T& input, const std::string& tempPathname = "temp")
{
    core::writeArchive<T>(input, tempPathname);
    T output = core::readArchive<T>(tempPathname);
    std::remove(tempPathname.c_str());
    return output;
}
}
}

#endif
