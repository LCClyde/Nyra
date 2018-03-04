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
#include <stdexcept>
#include <archive_entry.h>
#include <nyra/zip/Reader.h>
#include <nyra/zip/Verify.h>

namespace
{
static const size_t BLOCK_SIZE = 10240;
}

namespace nyra
{
namespace zip
{
//===========================================================================//
Reader::Reader(const std::string& pathname) :
    mPathname(pathname)
{
    if (!verify(pathname))
    {
        throw std::runtime_error(pathname + " is not a valid zip file");
    }
}

//===========================================================================//
std::vector<std::string> Reader::list() const
{
    archive* zipArchive = openArchive();

    std::vector<std::string> ret;
    archive_entry* entry;

    while (archive_read_next_header(zipArchive, &entry) == ARCHIVE_OK)
    {
        ret.push_back(archive_entry_pathname(entry));
        archive_read_data_skip(zipArchive);
    }

    archive_read_free(zipArchive);

    return ret;
}

//===========================================================================//
std::string Reader::read(const std::string& pathname,
                         size_t offset,
                         size_t size) const
{
    archive* zipArchive = openArchive();
    archive_entry* entry;

    while (archive_read_next_header(zipArchive, &entry) == ARCHIVE_OK)
    {
        if (pathname == archive_entry_pathname(entry))
        {
            std::string ret(std::min<size_t>(archive_entry_size(entry), size), '\0');

            // TODO: archive_seek_data did not work how I wanted. It would
            //       be nice to find a better way to do this.
            seek(offset, zipArchive);
            archive_read_data(zipArchive,
                              const_cast<char*>(ret.c_str()),
                              ret.length());
            archive_read_free(zipArchive);
            return ret;
        }
    }

    archive_read_free(zipArchive);
    throw std::runtime_error(pathname + " is not in " + mPathname);
}

//===========================================================================//
// TODO: Create a readImpl that can avoid this code duplication. For now
//       the method is simple enough that I don't care.
std::vector<uint8_t> Reader::readBinary(const std::string& pathname,
                                        size_t offset,
                                        size_t size) const
{
    archive* zipArchive = openArchive();
    archive_entry* entry;

    while (archive_read_next_header(zipArchive, &entry) == ARCHIVE_OK)
    {
        if (pathname == archive_entry_pathname(entry))
        {
            std::vector<uint8_t> ret(std::min<size_t>(archive_entry_size(entry), size));

            // TODO: archive_seek_data did not work how I wanted. It would
            //       be nice to find a better way to do this.
            seek(offset, zipArchive);
            archive_read_data(zipArchive,
                              const_cast<uint8_t*>(ret.data()),
                              ret.size());
            archive_read_free(zipArchive);
            return ret;
        }
    }

    archive_read_free(zipArchive);
    throw std::runtime_error(pathname + " is not in " + mPathname);
}

//===========================================================================//
archive* Reader::openArchive() const
{
    archive* zipArchive = archive_read_new();
    archive_read_support_filter_all(zipArchive);
    archive_read_support_format_all(zipArchive);
    archive_read_open_filename(zipArchive, mPathname.c_str(), BLOCK_SIZE);
    return zipArchive;
}

//===========================================================================//
void Reader::seek(size_t offset, archive* zipArchive) const
{
    if (offset == 0)
    {
        return;
    }

    std::string ret(std::min(offset, BLOCK_SIZE), '\0');
    size_t remaining = offset;

    while (remaining > 0)
    {
        const size_t readSize = std::min(remaining, BLOCK_SIZE);
        archive_read_data(zipArchive,
                          const_cast<char*>(ret.c_str()),
                          readSize);
        remaining -= readSize;
    }
}
}
}
