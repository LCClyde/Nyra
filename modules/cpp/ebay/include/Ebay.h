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
#ifndef __NYRA_EBAY_EBAY_H__
#define __NYRA_EBAY_EBAY_H__

#include <string>
#include <nyra/net/Browser.h>
#include <nyra/ebay/SearchResults.h>

namespace nyra
{
namespace ebay
{
/*
 *  \class Ebay
 *  \brief Creates an object that can interact with Ebay.
 */
class Ebay
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the Ebay object
     *
     *  \param appId The developer app ID used to interact with Ebay.
     */
    Ebay(const std::string& appId);

    /*
     *  \func search
     *  \brief Does the equivalent of an Ebay search.
     *
     *  \param keywords The terms to search for
     *  \return The search results
     */
    SearchResults search(const std::string& keywords) const;

private:
    const std::string& mAppId;
    mutable net::Browser mBrowser;
};
}
}

#endif

