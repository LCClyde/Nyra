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
#ifndef __NYRA_EBAY_SEARCH_RESULTS_H__
#define __NYRA_EBAY_SEARCH_RESULTS_H__

#include <string>
#include <vector>
#include <ostream>
#include <nyra/xml/XML.h>

namespace nyra
{
namespace ebay
{
/*
 *  \class SearchResult
 *  \brief An in memory representation of the Ebay find results.
 */
struct SearchResult
{
    /*
     *  \func Constructor
     *  \brief Initializes the search result
     *
     *  \param item The XML elment to use to populate the results.
     */
    SearchResult(const mem::Tree<xml::Element>& item);

    /*
     *  \var itemId
     *  \brief The Ebay unique item ID
     */
    const std::string itemId;

    /*
     *  \var title
     *  \brief The title of the auction.
     */
    const std::string title;

    /*
     *  \var galleryURL
     *  \brief The URL to a thumbnail of the auction
     */
    const std::string galleryURL;

    /*
     *  \var viewItemURL
     *  \brief The URL to the auction.
     */
    const std::string viewItemURL;

    /*
     *  \var shippingCost
     *  \brief The cost to ship the item
     */
    std::string shippingCost;

    /*
     *  \var currentPrice
     *  \brief The current auction price.
     */
    std::string currentPrice;

    /*
     *  \var startTime
     *  \brief The time when the auction was listed
     */
    const std::string startTime;

    /*
     *  \var endTime
     *  \brief The time the auction ends
     */
    const std::string endTime;

    /*
     *  \var timeLeft
     *  \brief The remaining time on the auction.
     */
    const std::string timeLeft;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const SearchResult& result);
};

/*
 *  \type SearchResults
 *  \brief A list of SearchResult.
 */
typedef std::vector<SearchResult> SearchResults;

/*
 *  \func getSearchResults
 *  \brief Parses the web return into an in memory list of results
 *
 *  \param webResults The return XML from the Ebay API
 *  \return The Ebay search results.
 */
SearchResults getSearchResults(const std::string& webResults);
}
}

#endif
