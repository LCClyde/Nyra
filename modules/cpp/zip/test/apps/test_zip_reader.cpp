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
#include <nyra/zip/ZipReader.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace zip
{
TEST(ZipReader, Read)
{
    EXPECT_ANY_THROW(ZipReader(core::path::join(
            core::APPLICATION_PATH, "test_zip_reader")));

    ZipReader reader(core::path::join(
            core::DATA_PATH, "misc/test.tar.gz"));

    const std::vector<std::string> list = reader.list();

    EXPECT_EQ("hello_world.txt", list[0]);
    EXPECT_EQ("sub/directory/sub.txt", list[1]);
    EXPECT_EQ("binary.bin", list[2]);

    EXPECT_ANY_THROW(reader.read("foo"));

    EXPECT_EQ("Hello World!", reader.read("hello_world.txt"));
    EXPECT_EQ("Subdirectory", reader.read("sub/directory/sub.txt"));

    const std::vector<uint8_t> binary = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(binary, reader.readBinary("binary.bin"));

    // Partial read
    EXPECT_EQ("World", reader.read("hello_world.txt", 6, 5));

    const std::vector<uint8_t> partialBinary = {3, 4, 5};
    EXPECT_EQ(partialBinary, reader.readBinary("binary.bin", 3, 3));
}
}
}

NYRA_TEST()
