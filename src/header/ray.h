#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <stdio.h>
#include <math.h>
#include <utility>
#include <array>
#include <iostream>
#include "map.h"
#include "rcvector.h"

namespace rc
{
    class RayHandler
    {

    private:

        const float TWO_THIRDS = 0.66;

        const Map& wallMap;
        sf::RenderWindow& window;
        const Vector2f SCREEN_SIZE;
        const float TILE_SIZE;
        const float GUI_SCALE;
        const float START_POS_X;
        const Color RAY_COLOR_2D;
        const Color RAY_IMPACT_COLOR_2D;

        sf::RectangleShape vertBar;
        sf::RectangleShape floor;
        sf::CircleShape hitCircle;

        std::vector<sf::VertexArray> rayVector2d;

        void drawFloor(const float verticalPixelOffset);

        Vector2f toTileCoords(const Vector2f& screenPos) const;

        float getVerticalPixelOffset(const float playerAngleVertical) const;

        std::tuple<Vector2f, float> setUpRayAngle(const Vector2f& playerDir, const Vector2f& plane, const int x) const;

        static Vector2f getStepSize(const Vector2f& rayDir);

        static Vector2i getStep(const Vector2f& rayDir);

        Vector2f getInitialRayLength1d(const Vector2f& rayDir, const Vector2f& rayOrigin, const Vector2i& mapPos, const Vector2f& stepSize) const;

        std::tuple<Color, Vector2f, bool> castRayUntilHit(const Vector2f& rayLength1dInit, const Vector2i& mapPosInit, const Vector2f& stepSize, const Vector2i& step) const;

        float getRayDistPerpendicular(const Vector2f& rayLength1d, const Vector2f& stepSize, const bool side) const;

        void shadeColor(Color& color, const float rayDistPerpendicular, const bool side) const;

        void drawVerticalBar3d(Color& color, const float rayDistPerpendicular, const float angleOffset, const float verticalPixelOffset, int x);

        Vector2f getHitPos(const Vector2f& rayOrigin, const Vector2f& rayDir, const float rayDistPerpendicular, const float angleOffset) const;

        sf::VertexArray getRayLine2d(const Vector2f& rayOrigin, const Vector2f& hitPos) const;

        void draw2dRayLines();

    public:

        RayHandler(const Map& wallMap, sf::RenderWindow& window, const float GUI_SCALE);

        void render(const Vector2f screenPos, const Vector2f playerDir, const float playerAngleVertical);
    };

}