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
#ifndef __NYRA_TEST_REQUIRED_H__
#define __NYRA_TEST_REQUIRED_H__

#include <string>
#include <fstream>
#include <gtest/gtest.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace nyra
{
namespace test
{
/*
 *  \func testArchive
 *  \brief Tests running a round trip on an object. The
 *
 *  \tparam T The data to test. The object must default construct and allow
 *          return by value.
 *  \param input A filled out specialized input.
 *  \param output The pathname to save the archive to.
 *  \return The round trip object.
 */
template <typename T>
T testArchive(const T& input, const std::string& tempPathname = "temp")
{
    std::ofstream outFile(tempPathname);
    {
        boost::archive::text_oarchive outArchive(outFile);
        outArchive << input;
    }
    T output;
    {
        std::ifstream inFile(tempPathname);
        boost::archive::text_iarchive inArchive(inFile);
        inArchive >> output;
    }
    return output;
}

/*
 *  \func testStdout
 *  \brief Gets the stdout string. Used to test that the ostream is correct.
 *
 *  \tparam T The data type to test
 *  \param obj The object to stream out.
 *  \return The string sent to stdout.
 */
template <typename T>
std::string testStdout(const T& obj = T())
{
    testing::internal::CaptureStdout();
    std::cout << obj;
    return testing::internal::GetCapturedStdout();
}
}
}

#endif
