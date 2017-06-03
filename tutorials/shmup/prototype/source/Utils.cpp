#define _USE_MATH_DEFINES
#include <cmath>
#include "Utils.h"

void normalize(sf::Vector2f& vec)
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length == 0.0f)
    {
        return;
    }
    vec /= length;
}

sf::Vector2f rotate(const sf::Vector2f& vec, float degrees)
{
    const float radians = degrees * (M_PI / 180.0f);
    sf::Vector2f ret;
    ret.x = vec.x * std::cos(radians) - vec.y * std::sin(radians);
    ret.y = vec.x * std::sin(radians) + vec.y * std::sin(radians);
    return ret;
}
