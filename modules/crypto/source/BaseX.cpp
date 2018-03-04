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
#include <iostream>
#include <stdexcept>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <nyra/crypto/BaseX.h>

namespace
{
//===========================================================================//
size_t calcDecodeLength(const std::string& buffer)
{
    size_t padding = 0;

    if (buffer.length() >= 2 &&
        buffer[buffer.length() - 1] == '=' &&
        buffer[buffer.length() - 2] == '=')
    {
        padding = 2;
    }
    else if (buffer.length() >= 1 &&
             buffer[buffer.length() - 1] == '=')
    {
        padding = 1;
    }

    return (buffer.length() * 3) / 4 - padding;
}
}

namespace nyra
{
namespace crypto
{
//===========================================================================//
std::string base64Encode(const void* buffer, size_t size)
{
    BIO* b64f = BIO_new(BIO_f_base64());
    BIO* bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64f, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, size);
    BIO_flush(bio);

    BUF_MEM* ptr;
    BIO_get_mem_ptr(bio, &ptr);
    BIO_set_close(bio, BIO_CLOSE);
    const std::string results(ptr->data, ptr->length);
    BIO_free_all(bio);

    return results;
}

//===========================================================================//
std::string base64Decode(const std::string& buffer)
{
    std::string results(calcDecodeLength(buffer), '\0');

    BIO* bio = BIO_new_mem_buf(buffer.data(), -1);
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    char* outBuffer = const_cast<char*>(results.c_str());
    const size_t actualLength = BIO_read(bio, outBuffer, buffer.size());

    if (actualLength != results.length())
    {
        throw std::runtime_error("Base64 decode failed");
    }

    BIO_free_all(bio);
    return results;
}
}
}
