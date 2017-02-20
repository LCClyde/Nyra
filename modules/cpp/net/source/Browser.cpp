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
#include <fstream>
#include <iostream>
#include <nyra/core/File.h>
#include <nyra/core/Time.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>
#include <nyra/crypto/BaseX.h>
#include <nyra/net/Browser.h>

namespace
{
//===========================================================================//
const size_t DAYS_TO_MILLISECONDS = 86400000;

//===========================================================================//
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    static_cast<std::string*>(userp)->append(
            static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

//===========================================================================//
std::string urlEncode(CURL* curl,
                      const std::string& url,
                      const std::vector<nyra::net::Param>& params)
{
    if (params.empty())
    {
        return url;
    }

    std::string ret = url;

    // Add the params
    for (size_t ii = 0; ii < params.size(); ++ii)
    {
        if (ii == 0)
        {
            ret += "?";
        }
        else
        {
            ret += "&";
        }

        char* key = curl_easy_escape(
                curl, params[ii].first.c_str(), params[ii].first.length());
        ret += key + std::string("=");
        curl_free(key);

        char* value = curl_easy_escape(
                curl, params[ii].second.c_str(), params[ii].second.length());
        ret += value;
        curl_free(value);
    }

    return ret;
}
}

namespace nyra
{
namespace net
{
//===========================================================================//
Browser::Browser(size_t cacheTime,
                 const std::string& cacheDir,
                 size_t cacheRandom) :
    mCacheTime(cacheTime * DAYS_TO_MILLISECONDS),
    mCacheDir(cacheDir),
    mGenerator(core::epoch()),
    mCacheRandom(0, cacheRandom * DAYS_TO_MILLISECONDS)
{
    if (mCacheTime > 0)
    {
        core::path::makeDirectory(mCacheDir);
    }
}

//===========================================================================//
std::string Browser::get(const std::string& url,
                         const std::vector<Param>& params)
{
    CURL* curl = getGlobalInstance().get();
    const std::string encoded = urlEncode(curl, url, params);

    // Check for a cached file
    const std::string cache = getCached(encoded);

    if (!cache.empty())
    {
        return cache;
    }

    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, encoded.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    const CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw std::runtime_error("Failed to get contents of: " + url);
    }

    // Cache results
    cacheURL(url, readBuffer);

    return readBuffer;
}

//===========================================================================//
std::string Browser::getCached(const std::string& url) const
{
    // Zero cache time means never use the cache. Otherwise we respect
    // whatever the previous cache had set.
    if (mCacheTime == 0)
    {
        return "";
    }

    const std::string cachePathname = getCachePathname(url);
    const std::string timestampPathname = cachePathname + ".timestamp";

    // Check for cached file
    if (core::path::exists(timestampPathname))
    {
        // Get the timestamp
        const size_t timestamp = core::str::toType<size_t>(
                core::readFile(timestampPathname));

        if (core::epoch() < timestamp)
        {
            return core::readFile(cachePathname);
        }
    }

    return "";
}

//===========================================================================//
void Browser::cacheURL(const std::string& url,
                       const std::string& contents)
{
    if (mCacheTime == 0)
    {
        return;
    }

    const std::string cachePathname = getCachePathname(url);
    const std::string timestampPathname = cachePathname + ".timestamp";

    // Make sure the directory exists
    core::path::makeDirectory(core::path::getDirectory(cachePathname));

    // Save off the expire time.
    const size_t expireTime =
            core::epoch() + mCacheTime + mCacheRandom(mGenerator);

    std::ofstream timeStream(timestampPathname);
    timeStream << expireTime;
    timeStream.close();

    std::ofstream contentStream(cachePathname);
    contentStream << contents;
    contentStream.close();
}

//===========================================================================//
std::string Browser::getCachePathname(const std::string& url) const
{
    // Remove the first xxxx://
    size_t prefix = url.find(":") + 1;

    while (prefix < url.size() && url[prefix] == '/')
    {
        ++prefix;
    }

    return core::path::join(mCacheDir,
                            url.substr(prefix, std::string::npos));
}
}
}
