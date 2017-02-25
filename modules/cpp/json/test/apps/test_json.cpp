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
#include <algorithm>
#include <nyra/test/Test.h>
#include <nyra/json/JSON.h>

namespace
{
static const std::string PATHNAME = "json_round_trip.json";

void writeFile()
{
    const std::string jsonString =
        "{\n"
        "    \"main\":\n"
        "    {\n"
        "        \"text\": \"main text\",\n"
        "        \"filename\": \"/home/user/xml.xml\",\n"
        "        \"small_list\": [\n"
        "            \"value\"\n"
        "        ],\n"
        "        \"modules\":\n"
        "        {\n"
        "            \"module\":\n"
        "            [{\n"
        "                \"type\": \"graphics\",\n"
        "                \"text\": \"opengl\"\n"
        "            },\n"
        "            {\n"
        "                \"type\": \"window\",\n"
        "                \"text\": \"opengl\"\n"
        "            },\n"
        "            {\n"
        "                \"type\": \"window\",\n"
        "                \"text\": \"posix\"\n"
        "            }]\n"
        "        },\n"
        "        \"debugLevel\": \"2\",\n"
        "        \"array\":\n"
        "        [\n"
        "            \"1\",\n"
        "            \"2\",\n"
        "            \"3\"\n"
        "        ]\n"
        "    }\n"
        "}\n";

    std::ofstream stream(PATHNAME);
    stream << jsonString;
    stream.close();
}
}

namespace nyra
{
namespace json
{
TEST(JSON, RoundTrip)
{
    writeFile();

    const JSON read = core::read<JSON>(PATHNAME);
    std::remove(PATHNAME.c_str());

    EXPECT_EQ("main text", read["main"]["text"].get());
    EXPECT_EQ("/home/user/xml.xml", read["main"]["filename"].get());
    EXPECT_EQ("", read["main"]["small_list"].get());
    EXPECT_EQ(static_cast<size_t>(1), read["main"]["small_list"].size());
    EXPECT_EQ("value", read["main"]["small_list"][0].get());

    EXPECT_EQ(static_cast<size_t>(3),
              read["main"]["modules"]["module"].size());
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][0]["text"].get());
    EXPECT_EQ("graphics",
              read["main"]["modules"]["module"][0]["type"].get());
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][1]["text"].get());
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][1]["type"].get());
    EXPECT_EQ("posix", read["main"]["modules"]["module"][2]["text"].get());
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][2]["type"].get());
    EXPECT_EQ("2", read["main"]["debugLevel"].get());
    EXPECT_EQ(static_cast<size_t>(3),
              read["main"]["array"].size());
    EXPECT_EQ("1", read["main"]["array"][0].get());
    EXPECT_EQ("2", read["main"]["array"][1].get());
    EXPECT_EQ("3", read["main"]["array"][2].get());

    core::write<JSON>(read, PATHNAME);
    JSON write = core::read<JSON>(PATHNAME);
    std::remove(PATHNAME.c_str());

    EXPECT_EQ("main text", write["main"]["text"].get());
    EXPECT_EQ("/home/user/xml.xml", write["main"]["filename"].get());
    EXPECT_EQ("", write["main"]["small_list"].get());
    EXPECT_EQ(static_cast<size_t>(1), write["main"]["small_list"].size());
    EXPECT_EQ("value", write["main"]["small_list"][0].get());

    EXPECT_EQ(static_cast<size_t>(3),
            write["main"]["modules"]["module"].size());
    EXPECT_EQ("opengl", write["main"]["modules"]["module"][0]["text"].get());
    EXPECT_EQ("graphics",
            write["main"]["modules"]["module"][0]["type"].get());
    EXPECT_EQ("opengl", write["main"]["modules"]["module"][1]["text"].get());
    EXPECT_EQ("window",
            write["main"]["modules"]["module"][1]["type"].get());
    EXPECT_EQ("posix", write["main"]["modules"]["module"][2]["text"].get());
    EXPECT_EQ("window",
              write["main"]["modules"]["module"][2]["type"].get());
    EXPECT_EQ("2", write["main"]["debugLevel"].get());
    EXPECT_EQ(static_cast<size_t>(3),
              write["main"]["array"].size());
    EXPECT_EQ("1", write["main"]["array"][0].get());
    EXPECT_EQ("2", write["main"]["array"][1].get());
    EXPECT_EQ("3", write["main"]["array"][2].get());
}

TEST(JSON, Stdout)
{
    writeFile();
    JSON read = core::read<JSON>(PATHNAME);
    std::string results = test::stdout(read);
    std::remove(PATHNAME.c_str());

    // We cannot know the order of the output here, so we just check
    // if it created something decent.
    EXPECT_TRUE(!results.empty());

    // Now let's do something we can know
    JSON test;
    test["main"] = new std::string();
    test["main"]["test1"] = new std::string();
    test["main"]["test1"]["test2"] = new std::string("text");

    results = test::stdout(test);

    const std::string expected =
    "{\n"
    "    \"main\": {\n"
    "        \"test1\": {\n"
    "            \"test2\": \"text\"\n"
    "        }\n"
    "    }\n"
    "}\n";

    EXPECT_EQ(expected, results);
}
}
}

NYRA_TEST()
