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
#ifndef __NYRA_GAME_TSTRAT_STATS_H__
#define __NYRA_GAME_TSTRAT_STATS_H__

#include <stdint.h>
#include <nyra/core/Archive.h>
#include <nyra/core/Random.h>

namespace nyra
{
namespace game
{
namespace twod
{
/*
 *  \class Stats
 *  \brief Holds onto character status used to effect gameplay.
 */
struct Stats
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up zero'd out stats.
     */
    Stats();

    /*
     *  \var movement
     *  \brief The number of tiles you can move.
     */
    int16_t movement;

    /*
     *  \var agility
     *  \brief Ranged accuracy
     */
    int16_t agility;

    /*
     *  \var evasion
     *  \brief Dodge chance
     */
    int16_t evasion;

    /*
     *  \var dexterity
     *  \brie Critical hit chance
     */
    int16_t dexterity;

    /*
     *  \var strength
     *  \brief Melee and thrown weapon damage
     */
    int16_t strength;

    /*
     *  \var constitution
     *  \brief Hit points
     */
    int16_t constitution;

    /*
     *  \var fortitude
     *  \brief Physical damage resistance
     */
    int16_t fortitude;

    /*
     *  \var stamina
     *  \brief Your ability to take actions
     */
    int16_t stamina;

    /*
     *  \var perception
     *  \brief How far you can fee into the fog of war
     */
    int16_t perception;

    /*
     *  \var speed
     *  \brief Sets turn order.
     */
    int16_t speed;

    /*
     *  \var luck
     *  \brief Slightly affects everything
     */
    int16_t luck;

    /*
     *  \var charisma
     *  \brief Your ability to influence other characters
     */
    int16_t charisma;

    /*
     *  \var block
     *  \brief Chance to stop an attack
     */
    int16_t block;

    /*
     *  \var resolve
     *  \brief Mental resistance against fear and intimidation
     */
    int16_t resolve;

    /*
     *  \func getDefaultDistribution
     *  \brief Gets the default stat distribution randomizer.
     *
     *  \return The distribution
     */
    static
    const core::RandomNormal<int16_t>& getDefaultDistribution()
    {
        return mDefaultDistribution;
    }

private:
    NYRA_SERIALIZE()

    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & BOOST_SERIALIZATION_NVP(movement);
        archive & BOOST_SERIALIZATION_NVP(agility);
        archive & BOOST_SERIALIZATION_NVP(evasion);
        archive & BOOST_SERIALIZATION_NVP(dexterity);
        archive & BOOST_SERIALIZATION_NVP(strength);
        archive & BOOST_SERIALIZATION_NVP(constitution);
        archive & BOOST_SERIALIZATION_NVP(fortitude);
        archive & BOOST_SERIALIZATION_NVP(stamina);
        archive & BOOST_SERIALIZATION_NVP(perception);
        archive & BOOST_SERIALIZATION_NVP(speed);
        archive & BOOST_SERIALIZATION_NVP(luck);
        archive & BOOST_SERIALIZATION_NVP(charisma);
        archive & BOOST_SERIALIZATION_NVP(block);
        archive & BOOST_SERIALIZATION_NVP(resolve);
    }

    friend std::ostream& operator<<(std::ostream& os, const Stats& stats);

    static core::RandomNormal<int16_t> mDefaultDistribution;
};
}
}
}

#endif
