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
#ifndef __NYRA_CRYPTO_BASE_X_H__
#define __NYRA_CRYPTO_BASE_X_H__

#include <string>

namespace nyra
{
namespace crypto
{
/*
 *  \func base64Encode
 *  \brief Performs base 64 encoding on a buffer.
 *
 *  \param buffer The buffer to encode
 *  \size The size of the buffer
 *  \return The encoded buffer.
 */
std::string base64Encode(const void* buffer, size_t size);

/*
 *  \func base64Encode
 *  \brief Performs base 64 encoding on a buffer.
 *
 *  \param buffer The buffer to encode
 *  \return The encoded buffer.
 */
inline std::string base64Encode(const std::string& buffer)
{
    return base64Encode(buffer.c_str(), buffer.size());
}

/*
 *  \func base64Decode
 *  \brief Performs base 64 decoding on a buffer.
 *
 *  \param buffer The buffer to decode
 *  \return The decoded buffer.
 */
std::string base64Decode(const std::string& buffer);
}
}

#endif
