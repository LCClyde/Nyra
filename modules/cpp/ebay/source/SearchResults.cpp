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
#include <nyra/ebay/SearchResults.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
void updateCurrency(const std::string& currency,
                    std::string& price)
{
    if (currency == "USD")
    {
        price = "$" + price;
    }
    else
    {
        price += " " + currency;
    }
}
}

namespace nyra
{
namespace ebay
{
//===========================================================================//
SearchResult::SearchResult(const mem::Tree<xml::Element>& item) :
    itemId(item["itemId"].get().text),
    title(item["title"].get().text),
    galleryURL(item["galleryURL"].get().text),
    viewItemURL(item["viewItemURL"].get().text),
    startTime(item["listingInfo"]["startTime"].get().text),
    endTime(item["listingInfo"]["endTime"].get().text),
    timeLeft(item["sellingStatus"]["timeLeft"].get().text)
{
    const auto& shippingInfo = item["shippingInfo"];
    if (shippingInfo.has("shippingServiceCost"))
    {
        shippingCost = shippingInfo["shippingServiceCost"].get().text;
        const std::string shippingCurrency =
               shippingInfo["shippingServiceCost"].get().
                       attributes.at("currencyId");
        updateCurrency(shippingCurrency, shippingCost);
    }
    else
    {
        shippingCost = "???";
    }

    const auto& sellingStatus = item["sellingStatus"];
    currentPrice = sellingStatus["currentPrice"].get().text;
    const std::string sellingCurrency =
            sellingStatus["currentPrice"].get().
                    attributes.at("currencyId");
    updateCurrency(sellingCurrency, currentPrice);
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os, const SearchResult& result)
{
    os << "Item ID: " << result.itemId << "\n"
       << "Title: " << result.title << "\n"
       << "Gallery URL: " << result.galleryURL << "\n"
       << "View Item URL: " << result.viewItemURL << "\n"
       << "Shipping Cost: " << result.shippingCost << "\n"
       << "Current Price: " << result.currentPrice << "\n"
       << "Start Time: " << result.startTime << "\n"
       << "End Time: " << result.endTime << "\n"
       << "Time Left: " << result.timeLeft;
    return os;
}

//===========================================================================//
SearchResults getSearchResults(const std::string& webResults)
{
    const xml::XML results = xml::XML(webResults);
    const std::string ack =
            results["findItemsByKeywordsResponse"]["ack"].get().text;
    if (ack != "Success")
    {
        throw std::runtime_error("Error in Ebay ACK: " + ack);
    }

    size_t count = core::str::toType<size_t>(
            results["findItemsByKeywordsResponse"]
                   ["searchResult"].get().attributes.at("count"));
    const auto& searchResultNode =
            results["findItemsByKeywordsResponse"]["searchResult"];

    SearchResults searchResults;
    for (size_t ii = 0; ii < count; ++ii)
    {
        searchResults.push_back(SearchResult(searchResultNode["item"][ii]));
    }
    return searchResults;
}
}
}
