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
#include <nyra/xml/XML.h>

namespace
{
//===========================================================================//
static const std::string XML_STRING =
        "<main>\n"
        "    main text\n"
        "    <multi a='0' b='1' c='2'/>\n"
        "    <filename>/home/user/xml.xml</filename>\n"
        "    <modules>\n"
        "        <module type='graphics'>opengl"
        "            <nested>1</nested>\n"
        "        </module>\n"
        "        <module type='window'>opengl\n"
        "            <nested>2</nested>\n"
        "        </module>\n"
        "        <module type='window'>posix\n"
        "            <nested>3</nested>\n"
        "        </module>\n"
        "    </modules>\n"
        "    <debugLevel>2</debugLevel>\n"
        "</main>\n"
        "<ack>Success</ack>\n";
//===========================================================================//
void writeFile()
{
    std::ofstream stream("xml_round_trip.xml");
    stream << XML_STRING;
    stream.close();
}
}

namespace nyra
{
namespace xml
{
//===========================================================================//
TEST(XML, RoundTrip)
{
    writeFile();

    XML read = core::read<XML>("xml_round_trip.xml");
    std::remove("xml_round_trip.xml");

    EXPECT_EQ("main text", read["main"].get().text);

    EXPECT_EQ("", read["main"]["multi"].get().text);
    EXPECT_EQ("0", read["main"]["multi"].get().attributes["a"]);
    EXPECT_EQ("1", read["main"]["multi"].get().attributes["b"]);
    EXPECT_EQ("2", read["main"]["multi"].get().attributes["c"]);

    EXPECT_EQ("/home/user/xml.xml", read["main"]["filename"].get().text);
    EXPECT_EQ(static_cast<size_t>(3),
              read["main"]["modules"]["module"].size());
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][0].get().text);
    EXPECT_EQ("graphics",
              read["main"]["modules"]["module"][0].get().attributes["type"]);
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][1].get().text);
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][1].get().attributes["type"]);
    EXPECT_EQ("posix", read["main"]["modules"]["module"][2].get().text);
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][2].get().attributes["type"]);
    EXPECT_EQ("2", read["main"]["debugLevel"].get().text);
    EXPECT_EQ("1", read["main"]["modules"]["module"][0]["nested"].get().text);
    EXPECT_EQ("2", read["main"]["modules"]["module"][1]["nested"].get().text);
    EXPECT_EQ("3", read["main"]["modules"]["module"][2]["nested"].get().text);
    EXPECT_EQ("Success", read["ack"].get().text);

    core::write<XML>(read, "xml_round_trip.xml");
    XML write = core::read<XML>("xml_round_trip.xml");
    std::remove("xml_round_trip.xml");

    EXPECT_EQ("main text", write["main"].get().text);
    EXPECT_EQ("/home/user/xml.xml", write["main"]["filename"].get().text);
    EXPECT_EQ(static_cast<size_t>(3),
              write["main"]["modules"]["module"].size());
    EXPECT_EQ("opengl", write["main"]["modules"]["module"][0].get().text);
    EXPECT_EQ("graphics",
              write["main"]["modules"]["module"][0].get().attributes["type"]);
    EXPECT_EQ("opengl", write["main"]["modules"]["module"][1].get().text);
    EXPECT_EQ("window",
              write["main"]["modules"]["module"][1].get().attributes["type"]);
    EXPECT_EQ("posix", write["main"]["modules"]["module"][2].get().text);
    EXPECT_EQ("window",
              write["main"]["modules"]["module"][2].get().attributes["type"]);
    EXPECT_EQ("2", write["main"]["debugLevel"].get().text);
    EXPECT_EQ("1", write["main"]["modules"]["module"][0]["nested"].get().text);
    EXPECT_EQ("2", write["main"]["modules"]["module"][1]["nested"].get().text);
    EXPECT_EQ("3", write["main"]["modules"]["module"][2]["nested"].get().text);
    EXPECT_EQ("Success", write["ack"].get().text);
}

//===========================================================================//
TEST(XML, FromString)
{
    XML read(XML_STRING);

    EXPECT_EQ("main text", read["main"].get().text);
    EXPECT_EQ("/home/user/xml.xml", read["main"]["filename"].get().text);
    EXPECT_EQ(static_cast<size_t>(3),
              read["main"]["modules"]["module"].size());
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][0].get().text);
    EXPECT_EQ("graphics",
              read["main"]["modules"]["module"][0].get().attributes["type"]);
    EXPECT_EQ("opengl", read["main"]["modules"]["module"][1].get().text);
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][1].get().attributes["type"]);
    EXPECT_EQ("posix", read["main"]["modules"]["module"][2].get().text);
    EXPECT_EQ("window",
              read["main"]["modules"]["module"][2].get().attributes["type"]);
    EXPECT_EQ("2", read["main"]["debugLevel"].get().text);
    EXPECT_EQ("1", read["main"]["modules"]["module"][0]["nested"].get().text);
    EXPECT_EQ("2", read["main"]["modules"]["module"][1]["nested"].get().text);
    EXPECT_EQ("3", read["main"]["modules"]["module"][2]["nested"].get().text);
    EXPECT_EQ("Success", read["ack"].get().text);
}

//===========================================================================//
TEST(XML, Stdout)
{
    writeFile();
    XML read = core::read<XML>("xml_round_trip.xml");
    std::string results = test::stdout(read);

    // We cannot know the order of the output here, so we just check
    // if it created something decent.
    EXPECT_TRUE(!results.empty());

    // Now let's do something we can know
    XML test;
    test["main"] = new Element();
    test["main"]["test1"] = new Element();
    test["main"]["test1"]["test2"] = new Element();
    results = test::stdout(test);

    const std::string expected =
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<main>\n"
            "\t<test1>\n"
            "\t\t<test2/>\n"
            "\t</test1>\n"
            "</main>\n";

    EXPECT_EQ(expected, results);
    std::remove("xml_round_trip.xml");
}
}
}

NYRA_TEST()
