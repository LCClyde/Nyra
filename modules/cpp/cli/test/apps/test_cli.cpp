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
#include <nyra/cli/Parser.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace cli
{
TEST(CommandLine, ParseSimple)
{
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("test_cli"));
    argv.push_back(const_cast<char*>("--input"));
    argv.push_back(const_cast<char*>("in.txt"));
    argv.push_back(const_cast<char*>("--output"));
    argv.push_back(const_cast<char*>("out.txt"));
    argv.push_back(nullptr);

    Options options("ParseSimple");
    options.add("input", "Some input");
    options.add("output", "Some output");
    Parser parser(options, argv.size() - 1, argv.data());

    const std::string results = test::stdout(parser);
    const std::string expected =
            "ParseSimple:\n"
            "  -h [ --help ]         Produces this help message\n"
            "  --input arg           Some input\n"
            "  --output arg          Some output\n";
    EXPECT_EQ(expected, results);

    EXPECT_FALSE(parser.get<bool>("help"));
    EXPECT_EQ("in.txt", parser.get("input"));
    EXPECT_EQ("out.txt", parser.get("output"));
}

TEST(CommandLine, ParsePositional)
{
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("test_cli"));
    argv.push_back(const_cast<char*>("in.txt"));
    argv.push_back(const_cast<char*>("out.txt"));
    argv.push_back(nullptr);

    Options options("ParsePositional");
    options.add("input", "Some input").setPositional();
    options.add("output", "Some output").setPositional();
    Parser parser(options, argv.size() - 1, argv.data());

    const std::string results = test::stdout(parser);
    const std::string expected =
            "ParsePositional:\n"
            "  -h [ --help ]         Produces this help message\n"
            "  --input arg           Some input\n"
            "  --output arg          Some output\n";
    EXPECT_EQ(expected, results);

    EXPECT_FALSE(parser.get<bool>("help"));
    EXPECT_EQ("in.txt", parser.get("input"));
    EXPECT_EQ("out.txt", parser.get("output"));
}

TEST(CommandLine, ParseFlags)
{
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("test_cli"));
    argv.push_back(const_cast<char*>("--flag2"));
    argv.push_back(nullptr);

    Options options("ParseFlags");
    options.add("flag1", "Flag 1").setIsFlag();
    options.add("flag2", "Flag 2").setIsFlag();
    Parser parser(options, argv.size() - 1, argv.data());

    const std::string results = test::stdout(parser);
    const std::string expected =
            "ParseFlags:\n"
            "  -h [ --help ]         Produces this help message\n"
            "  --flag1               Flag 1\n"
            "  --flag2               Flag 2\n";
    EXPECT_EQ(expected, results);

    EXPECT_FALSE(parser.get<bool>("help"));
    EXPECT_FALSE(parser.get<bool>("flag1"));
    EXPECT_TRUE(parser.get<bool>("flag2"));
}

TEST(CommandLine, ParseDefaults)
{

    Options options("ParseDefaults");
    options.add("string", "Default String").setDefault("string");
    options.add("int", "Default Int").setDefault<int>(42);
    options.add("double", "Default Double").setDefault<double>(99.5);
    options.add("bool", "Default Bool").setDefault<bool>(false);

    {
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>("test_cli"));
        argv.push_back(nullptr);
        Parser parser(options, argv.size() - 1, argv.data());

        const std::string results = test::stdout(parser);
        const std::string expected =
                "ParseDefaults:\n"
                "  -h [ --help ]          Produces this help message\n"
                "  --string arg (=string) Default String\n"
                "  --int arg (=42)        Default Int\n"
                "  --double arg (=99.5)   Default Double\n"
                "  --bool arg (=false)    Default Bool\n";

        EXPECT_EQ(expected, results);

        EXPECT_FALSE(parser.get<bool>("help"));
        EXPECT_EQ("string", parser.get("string"));
        EXPECT_EQ(42, parser.get<int>("int"));
        EXPECT_EQ(99.5, parser.get<double>("double"));
        EXPECT_FALSE(parser.get<bool>("bool"));
    }

    {
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>("test_cli"));
        argv.push_back(const_cast<char*>("--string"));
        argv.push_back(const_cast<char*>("new string"));
        argv.push_back(const_cast<char*>("--int"));
        argv.push_back(const_cast<char*>("500"));
        argv.push_back(const_cast<char*>("--double"));
        argv.push_back(const_cast<char*>("500.25"));
        argv.push_back(const_cast<char*>("--bool"));
        argv.push_back(const_cast<char*>("true"));
        argv.push_back(nullptr);
        Parser parser(options, argv.size() - 1, argv.data());

        EXPECT_FALSE(parser.get<bool>("help"));
        EXPECT_EQ("new string", parser.get("string"));
        EXPECT_EQ(500, parser.get<int>("int"));
        EXPECT_EQ(500.25, parser.get<double>("double"));
        EXPECT_TRUE(parser.get<bool>("bool"));
    }
}

TEST(CommandLine, Set)
{
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("test_cli"));
    argv.push_back(const_cast<char*>("--value1"));
    argv.push_back(const_cast<char*>("value1"));
    argv.push_back(nullptr);

    Options options("Set");
    options.add("value1", "Some value");
    options.add("value2", "Some value");
    options.add("value3", "Some value").setDefault("value3");
    Parser parser(options, argv.size() - 1, argv.data());

    EXPECT_TRUE(parser.isSet("value1"));
    EXPECT_FALSE(parser.isSet("value2"));
    EXPECT_TRUE(parser.isSet("value3"));
}

TEST(CommandLine, Invalid)
{
    // Test missing positional value
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("test_cli"));
    argv.push_back(nullptr);

    Options options("Invalid");
    options.add("input", "Some input");
    Parser parser(options, argv.size() - 1, argv.data());

    EXPECT_ANY_THROW(parser.get("input"));
}
}
}

NYRA_TEST()
