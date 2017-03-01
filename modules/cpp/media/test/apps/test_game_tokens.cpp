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
#include <nyra/media/GameTokens.h>

//===========================================================================//
nyra::media::GameTokens make(const std::string& filename)
{
    nyra::media::GameTokens tokens;
    tokens.initialize(filename);
    return tokens;
}

namespace nyra
{
namespace media
{
//===========================================================================//
TEST(GameTokens, Country)
{
    GameTokens token;

    token = make("Sample Game (1).bin");
    EXPECT_EQ("Country: Japan & Korea", test::stdout(token));
    token = make("Sample Game (A).bin");
    EXPECT_EQ("Country: Australia", test::stdout(token));
    token = make("Sample Game (B).bin");
    EXPECT_EQ("Country: Non USA", test::stdout(token));
    token = make("Sample Game (C).bin");
    EXPECT_EQ("Country: China", test::stdout(token));
    token = make("Sample Game (E).bin");
    EXPECT_EQ("Country: Europe", test::stdout(token));
    token = make("Sample Game (F).bin");
    EXPECT_EQ("Country: France", test::stdout(token));
    token = make("Sample Game (FC).bin");
    EXPECT_EQ("Country: French Canadian", test::stdout(token));
    token = make("Sample Game (FN).bin");
    EXPECT_EQ("Country: Finland", test::stdout(token));
    token = make("Sample Game (G).bin");
    EXPECT_EQ("Country: Germany", test::stdout(token));
    token = make("Sample Game (GR).bin");
    EXPECT_EQ("Country: Greece", test::stdout(token));
    token = make("Sample Game (HK).bin");
    EXPECT_EQ("Country: Hong Kong", test::stdout(token));
    token = make("Sample Game (D).bin");
    EXPECT_EQ("Country: Dutch", test::stdout(token));
    token = make("Sample Game (4).bin");
    EXPECT_EQ("Country: USA & Brazil", test::stdout(token));
    token = make("Sample Game (J).bin");
    EXPECT_EQ("Country: Japan", test::stdout(token));
    token = make("Sample Game (K).bin");
    EXPECT_EQ("Country: Korea", test::stdout(token));
    token = make("Sample Game (NL).bin");
    EXPECT_EQ("Country: Netherlands", test::stdout(token));
    token = make("Sample Game (PD).bin");
    EXPECT_EQ("Country: Public Domain", test::stdout(token));
    token = make("Sample Game (S).bin");
    EXPECT_EQ("Country: Spain", test::stdout(token));
    token = make("Sample Game (Sw).bin");
    EXPECT_EQ("Country: Sweden", test::stdout(token));
    token = make("Sample Game (U).bin");
    EXPECT_EQ("Country: USA", test::stdout(token));
    token = make("Sample Game (UK).bin");
    EXPECT_EQ("Country: England", test::stdout(token));
    token = make("Sample Game (Unk).bin");
    EXPECT_EQ("Country: Unknown", test::stdout(token));
    token = make("Sample Game (I).bin");
    EXPECT_EQ("Country: Italy", test::stdout(token));
    token = make("Sample Game (Unl).bin");
    EXPECT_EQ("Country: Unlicensed", test::stdout(token));
    token = make("Sample Game.bin");
    EXPECT_EQ("Country: Unknown", test::stdout(token));
    token = make("Sample Game (foo).bin");
    EXPECT_EQ("Country: Unknown\n"
              "Miscellaneous Codes:\n"
              "    (foo)",
              test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Hack)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Hack: ";


    token = make("Sample Game (U) [h1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [h2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [h1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [hfoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Fixed)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Fixed: ";


    token = make("Sample Game (U) [f1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [f2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [f1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [ffoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Alternative)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Alternative: ";


    token = make("Sample Game (U) [a1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [a2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [a1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [afoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Overdump)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Overdump: ";


    token = make("Sample Game (U) [o1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [o2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [o1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [ofoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Trainer)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Trainer: ";


    token = make("Sample Game (U) [t1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [t2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [t1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [tfoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Pirated)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Pirated: ";


    token = make("Sample Game (U) [p1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [p2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [p1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [pfoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, BadDump)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Bad Dump: ";


    token = make("Sample Game (U) [b1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [b2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [b1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [bfoo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, OldTranslation)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Old Translation: ";


    token = make("Sample Game (U) [T-1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [T-2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [T-1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [T-foo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, NewTranslation)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "New Translation: ";


    token = make("Sample Game (U) [T+1].bin");
    EXPECT_EQ(expected + "1", test::stdout(token));
    token = make("Sample Game (U) [T+2].bin");
    EXPECT_EQ(expected + "2", test::stdout(token));
    token = make("Sample Game (U) [T+1000].bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
    token = make("Sample Game (U) [T+foo].bin");
    EXPECT_EQ(expected + "foo", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, Version)
{
    GameTokens token;
    const std::string expected =
            "Country: USA\n"
            "Version: ";


    token = make("Sample Game (U) (V1.1).bin");
    EXPECT_EQ(expected + "1.1", test::stdout(token));
    token = make("Sample Game (U) (V1.2).bin");
    EXPECT_EQ(expected + "1.2", test::stdout(token));
    token = make("Sample Game (U) (V1000).bin");
    EXPECT_EQ(expected + "1000", test::stdout(token));
}

//===========================================================================//
TEST(GameTokens, LessThan)
{
    GameTokens token1;
    GameTokens token2;

    token1 = make("Sample Game (U) [!].bin");

    EXPECT_TRUE(token1 < token2);
    EXPECT_FALSE(token2 < token1);
    EXPECT_FALSE(token1 < token1);
    EXPECT_FALSE(token2 < token1);
}
}
}

NYRA_TEST()
