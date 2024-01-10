#include "header/hueShift.h"

//https://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color

namespace hueShift
{
    //clamps double of r g or b value between 0-255, may cause approximation errors in the coloring
    sf::Uint8 clampColor(double v)
    {
        if (v < 0)
            return (sf::Uint8)0;
        if (v > 255)
            return (sf::Uint8)255;
        return static_cast<sf::Uint8>(v + 0.5f);
    }

    //converts degrees to radians with simple math
    double degreesToRadians(double degrees)
    {
        double returnVal = degrees * (pi / 180.0f);
        return returnVal;
    }

    //https://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color
    //simulates a cube with a matrix, and rotates it by the amount of degrees provided
    //returns a new sf::Color with the rotated rgb values, maintains the alpha from the old color
    sf::Color hueShift(const sf::Color& color, double degrees)
    {
        std::array<std::array<double, 3>, 3> colorMatrix{ { { {1.,0.,0.} }, { {0.,1.,0.} }, { {0.,0.,1.} } } };

        auto cosA = cos(degreesToRadians(degrees));
        auto sinA = sin(degreesToRadians(degrees));

        colorMatrix[0][0] = cosA + (1.0 - cosA) / 3.0;
        colorMatrix[0][1] = 1. / 3. * (1.0 - cosA) - sqrt(1. / 3.) * sinA;
        colorMatrix[0][2] = 1. / 3. * (1.0 - cosA) + sqrt(1. / 3.) * sinA;
        colorMatrix[1][0] = 1. / 3. * (1.0 - cosA) + sqrt(1. / 3.) * sinA;
        colorMatrix[1][1] = cosA + 1. / 3. * (1.0 - cosA);
        colorMatrix[1][2] = 1. / 3. * (1.0 - cosA) - sqrt(1. / 3.) * sinA;
        colorMatrix[2][0] = 1. / 3. * (1.0 - cosA) - sqrt(1. / 3.) * sinA;
        colorMatrix[2][1] = 1. / 3. * (1.0 - cosA) + sqrt(1. / 3.) * sinA;
        colorMatrix[2][2] = cosA + 1. / 3. * (1.0 - cosA);

        double curRed = (double)color.r;
        double curGreen = (double)color.g;
        double curBlue = (double)color.b;

        double newRed = curRed * colorMatrix[0][0] + curGreen * colorMatrix[0][1] + curBlue * colorMatrix[0][2];
        double newGreen = curRed * colorMatrix[1][0] + curGreen * colorMatrix[1][1] + curBlue * colorMatrix[1][2];
        double newBlue = curRed * colorMatrix[2][0] + curGreen * colorMatrix[2][1] + curBlue * colorMatrix[2][2];

        return sf::Color{ clampColor(newRed), clampColor(newGreen), clampColor(newBlue), color.a };
    }
}
