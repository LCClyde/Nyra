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
#ifndef __NYRA_ZIP_ZIP_WRITER_H__
#define __NYRA_ZIP_ZIP_WRITER_H__

#include <string>
#include <archive.h>
#include <nyra/zip/Format.h>

namespace nyra
{
namespace zip
{
/*
 *  \class ZipWriter
 *  \brief Writes a zip file. All formats in zip/Types.h are supported.
 */
class ZipWriter
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up and opens the zip file to write.
     *
     *  \param pathname The pathname to the zip file
     *  \param format The format of the zip. If this is set to AUTO it will
     *         try to determine the format from the pathname.
     */
    ZipWriter(const std::string& pathname,
              Format format = AUTO);

    /*
     *  \func Destructor
     *  \brief Closes the zip file.
     */
    ~ZipWriter();

    /*
     *  \func write
     *  \brief Writes a file to the zip.
     *
     *  \param pathname The location to write in the zip folder
     *  \buffer The bytes to write
     *  \size The size of the buffer
     */
    void write(const std::string& pathname,
               const void* buffer,
               size_t size);

    /*
     *  \func write
     *  \brief Writes a file to the zip.
     *
     *  \param pathname The location to write in the zip folder
     *  \buffer The string to write
     */
    void write(const std::string& pathname,
               const std::string& buffer)
    {
        write(pathname, buffer.c_str(), buffer.length());
    }

private:
    archive* const mArchive;
};
}
}

#endif
