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
#ifndef __NYRA_ZIP_READER_H__
#define __NYRA_ZIP_READER_H__

#include <vector>
#include <string>
#include <limits>
#include <archive.h>

namespace nyra
{
namespace zip
{
/*
 *  \class Reader
 *  \brief Class for reading from zip files.
 */
class Reader
{
public:
    /*
     *  \func Constructor
     *  \brief Loads a zip file.
     *
     *  \param pathname The name of the file on disk
     *  \throw If the file does not exist or if it is not a zip file.
     */
    Reader(const std::string& pathname);

    /*
     *  \func list
     *  \brief Lists all files in the zip
     *
     *  \return A vector of the pathnames in the file.
     */
    std::vector<std::string> list() const;

    /*
     *  \func read
     *  \brief Reads a file into a string
     *
     *  \param pathname The location of the file in the zip
     *  \param offset The number of bytes to skip before reading.
     *  \param size The number of bytes to read. If there are less bytes
     *         available this will only read until EOF is reached.
     *  \return A string of the file contents.
     */
    std::string read(const std::string& pathname,
                     size_t offset = 0,
                     size_t size = std::numeric_limits<size_t>::max()) const;

    /*
     *  \func readBinary
     *  \brief Reads a file into a vector
     *
     *  \param pathname The location of the file in the zip
     *  \param offset The number of bytes to skip before reading.
     *  \param size The number of bytes to read. If there are less bytes
     *         available this will only read until EOF is reached.
     *  \return A vector of the file contents.
     */
    std::vector<uint8_t> readBinary(
            const std::string& pathname,
            size_t offset = 0,
            size_t size = std::numeric_limits<size_t>::max()) const;

private:
    archive* openArchive() const;

    void seek(size_t offset, archive* zipArchive) const;

    const std::string mPathname;
};
}
}

#endif
