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
#ifndef __NYRA_CORE_FILE_H__
#define __NYRA_CORE_FILE_H__

#include <string>
#include <vector>

namespace nyra
{
namespace core
{
/*
 *  \func getFileSize
 *  \brief Gets the size of the a file in bytes.
 *
 *  \param pathname The full pathname of the file
 *  \return The size in bytes.
 */
size_t getFileSize(const std::string& pathname);

/*
 *  \func readBinaryFile
 *  \brief Reads the entire file into binary.
 *
 *  \param pathname The full pathname of the file.
 *  \return The bytes in the binary.
 */
std::vector<uint8_t> readBinaryFile(const std::string& pathname);

/*
 *  \func readFile
 *  \brief Reads the entire file into a string.
 *
 *  \param pathname The full pathname of the file.
 *  \return The contents of the file.
 */
std::string readFile(const std::string& pathname);

void writeFile(const std::string& contents,
               const std::string& pathname);

void writeBinary(const void* contents,
                 size_t size,
                 const std::string& pathname);

void writeBinary(const std::vector<uint8_t>& contents,
                 const std::string& pathname)
{
    writeBinary(contents.data(), contents.size(), pathname);
}
}
}

#endif
