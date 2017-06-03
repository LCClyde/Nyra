#ifndef __SHMUP_UTILS_H__
#define __SHMUP_UTILS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>

void normalize(sf::Vector2f& vec);

sf::Vector2f rotate(const sf::Vector2f& vec, float degrees);

#endif
