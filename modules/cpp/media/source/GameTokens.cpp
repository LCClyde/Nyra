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
#include <unordered_map>
#include <nyra/media/GameTokens.h>
#include <nyra/core/Regex.h>
#include <nyra/core/String.h>

namespace
{
//===========================================================================//
static const std::unordered_map<std::string, nyra::media::GameTokens::Country>
CODE_TO_COUNTRY = {{"(1)", nyra::media::GameTokens::JAPAN_AND_KOREA},
                   {"(4)", nyra::media::GameTokens::USA_AND_BRAZIL},
                   {"(A)", nyra::media::GameTokens::AUSTRALIA},
                   {"(J)", nyra::media::GameTokens::JAPAN},
                   {"(B)", nyra::media::GameTokens::NON_USA},
                   {"(K)", nyra::media::GameTokens::KOREA},
                   {"(C)", nyra::media::GameTokens::CHINA},
                   {"(NL)", nyra::media::GameTokens::NETHERLANDS},
                   {"(E)", nyra::media::GameTokens::EUROPE},
                   {"(PD)", nyra::media::GameTokens::PUBLIC_DOMAIN},
                   {"(F)", nyra::media::GameTokens::FRANCE},
                   {"(S)", nyra::media::GameTokens::SPAIN},
                   {"(FC)", nyra::media::GameTokens::FRENCH_CANADIAN},
                   {"(Sw)", nyra::media::GameTokens::SWEDEN},
                   {"(FN)", nyra::media::GameTokens::FINLAND},
                   {"(U)", nyra::media::GameTokens::USA},
                   {"(G)", nyra::media::GameTokens::GERMANY},
                   {"(UK)", nyra::media::GameTokens::ENGLAND},
                   {"(GR)", nyra::media::GameTokens::GREECE},
                   {"(Unk)", nyra::media::GameTokens::UNKNOWN_COUNTRY},
                   {"(HK)", nyra::media::GameTokens::HONG_KONG},
                   {"(I)", nyra::media::GameTokens::ITALY},
                   {"(D)", nyra::media::GameTokens::DUTCH},
                   {"(Unl)", nyra::media::GameTokens::UNLICENSED}};

//===========================================================================//
static const std::unordered_map<
        nyra::media::GameTokens::Country, std::string, std::hash<int> >
COUNTRY_TO_STRING = {{nyra::media::GameTokens::JAPAN_AND_KOREA, "Japan & Korea"},
                     {nyra::media::GameTokens::USA_AND_BRAZIL, "USA & Brazil"},
                     {nyra::media::GameTokens::AUSTRALIA, "Australia"},
                     {nyra::media::GameTokens::JAPAN, "Japan"},
                     {nyra::media::GameTokens::NON_USA, "Non USA"},
                     {nyra::media::GameTokens::KOREA, "Korea"},
                     {nyra::media::GameTokens::CHINA, "China"},
                     {nyra::media::GameTokens::NETHERLANDS, "Netherlands"},
                     {nyra::media::GameTokens::EUROPE, "Europe"},
                     {nyra::media::GameTokens::PUBLIC_DOMAIN, "Public Domain"},
                     {nyra::media::GameTokens::FRANCE, "France"},
                     {nyra::media::GameTokens::SPAIN, "Spain"},
                     {nyra::media::GameTokens::FRENCH_CANADIAN, "French Canadian"},
                     {nyra::media::GameTokens::SWEDEN, "Sweden"},
                     {nyra::media::GameTokens::FINLAND, "Finland"},
                     {nyra::media::GameTokens::USA, "USA"},
                     {nyra::media::GameTokens::GERMANY, "Germany"},
                     {nyra::media::GameTokens::ENGLAND, "England"},
                     {nyra::media::GameTokens::GREECE, "Greece"},
                     {nyra::media::GameTokens::UNKNOWN_COUNTRY, "Unknown"},
                     {nyra::media::GameTokens::HONG_KONG, "Hong Kong"},
                     {nyra::media::GameTokens::ITALY, "Italy"},
                     {nyra::media::GameTokens::DUTCH, "Dutch"},
                     {nyra::media::GameTokens::UNLICENSED, "Unlicensed"}};

//===========================================================================//
nyra::media::GameTokens::Country getCountry(const std::string& code)
{
    const auto iter = CODE_TO_COUNTRY.find(code);
    if (iter == CODE_TO_COUNTRY.end())
    {
        return nyra::media::GameTokens::ERROR;
    }

    return iter->second;
}
}

namespace nyra
{
namespace media
{
//===========================================================================//
GameTokens::GameTokens() :
    mVersion(0.0),
    mVerifiedGoodDump(false),
    mCountry(UNKNOWN_COUNTRY)
{
}

//===========================================================================//
GameTokens::GameTokens(const std::string& filename) :
    GameTokens()
{
    initialize(filename);
}

//===========================================================================//
void GameTokens::initialize(const std::string& filename)
{
    const static std::regex REGEX("([(\\[].*?[)\\]])");
    const std::vector<std::string> tokens =
            core::regexMatches(filename, REGEX);

    for (const std::string& token : tokens)
    {
        try
        {
            const std::string substr =
                    token.substr(2, token.size() - 3);
            switch (token[0])
            {
            case '[':
            {
                switch (token[1])
                {
                case 'b':
                    mBadDump = substr;
                    break;
                case 'a':
                    mAlternative = substr;
                    break;
                case 'f':
                    mFixed = substr;
                    break;
                case 'o':
                    mOverdump = substr;
                    break;
                case 't':
                    mTrainer = substr;
                    break;
                case 'p':
                    mPirate = substr;
                    break;
                case 'h':
                    mHack = substr;
                    break;
                case '!':
                    mVerifiedGoodDump = true;
                    break;
                case 'T':
                    if (substr[0] == '-')
                    {
                        mOldTranslation = substr.substr(1, substr.size() - 1);
                    }
                    else if (substr[0] == '+')
                    {
                        mNewTranslation = substr.substr(1, substr.size() - 1);
                    }
                    else
                    {
                        mMisc.push_back(token);
                    }
                    break;
                default:
                    mMisc.push_back(token);
                    break;
                }
                break;
            }

            case '(':
            {
                switch (token[1])
                {
                case 'V':
                    mVersion = core::str::toType<double>(substr);
                    break;
                default:
                    {
                        const Country country = getCountry(token);
                        if (country != Country::ERROR)
                        {
                            mCountry = country;
                        }
                        else
                        {
                            mMisc.push_back(token);
                        }
                        break;
                    }
                }
                break;
            }
            default:
                mMisc.push_back(token);
                break;
            }

        }
        catch (...)
        {
            mMisc.push_back(token);
        }
    }
}

//===========================================================================//
size_t GameTokens::countUnsortedTokens() const
{
    return static_cast<size_t>(!mAlternative.empty()) +
           static_cast<size_t>(!mFixed.empty()) +
           static_cast<size_t>(!mOverdump.empty()) +
           static_cast<size_t>(!mHack.empty()) +
           static_cast<size_t>(!mPirate.empty()) +
           static_cast<size_t>(!mTrainer.empty()) +
           static_cast<size_t>(!mOldTranslation.empty()) +
           static_cast<size_t>(!mNewTranslation.empty()) +
           mMisc.size();
}

//===========================================================================//
bool GameTokens::operator<(const GameTokens& other) const
{
    // Prefer verified roms
    if (mVerifiedGoodDump != other.mVerifiedGoodDump)
    {
        return mVerifiedGoodDump;
    }

    // Move newer versions to the front
    if (mVersion != other.mVersion)
    {
        return mVersion > other.mVersion;
    }

    // Get rid of bad dumps
    if (mBadDump.empty() != other.mBadDump.empty())
    {
        return mBadDump.empty();
    }

    // If something has more tokens it is probably something weird
    const size_t thisTokens = countUnsortedTokens();
    const size_t otherTokens = other.countUnsortedTokens();

    if (thisTokens != otherTokens)
    {
        return thisTokens < otherTokens;
    }

    return mCountry < other.mCountry;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os,
                         const GameTokens& tokens)
{
    os << "Country: " << COUNTRY_TO_STRING.at(tokens.mCountry);

    if (tokens.mVerifiedGoodDump)
    {
        os << "\nVerified Good";
    }

    if (tokens.mVersion != 0.0)
    {
        os << "\nVersion: " << tokens.mVersion;
    }

    if (!tokens.mHack.empty())
    {
        os << "\nHack: " << tokens.mHack;
    }

    if (!tokens.mFixed.empty())
    {
        os << "\nFixed: " << tokens.mFixed;
    }

    if (!tokens.mAlternative.empty())
    {
        os << "\nAlternative: " << tokens.mAlternative;
    }

    if (!tokens.mOverdump.empty())
    {
        os << "\nOverdump: " << tokens.mOverdump;
    }

    if (!tokens.mTrainer.empty())
    {
        os << "\nTrainer: " << tokens.mTrainer;
    }

    if (!tokens.mPirate.empty())
    {
        os << "\nPirated: " << tokens.mPirate;
    }

    if (!tokens.mBadDump.empty())
    {
        os << "\nBad Dump: " << tokens.mBadDump;
    }

    if (!tokens.mNewTranslation.empty())
    {
        os << "\nNew Translation: " << tokens.mNewTranslation;
    }

    if (!tokens.mOldTranslation.empty())
    {
        os << "\nOld Translation: " << tokens.mOldTranslation;
    }

    if (!tokens.mMisc.empty())
    {
        os << "\nMiscellaneous Codes:";
        for (const std::string& misc : tokens.mMisc)
        {
            os << "\n    " << misc;
        }
    }

    return os;
}
}
}
