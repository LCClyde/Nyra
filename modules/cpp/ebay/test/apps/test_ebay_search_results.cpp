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
#include <nyra/test/Test.h>
#include <nyra/ebay/SearchResults.h>

namespace
{
const std::string SAMPLE_INPUT =
"<?xml version='1.0' encoding='UTF-8'?>"
"<findItemsByKeywordsResponse xmlns=\"http://www.ebay.com/marketplace/search/v1/services\">"
"    <ack>Success</ack>"
"    <version>1.13.0</version>"
"    <timestamp>2017-04-16T12:24:06.548Z</timestamp>"
"    <searchResult count=\"2\">"
"    <item>"
"        <itemId>361942910373</itemId>"
"        <title>Foo</title>"
"        <globalId>EBAY-US</globalId>"
"        <primaryCategory>"
"            <categoryId>38292</categoryId>"
"            <categoryName>MTG Individual Cards</categoryName>"
"       </primaryCategory>"
"       <galleryURL>http://foo.jpg</galleryURL>"
"       <viewItemURL>http://www.ebay.com/foo</viewItemURL>"
"       <paymentMethod>PayPal</paymentMethod>"
"       <autoPay>true</autoPay>"
"       <postalCode>04011</postalCode>"
"       <location>Somewhere, USA</location>"
"       <country>US</country><shippingInfo>"
"       <shippingServiceCost currencyId=\"USD\">3.5</shippingServiceCost>"
"       <shippingType>Flat</shippingType>"
"       <shipToLocations>US</shipToLocations>"
"       <expeditedShipping>false</expeditedShipping>"
"       <oneDayShippingAvailable>false</oneDayShippingAvailable>"
"       <handlingTime>2</handlingTime></shippingInfo>"
"       <sellingStatus>"
"           <currentPrice currencyId=\"USD\">29.99</currentPrice>"
"           <convertedCurrentPrice currencyId=\"USD\">29.99</convertedCurrentPrice>"
"           <sellingState>Active</sellingState>"
"           <timeLeft>P15DT14H26M59S</timeLeft>"
"       </sellingStatus>"
"       <listingInfo>"
"           <bestOfferEnabled>false</bestOfferEnabled>"
"           <buyItNowAvailable>false</buyItNowAvailable>"
"           <startTime>2017-04-02T02:51:05.000Z</startTime>"
"           <endTime>2017-05-02T02:51:05.000Z</endTime>"
"           <listingType>FixedPrice</listingType>"
"           <gift>false</gift>"
"       </listingInfo>"
"       <returnsAccepted>false</returnsAccepted>"
"       <condition>"
"           <conditionId>1000</conditionId>"
"           <conditionDisplayName>New</conditionDisplayName>"
"       </condition>"
"       <isMultiVariationListing>false</isMultiVariationListing>"
"       <topRatedListing>false</topRatedListing>"
"    </item>"
"    <item>"
"        <itemId>361942910374</itemId>"
"        <title>Bar</title>"
"        <globalId>EBAY-US</globalId>"
"        <primaryCategory>"
"            <categoryId>38292</categoryId>"
"            <categoryName>MTG Individual Cards</categoryName>"
"       </primaryCategory>"
"       <galleryURL>http://bar.jpg</galleryURL>"
"       <viewItemURL>http://www.ebay.com/bar</viewItemURL>"
"       <paymentMethod>PayPal</paymentMethod>"
"       <autoPay>true</autoPay>"
"       <postalCode>04011</postalCode>"
"       <location>Somewhere, USA</location>"
"       <country>US</country><shippingInfo>"
"       <shippingServiceCost currencyId=\"USD\">1.5</shippingServiceCost>"
"       <shippingType>Flat</shippingType>"
"       <shipToLocations>US</shipToLocations>"
"       <expeditedShipping>false</expeditedShipping>"
"       <oneDayShippingAvailable>false</oneDayShippingAvailable>"
"       <handlingTime>2</handlingTime></shippingInfo>"
"       <sellingStatus>"
"           <currentPrice currencyId=\"USD\">19.99</currentPrice>"
"           <convertedCurrentPrice currencyId=\"USD\">19.99</convertedCurrentPrice>"
"           <sellingState>Active</sellingState>"
"           <timeLeft>P16DT14H26M59S</timeLeft>"
"       </sellingStatus>"
"       <listingInfo>"
"           <bestOfferEnabled>false</bestOfferEnabled>"
"           <buyItNowAvailable>false</buyItNowAvailable>"
"           <startTime>2017-03-02T02:51:05.000Z</startTime>"
"           <endTime>2017-06-02T02:51:05.000Z</endTime>"
"           <listingType>FixedPrice</listingType>"
"           <gift>false</gift>"
"       </listingInfo>"
"       <returnsAccepted>false</returnsAccepted>"
"       <condition>"
"           <conditionId>1000</conditionId>"
"           <conditionDisplayName>New</conditionDisplayName>"
"       </condition>"
"       <isMultiVariationListing>false</isMultiVariationListing>"
"       <topRatedListing>false</topRatedListing>"
"    </item>"
"    </searchResult>"
"    <paginationOutput>"
"        <pageNumber>1</pageNumber>"
"        <entriesPerPage>100</entriesPerPage>"
"        <totalPages>1</totalPages>"
"        <totalEntries>2</totalEntries>"
"    </paginationOutput>"
"    <itemSearchURL>http://www.ebay.com/sch/anything</itemSearchURL>"
"</findItemsByKeywordsResponse>";
}

namespace nyra
{
namespace ebay
{
TEST(SearchResults, Parse)
{
    SearchResults searchResults = getSearchResults(SAMPLE_INPUT);

    EXPECT_EQ(static_cast<size_t>(2), searchResults.size());

    EXPECT_EQ(searchResults[0].itemId, "361942910373");
    EXPECT_EQ(searchResults[0].title, "Foo");
    EXPECT_EQ(searchResults[0].galleryURL, "http://foo.jpg");
    EXPECT_EQ(searchResults[0].viewItemURL, "http://www.ebay.com/foo");
    EXPECT_EQ(searchResults[0].shippingCost, "$3.5");
    EXPECT_EQ(searchResults[0].currentPrice, "$29.99");
    EXPECT_EQ(searchResults[0].startTime, "2017-04-02T02:51:05.000Z");
    EXPECT_EQ(searchResults[0].endTime, "2017-05-02T02:51:05.000Z");
    EXPECT_EQ(searchResults[0].timeLeft, "P15DT14H26M59S");

    EXPECT_EQ(searchResults[1].itemId, "361942910374");
    EXPECT_EQ(searchResults[1].title, "Bar");
    EXPECT_EQ(searchResults[1].galleryURL, "http://bar.jpg");
    EXPECT_EQ(searchResults[1].viewItemURL, "http://www.ebay.com/bar");
    EXPECT_EQ(searchResults[1].shippingCost, "$1.5");
    EXPECT_EQ(searchResults[1].currentPrice, "$19.99");
    EXPECT_EQ(searchResults[1].startTime, "2017-03-02T02:51:05.000Z");
    EXPECT_EQ(searchResults[1].endTime, "2017-06-02T02:51:05.000Z");
    EXPECT_EQ(searchResults[1].timeLeft, "P16DT14H26M59S");
}

TEST(SearchResults, Stdout)
{
    SearchResults searchResults = getSearchResults(SAMPLE_INPUT);

    std::string expected =
            "Item ID: 361942910373\n"
            "Title: Foo\n"
            "Gallery URL: http://foo.jpg\n"
            "View Item URL: http://www.ebay.com/foo\n"
            "Shipping Cost: $3.5\n"
            "Current Price: $29.99\n"
            "Start Time: 2017-04-02T02:51:05.000Z\n"
            "End Time: 2017-05-02T02:51:05.000Z\n"
            "Time Left: P15DT14H26M59S";
    EXPECT_EQ(test::stdout(searchResults[0]), expected);

    expected =
            "Item ID: 361942910374\n"
            "Title: Bar\n"
            "Gallery URL: http://bar.jpg\n"
            "View Item URL: http://www.ebay.com/bar\n"
            "Shipping Cost: $1.5\n"
            "Current Price: $19.99\n"
            "Start Time: 2017-03-02T02:51:05.000Z\n"
            "End Time: 2017-06-02T02:51:05.000Z\n"
            "Time Left: P16DT14H26M59S";
    EXPECT_EQ(test::stdout(searchResults[1]), expected);
}
}
}

NYRA_TEST()
