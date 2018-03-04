/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <random>
#include <iostream>
#include <exception>
#include <nyra/cli/Parser.h>
#include <nyra/process/Hijack.h>
#include <nyra/poke/Simulator.h>
#include <nyra/core/Time.h>

using namespace nyra;

namespace
{
bool run(const std::string& binaryPathname,
         const std::string& gamePathname)
{
    poke::Simulator simulator(binaryPathname, gamePathname);
    img::Image stuck = core::read<img::Image>("stuck_game.png");
    if (stuck == simulator.screenshot())
    {
        std::cout << "The game was stuck, resetting\n";
        return false;
    }

    const size_t waitTime = 2500;

    std::random_device rdev;
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution<size_t> idist(waitTime, waitTime + 2500);

    // Interact with pokeball
    // Adds some randomness just to keep things different each run
    core::sleep(idist(rgen));
    simulator.pressA();
    std::cout << "Interacted with pokeball\n";

    // Skip first text
    core::sleep(waitTime);
    simulator.pressA();
    std::cout << "Skipped text\n";

    // Accept the pokemon
    core::sleep(waitTime);
    simulator.pressA();
    std::cout << "Accepted pokemon\n";

    // Skip the next text
    core::sleep(waitTime + 1000);
    simulator.pressA();
    std::cout << "Skipped text\n";

    // Don't change his name
    core::sleep(waitTime + 2500);
    simulator.pressB();
    std::cout << "Did not change name\n";

    // Skip rival text
    core::sleep(waitTime);
    simulator.pressA();
    std::cout << "Skipped text\n";

    // Open menu
    core::sleep(waitTime);
    simulator.pressStart();
    std::cout << "Opened menu\n";

    // Select pokemon
    core::sleep(1500);
    simulator.pressA();
    std::cout << "Selected pokemon\n";

    // Select squirtle
    core::sleep(1500);
    simulator.pressA();
    std::cout << "Selected squirtle\n";

    // Select summary
    core::sleep(1500);
    simulator.pressA();
    std::cout << "Selected summary\n";

    // Check screenshot
    core::sleep(waitTime);
    img::Image screenshot = simulator.screenshot(
            math::Vector2U(8, 35),
            math::Vector2U(90, 55));
    img::Image notShiny = core::read<img::Image>("squirtle.png");
    std::cout << "Took screenshot\n";

    if (screenshot != notShiny)
    {
        std::cout << "FOUND SHINY\n";
        core::sleep(500);
        simulator.saveAll();

        // Just stay here forever
        while (true)
        {
        }
        return true;
    }

    core::sleep(500);

    std::cout << "Not shiny\n";
    return false;
}
}

int main(int argc, char** argv)
{
    try
    {
        cli::Options opt("Includes ways to try to automate "
                         "waiting for shiny POKEMON");
        opt.add("game", "Specify the game pathname").setPositional();
        opt.add("vba", "Specify the location of "
                "the VisualBoyAdvanced pathname").
                        setDefault("/usr/bin/VisualBoyAdvance");
        cli::Parser options(opt, argc, argv);

        const std::string binaryPathname = options.get("vba");
        const std::string gamePathname = options.get("game");
        size_t iteration = 0;

        do
        {
            std::cout << "Starting iteration: " << iteration++ << "\n";
        }
        while (!run(binaryPathname, gamePathname));

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
