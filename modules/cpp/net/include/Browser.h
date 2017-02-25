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
#ifndef __NYRA_NET_BROWSER_H__
#define __NYRA_NET_BROWSER_H__

#include <random>
#include <string>
#include <nyra/net/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace net
{
/*
 *  \type Param
 *  \brief Holds a key value pair for url parameters
 */
typedef std::pair<std::string, std::string> Param;

/*
 *  \class Browser
 *  \brief Mimics a browser to interact with the web.
 */
class Browser: private mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the browser
     *
     *  \param cacheTime The time to set for the caching in days. If a value
     *         of 0 is used, no cache is ever done.
     *  \param cacheDir The directory to cache files to.
     *  \param cacheRandom An extra random factor to add to the cache
     *         time in days. This helps spread out the cache misses
     *         over a larger period.
     */
    Browser(size_t cacheTime = 0,
            const std::string& cacheDir = "cache",
            size_t cacheRandom = 1);

    /*
     *  \func get
     *  \brief Does the equivalent of a HTTP GET call.
     *
     *  \param url The target URL
     *  \param params The URL parameters. These do not need to be
     *         percent encoded.
     *  \return The results of the call
     */
    std::string get(const std::string& url,
                    const std::vector<Param>& params = std::vector<Param>());

private:
    std::string getCached(const std::string& url) const;

    void cacheURL(const std::string& url,
                  const std::string& contents);

    std::string getCachePathname(const std::string& url) const;

    const size_t mCacheTime;
    const std::string mCacheDir;
    std::mt19937 mGenerator;
    std::uniform_int_distribution<size_t> mCacheRandom;
};
}
}

#endif
