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
#include <nyra/ebay/Ebay.h>


namespace nyra
{
namespace ebay
{
//===========================================================================//
Ebay::Ebay(const std::string& appId) :
    mAppId(appId)
    //mBrowser(30, "./ebay_cache")
{
}

//===========================================================================//
SearchResults Ebay::search(const std::string& keywords) const
{
    const std::string url =
            "http://svcs.ebay.com/services/search/FindingService/v1";
    std::vector<net::Param> params;
    params.push_back(net::Param("OPERATION-NAME", "findItemsByKeywords"));
    params.push_back(net::Param("SERVICE-VERSION", "1.0.0"));
    params.push_back(net::Param("SECURITY-APPNAME", mAppId));
    params.push_back(net::Param("RESPONSE-DATA-FORMAT", "XML"));
    params.push_back(net::Param("REST-PAYLOAD", ""));
    params.push_back(net::Param("keywords", keywords));

    return getSearchResults(mBrowser.get(url, params));
}
}
}
