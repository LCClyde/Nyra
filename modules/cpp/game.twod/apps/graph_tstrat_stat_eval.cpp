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
#include <exception>
#include <vector>
#include <string>
#include <functional>
#include <nyra/game/twod/Stats.h>
#include <nyra/process/Subprocess.h>
#include <nyra/core/String.h>
#include <nyra/game/twod/StatEvaluator.h>

using namespace nyra;

namespace
{
//===========================================================================//
double getMovement(const game::twod::StatEvaluator& eval,
                   game::twod::Stats& stats)
{
    return eval.movement(stats.movement++);
}

//===========================================================================//
double getAgility(const game::twod::StatEvaluator& eval,
                  game::twod::Stats& stats)
{
    return eval.agility(stats.agility++);
}

//===========================================================================//
double getEvasionMelee(const game::twod::StatEvaluator& eval,
                       game::twod::Stats& stats)
{
    return eval.evasionMelee(stats.evasion++);
}

//===========================================================================//
double getEvasionRanged(const game::twod::StatEvaluator& eval,
                        game::twod::Stats& stats)
{
    return eval.evasionRanged(stats.evasion++);
}

//===========================================================================//
double getDexterity(const game::twod::StatEvaluator& eval,
                    game::twod::Stats& stats)
{
    return eval.dexterity(stats.dexterity++);
}

//===========================================================================//
double getStrength(const game::twod::StatEvaluator& eval,
                   game::twod::Stats& stats)
{
    return eval.strength(stats.strength++);
}

//===========================================================================//
double getConstitution(const game::twod::StatEvaluator& eval,
                       game::twod::Stats& stats)
{
    return eval.constitution(stats.constitution++);
}

//===========================================================================//
double getFortitude(const game::twod::StatEvaluator& eval,
                    game::twod::Stats& stats)
{
    return eval.fortitude(stats.fortitude++);
}

//===========================================================================//
double getStamina(const game::twod::StatEvaluator& eval,
                  game::twod::Stats& stats)
{
    return eval.stamina(stats.stamina++);
}

//===========================================================================//
double getPerception(const game::twod::StatEvaluator& eval,
                     game::twod::Stats& stats)
{
    return eval.perception(stats.perception++);
}

//===========================================================================//
double getSpeed(const game::twod::StatEvaluator& eval,
                game::twod::Stats& stats)
{
    return eval.speed(stats.speed++);
}

//===========================================================================//
double getLuck(const game::twod::StatEvaluator& eval,
               game::twod::Stats& stats)
{
    return eval.luck(stats.luck++);
}

//===========================================================================//
double getCharisma(const game::twod::StatEvaluator& eval,
                   game::twod::Stats& stats)
{
    return eval.charisma(stats.charisma++);
}

//===========================================================================//
double getBlock(const game::twod::StatEvaluator& eval,
                game::twod::Stats& stats)
{
    return eval.block(stats.block++);
}

//===========================================================================//
double getResolve(const game::twod::StatEvaluator& eval,
                  game::twod::Stats& stats)
{
    return eval.resolve(stats.resolve++);
}

//===========================================================================//
typedef std::function<double(const game::twod::StatEvaluator& eval,
                             game::twod::Stats& stats)> GetStatT;

//===========================================================================//
void graph(const game::twod::StatEvaluator& eval,
           const std::string& name,
           GetStatT getStat,
           int16_t min = 0,
           int16_t max = 100)
{
    ++max;
    game::twod::Stats stats;

    std::vector<double> values;
    for (int16_t ii = min; ii < max; ++ii)
    {
        values.push_back(getStat(eval, stats));
    }

    std::string list = "[";
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        if (ii != 0)
        {
            list += ",";
        }
        list += core::str::toString(values[ii]);
    }
    list += "]";

    const std::string script =
            "import matplotlib.pyplot as plt;"
            "import numpy as np;"
            "dim = range(" + core::str::toString(min) + ", " + core::str::toString(max) + ");"
            "plt.plot(dim, " + list + ");"
            "plt.title('" + name + "');"
            "plt.savefig('" + name + ".png')";
    std::cout << "\npython -c \"" + script << "\"\n\n";

    std::vector<std::string> args;
    args.push_back("-c");
    args.push_back(script);

    // TODO: This should be able run off the PATH.
    process::subprocess("/home/clyde/anaconda2/bin/python", args);
}
}

int main(int argc, char** argv)
{
    try
    {
        game::twod::StatEvaluator eval;
        graph(eval, "Movement", getMovement, 0, 5);
        graph(eval, "Agility", getAgility);
        graph(eval, "Melee Evasion", getEvasionMelee);
        graph(eval, "Ranged Evasion", getEvasionRanged);
        graph(eval, "Dexterity", getDexterity);
        graph(eval, "Strength", getStrength);
        graph(eval, "Constitution", getConstitution, 10, 20);
        graph(eval, "Fortitude", getFortitude);
        graph(eval, "Stamina", getStamina);
        graph(eval, "Perception", getPerception, 0, 5);
        graph(eval, "Speed", getSpeed);
        graph(eval, "Luck", getLuck);
        graph(eval, "Charisma", getCharisma);
        graph(eval, "Block", getBlock);
        graph(eval, "Resolve", getResolve);
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
