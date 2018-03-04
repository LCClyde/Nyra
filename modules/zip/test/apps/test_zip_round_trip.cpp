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
#include <nyra/zip/Writer.h>
#include <nyra/zip/Reader.h>

namespace
{
static const std::string BASE_NAME = "zip_round_trip";
static const std::pair<std::string, std::string> FILE_1(
        "hello_world.txt", "Hello World!");
static const std::pair<std::string, std::string> FILE_2(
        "sub/directory/sub.txt", "Subdirectory");
static const std::pair<std::string, std::vector<uint8_t> > FILE_3(
        "binary.bin", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

void save(const std::string extension)
{
    nyra::zip::Writer writer(BASE_NAME + extension);
    writer.write(FILE_1.first, FILE_1.second);
    writer.write(FILE_2.first, FILE_2.second);
    writer.write(FILE_3.first, FILE_3.second.data(), FILE_3.second.size());
}

void read(const std::string extension,
          std::vector<std::string>& list,
          std::string& file1,
          std::string& file2,
          std::vector<uint8_t>& file3)
{
    nyra::zip::Reader reader(BASE_NAME + extension);
    list = reader.list();
    file1 = reader.read(FILE_1.first);
    file2 = reader.read(FILE_2.first);
    file3 = reader.readBinary(FILE_3.first);

    std::remove((BASE_NAME + extension).c_str());
}
}

namespace nyra
{
namespace zip
{
TEST(Zip, GZIP)
{
    save(".tar.gz");
    std::vector<std::string> list;
    std::string file1;
    std::string file2;
    std::vector<uint8_t> file3;
    read(".tar.gz", list, file1, file2, file3);

    EXPECT_EQ(FILE_1.first, list[0]);
    EXPECT_EQ(FILE_2.first, list[1]);
    EXPECT_EQ(FILE_3.first, list[2]);

    EXPECT_EQ(FILE_1.second, file1);
    EXPECT_EQ(FILE_2.second, file2);
    EXPECT_EQ(FILE_3.second, file3);
}

TEST(Zip, BZ2)
{
    save(".tar.bz2");
    std::vector<std::string> list;
    std::string file1;
    std::string file2;
    std::vector<uint8_t> file3;
    read(".tar.bz2", list, file1, file2, file3);

    EXPECT_EQ(FILE_1.first, list[0]);
    EXPECT_EQ(FILE_2.first, list[1]);
    EXPECT_EQ(FILE_3.first, list[2]);

    EXPECT_EQ(FILE_1.second, file1);
    EXPECT_EQ(FILE_2.second, file2);
    EXPECT_EQ(FILE_3.second, file3);
}

TEST(Zip, ZIP)
{
    save(".zip");
    std::vector<std::string> list;
    std::string file1;
    std::string file2;
    std::vector<uint8_t> file3;
    read(".zip", list, file1, file2, file3);

    EXPECT_EQ(FILE_1.first, list[0]);
    EXPECT_EQ(FILE_2.first, list[1]);
    EXPECT_EQ(FILE_3.first, list[2]);

    EXPECT_EQ(FILE_1.second, file1);
    EXPECT_EQ(FILE_2.second, file2);
    EXPECT_EQ(FILE_3.second, file3);
}

TEST(Zip, TAR)
{
    save(".tar");
    std::vector<std::string> list;
    std::string file1;
    std::string file2;
    std::vector<uint8_t> file3;
    read(".tar", list, file1, file2, file3);

    EXPECT_EQ(FILE_1.first, list[0]);
    EXPECT_EQ(FILE_2.first, list[1]);
    EXPECT_EQ(FILE_3.first, list[2]);

    EXPECT_EQ(FILE_1.second, file1);
    EXPECT_EQ(FILE_2.second, file2);
    EXPECT_EQ(FILE_3.second, file3);
}

TEST(Zip, SEVEN_ZIP)
{
    save(".7z");
    std::vector<std::string> list;
    std::string file1;
    std::string file2;
    std::vector<uint8_t> file3;
    read(".7z", list, file1, file2, file3);

    EXPECT_EQ(FILE_1.first, list[0]);
    EXPECT_EQ(FILE_2.first, list[1]);
    EXPECT_EQ(FILE_3.first, list[2]);

    EXPECT_EQ(FILE_1.second, file1);
    EXPECT_EQ(FILE_2.second, file2);
    EXPECT_EQ(FILE_3.second, file3);
}
}
}

NYRA_TEST()
