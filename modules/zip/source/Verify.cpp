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
#include <archive.h>
#include <nyra/zip/Verify.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace zip
{
bool verify(const std::string& pathname)
{
    if (!core::path::exists(pathname))
    {
        throw std::runtime_error(pathname + " does not exist");
    }

    archive* zipArchive = archive_read_new();
    archive_read_support_filter_all(zipArchive);
    archive_read_support_format_all(zipArchive);
    const int results = archive_read_open_filename(
            zipArchive, pathname.c_str(), 10240);
    archive_read_free(zipArchive);
    return results == ARCHIVE_OK;
}
}
}
