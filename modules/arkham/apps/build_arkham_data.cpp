/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <exception>
#include <vector>
#include <nyra/cli/Parser.h>
#include <nyra/net/Browser.h>
#include <nyra/core/Path.h>
#include <nyra/xml/XML.h>
#include <nyra/arkham/Location.h>
#include <nyra/arkham/Encounter.h>
#include <nyra/core/Regex.h>
#include <nyra/img/Algs.h>
#include <nyra/process/Subprocess.h>
#include <nyra/core/File.h>

using namespace nyra;

//===========================================================================//
static const std::string URL = "http://www.arkhamhorrorwiki.com";

//===========================================================================//
std::vector<arkham::Location> getLocations(net::Browser& browser)
{
    const xml::XML locationsXML(browser.get(URL + "/Location"));

    const auto& table = locationsXML["html"]["body"]["div"]["div"][0]
                                    ["div"]["div"]["div"][3]["table"]["tr"];

    std::vector<arkham::Location> locations;
    for (size_t ii = 1; ii < table.loopSize(); ++ii)
    {
        const std::string name = table[ii]["td"][0]["a"].get().text;
        std::string expansion = "";

        if (table[ii]["td"][5].has("a"))
        {
            // TODO: I don't think the XML was read correctly here. The
            //       attributes do not seem to be in the right spot.
            expansion = table[ii]["td"][5]["a"].get().attributes.at("title");
        }

        locations.push_back(arkham::Location(name, expansion));
    }

    return locations;
}

//===========================================================================//
std::vector<arkham::Encounter> getEncounters(const std::string& locationIn,
                                             net::Browser& browser)
{
    std::string location = core::str::findAndReplace(locationIn, " ", "_");
    location = browser.encode(location);
    std::vector<arkham::Encounter> encounters;

    const std::string xmlText = browser.get(URL + "/" + location);

    // The html has embedded links that are not structured well. So I will
    // manually pull out the values I need.
    std::string regex = "(<tr>\\n<td>(\\s|.)*?\n<\\/td>)";
    const std::vector<std::string> text = core::regexMatches(xmlText, regex);
    std::vector<std::string> finalText;

    for (size_t ii = 0; ii < text.size(); ++ii)
    {
        regex = "\\>(.*?)[\\<\\n]";
        const std::vector<std::string> parts = core::regexMatches(text[ii], regex);
        std::string newText = "";
        for (const std::string& part : parts)
        {
            newText += part;
        }

        // This finds too many entries and some of them are not correct.
        // These will show up as empty strings here and we just ignore
        // them.
        if (!newText.empty())
        {
            finalText.push_back(newText);
        }
    }

    const xml::XML tree(xmlText);

    const auto& findTable = tree["html"]["body"]["div"]["div"][0]
                                ["div"]["div"]["div"];
    for (size_t ii = 0; ii < findTable.loopSize(); ++ii)
    {
        if (findTable[ii].has("table"))
        {
            const auto& table = findTable[ii]["table"]["tr"];
            const size_t tableSize = table.loopSize();

            // There should be as many entries as we have text
            if (tableSize - 1 != finalText.size())
            {
                throw std::runtime_error(
                        "The number of regex text was incorrect. We found " +
                        core::str::toString(finalText.size()) +
                        " entries there should be " +
                        core::str::toString(tableSize - 1) + ". " +
                        "For entry: " + locationIn);
            }

            for (size_t jj = 1; jj < tableSize; ++jj)
            {
                std::string exp = "";
                const auto& expTree = table[jj]["td"][2];
                if (expTree.has("a"))
                {
                    // There can be multiple "a" entries. Just take
                    // the last one
                    exp = expTree["a"][expTree["a"].loopSize() - 1].
                            get().attributes.at("title");
                }
                encounters.push_back(arkham::Encounter(finalText[jj - 1], exp));
            }
        }
    }
    return encounters;
}

//===========================================================================//
std::vector<arkham::Location> getOtherWorldLocations(net::Browser& browser)
{
    std::vector<arkham::Location> locations;
    const xml::XML tree(browser.get(URL + "/Other_World"));
    core::write(tree, "xml.xml");

    const auto& table = tree["html"]["body"]["div"]["div"][0]
                            ["div"]["div"]["div"][3]["table"]["tr"];

    for (size_t ii = 1; ii < table.loopSize(); ++ii)
    {
        const std::string name = table[ii]["td"][0]["a"].get().text;
        const std::string blue = table[ii]["td"][1].get().text;
        const std::string green = table[ii]["td"][2].get().text;
        const std::string red = table[ii]["td"][3].get().text;
        const std::string yellow = table[ii]["td"][4].get().text;

        std::string exp;
        if (table[ii]["td"][5].has("a"))
        {
            // TODO: I don't think the XML was read correctly here. The
            //       attributes do not seem to be in the right spot.
            exp = table[ii]["td"][5]["a"].get().attributes.at("title");
        }

        locations.push_back(arkham::Location(name, exp,
                                             !blue.empty(),
                                             !green.empty(),
                                             !red.empty(),
                                             !yellow.empty()));
    }
    return locations;
}

//===========================================================================//
std::vector<std::unordered_map<std::string, arkham::Encounter>>
getOtherWorldEncounter(size_t start, size_t end,
                       const std::vector<arkham::Location>& locations,
                       net::Browser& browser)
{
    std::vector<std::unordered_map<std::string, arkham::Encounter>> encounters;
    const std::string urlPrefix = URL + "/wiki/images/";
    const std::string pathname = "gate.png";
    for (size_t ii = start; ii < end + 1; ++ii)
    {
        const std::string fullUrl =
                urlPrefix + "Gate" + core::str::toString(ii) + ".png";
        browser.download(fullUrl, pathname);
        img::Image image = core::read<img::Image>(pathname);
        image = img::resize(image, image.getSize() * 6);
        image = img::threshold(image, 180);
        const math::Vector2U offset(240, 240);
        const math::Vector2U extents = image.getSize() - (offset * 2);
        image = img::crop(image, offset, extents);
        core::write(image, pathname);
        process::subprocess("/usr/bin/tesseract", {"gate.png", "results"});
        std::vector<std::string> results = core::str::split(
                core::readFile("results.txt"), "\n");

        size_t line = 0;
        for (size_t entry = 0; entry < 3; ++entry)
        {
            std::string text;

            // Increment until we find content
            while (results[line].empty())
            {
                ++line;
            }

            // First line is the location
            std::string location  = results[line++];

            // Increment until we find content
            while (results[line].empty())
            {
                ++line;
            }

            while (line < results.size() && !results[line].empty())
            {
                text += results[line++] + " ";
            }

            std::cout << location << "\n" << text << "\n\n";
        }
    }
    return encounters;
}

//===========================================================================//
int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Creates the Arkham Horror data files");
        cli::Parser options(opt, argc, argv);

        net::Browser browser(100);

        /*std::cout << "Obtaining locations list";
        const std::vector<arkham::Location> locations =
                getLocations(browser);
        std::cout << " Found " << locations.size() << " locations.\n";

        std::unordered_map<std::string, std::vector<arkham::Encounter>> encounters;
        for (const auto& loc : locations)
        {
            // TODO: Wizard's Hill was not up when I was creating this.
            if (loc.name != "Wizard's Hill")
            {
                std::cout << "Building encounters for: " << loc.name;
                encounters[loc.name] = getEncounters(loc.name, browser);
                std::cout << ". Found " << encounters[loc.name].size() << " encounters.\n";
            }
            else
            {
                std::cout << "WARNING: " << loc.name << " was not included\n";
            }
        }

        const std::string outDir = core::path::join(
                core::INSTALL_PATH, "../modules/arkham/data/serial/");
        const std::string locPathname =
                core::path::join(outDir, "arkham_locations.txt");
        const std::string encPathname =
                core::path::join(outDir, "arkham_encounters.txt");*/

        getOtherWorldLocations(browser);
        getOtherWorldEncounter(1, 48, browser);

        /*core::write(locations, locPathname);
        std::cout << "Wrote locations to " << locPathname << "\n";
        core::write(encounters, encPathname);
        std::cout << "Wrote encounters to " << encPathname << "\n";*/
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
    }

    return 0;
}
