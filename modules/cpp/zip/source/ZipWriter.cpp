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
#include <nyra/zip/ZipWriter.h>

namespace nyra
{
namespace zip
{
//===========================================================================//
ZipWriter::ZipWriter(const std::string& pathname,
                     Format format) :
    mArchive(archive_write_new())
{
    if (format == AUTO)
    {
        format = fileToFormat(pathname);
    }

    switch (format)
    {
    case GZIP:
        archive_write_add_filter_gzip(mArchive);
        archive_write_set_format_pax_restricted(mArchive);
        break;
    case BZIP2:
        archive_write_add_filter_bzip2(mArchive);
        archive_write_set_format_pax_restricted(mArchive);
        break;
    case ZIP:
        archive_write_set_format_zip(mArchive);
        archive_write_zip_set_compression_store(mArchive);
        break;
    case SEVEN_ZIP:
        archive_write_set_format_7zip(mArchive);
        archive_write_set_format_pax_restricted(mArchive);
        break;
    case TAR:
        archive_write_add_filter_none(mArchive);
        archive_write_set_format_pax_restricted(mArchive);
        break;
    default:
        throw std::runtime_error(
                "Unsupported zip format: " + std::to_string(format));
    }

    archive_write_open_filename(mArchive, pathname.c_str());
}

//===========================================================================//
ZipWriter::~ZipWriter()
{
    archive_write_close(mArchive);
    archive_write_free(mArchive);
}

//===========================================================================//
void ZipWriter::write(const std::string& pathname,
                      const void* buffer,
                      size_t size)
{
    archive_entry* entry = archive_entry_new();
    archive_entry_set_pathname(entry, pathname.c_str());
    archive_entry_set_size(entry, size);
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(mArchive, entry);
    archive_write_data(mArchive, buffer, size);
    archive_entry_free(entry);
}
}
}
