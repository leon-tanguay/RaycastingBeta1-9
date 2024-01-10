#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>
#include <utility>
#include <array>

namespace hueShift
{
    const double pi = atan(1) * 4;

    sf::Uint8 clampColor(double v);

    double degreesToRadians(double degrees);

    sf::Color hueShift(const sf::Color& color, double degrees);
}