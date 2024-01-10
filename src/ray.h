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
#include "hueShift.h"
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
        const Color RAY_COLOR_IMPACT_CIRCLE_2D;

        sf::RectangleShape vertBar;
        sf::RectangleShape floor;
        sf::CircleShape hitCircle;
        
        std::vector<sf::VertexArray> rayVector2d;

    public:
        RayHandler(const Map& wallMap, sf::RenderWindow& window, const float GUI_SCALE) : 
            window(window), 
            wallMap(wallMap), 
            TILE_SIZE(wallMap.getTileSizeF()), 
            SCREEN_SIZE{static_cast<float>(window.getSize().x), 
            static_cast<float>(window.getSize().y)},
            floor{ Vector2f{SCREEN_SIZE.x / 2.f, SCREEN_SIZE.y / 2.f} }, 
            GUI_SCALE(GUI_SCALE), 
            START_POS_X(SCREEN_SIZE.x* (1.f - GUI_SCALE) + GUI_SCALE),
            RAY_COLOR_2D(Color::Green), 
            RAY_COLOR_IMPACT_CIRCLE_2D(Color::White),
            hitCircle{ 2 }
        {
            floor.setFillColor(Color::Green);
            hitCircle.setOrigin(1, 1);
        }

        void drawFloor(const float verticalPixelOffset)
        {
            floor.setSize(Vector2f(SCREEN_SIZE.x, SCREEN_SIZE.y / 2 - verticalPixelOffset));
            floor.setPosition(Vector2f(0.f, SCREEN_SIZE.y / 2 + verticalPixelOffset));
            window.draw(floor);
        }

        Vector2f toTileCoords(const Vector2f& screenPos) const
        {
            return screenPos / TILE_SIZE;
        }

        float getVerticalPixelOffset(const float playerAngleVertical) const
        {
            return (SCREEN_SIZE.y / 90.f) * playerAngleVertical;
        }

        std::tuple<Vector2f, float> setUpRayAngle(const Vector2f& playerDir, const Vector2f& plane, const int x) const
        {
            const float cameraX = 2.f * static_cast<float>(x) / static_cast<float>(SCREEN_SIZE.x) - 1.f;
            Vector2f rayDir{ playerDir.x + plane.x * cameraX , playerDir.y + plane.y * cameraX };
            float angleOffset = (atan(rayDir.y / rayDir.x) - atan(playerDir.y / playerDir.x));
            return { rayDir, angleOffset };
        }
        
        Vector2f getStepSize(const Vector2f& rayDir) const
        {
            return Vector2f{ sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)),
                    sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y)) };
        }
        
        Vector2i getStep(const Vector2f& rayDir) const
        {
            Vector2i step;
            if (rayDir.x < 0)
            {
                step.x = -1;
            }
            else
            {
                step.x = 1;
            }
            if (rayDir.y < 0)
            {
                step.y = -1;
            }
            else
            {
                step.y = 1;
            }
            return step;
        }

        Vector2f getInitialRayLength1d(const Vector2f& rayDir, const Vector2f& rayOrigin, const Vector2i& mapPos, const Vector2f& stepSize) const
        {
            Vector2f rayLength1d;
            if (rayDir.x < 0)
            {
                rayLength1d.x = (rayOrigin.x - static_cast<float>(mapPos.x)) * stepSize.x;
            }
            else
            {
                rayLength1d.x = (static_cast<float>(mapPos.x) + 1.f - rayOrigin.x) * stepSize.x;
            }
            if (rayDir.y < 0)
            {
                rayLength1d.y = (rayOrigin.y - static_cast<float>(mapPos.y)) * stepSize.y;
            }
            else
            {
                rayLength1d.y = (static_cast<float>(mapPos.y + 1.f - rayOrigin.y)) * stepSize.y;
            }
            return rayLength1d;
        }
        
        std::tuple<Color, Vector2f, bool> castRayUntilHit(const Vector2f& rayLength1dInit, const Vector2i& mapPosInit, const Vector2f& stepSize, const Vector2i& step) const
        {
            bool side;
            Color rayColor;
            Vector2f rayLength1d = rayLength1dInit;
            Vector2i mapPos = mapPosInit;
            while (true)
            {
                //jump to next map square, either in x-direction, or in y-direction
                if (rayLength1d.x < rayLength1d.y)
                {
                    mapPos.x += step.x;
                    rayLength1d.x += stepSize.x;

                    side = false;

                }
                else
                {
                    mapPos.y += step.y;
                    rayLength1d.y += stepSize.y;

                    side = true;
                }

                if (wallMap.isOOB(mapPos))
                {
                    rayColor = Color::Black;
                    break;
                }
                char rayEndChar = wallMap.getChar(mapPos);
                //Check if ray has hit a wall
                if (rayEndChar != '0')
                {
                    rayColor = wallMap.getColor(mapPos);
                    break;
                }
            }
            return { rayColor, rayLength1d, side };
        }

        float getRayDistPerpendicular(const Vector2f& rayLength1d, const Vector2f& stepSize, const bool side) const
        {
            return (!side) ? rayLength1d.x - stepSize.x : rayLength1d.y - stepSize.y;
        }

        void shadeColor(Color& color, const float rayDistPerpendicular, const bool side) const
        {
            //darkens hits on the side
            if (side)
            {
                color.r = std::max(color.r - 50.f, 0.f);
                color.g = std::max(color.g - 50.f, 0.f);
                color.b = std::max(color.b - 50.f, 0.f);
            }

            //gradually darkens rays if they are further
            color.r = std::max(color.r - 11.f * rayDistPerpendicular, 0.f);
            color.g = std::max(color.g - 11.f * rayDistPerpendicular, 0.f);
            color.b = std::max(color.b - 11.f * rayDistPerpendicular, 0.f);
        }

        void drawVerticalBar3d(Color& color, const float rayDistPerpendicular, const float angleOffset, const float verticalPixelOffset, int x)
        {
            const float lineHeight = SCREEN_SIZE.y / (rayDistPerpendicular * cos(angleOffset));
            const float drawStartY = SCREEN_SIZE.y / 2.f - lineHeight / 2.f + verticalPixelOffset;

            vertBar.setFillColor(color);
            vertBar.setPosition(Vector2f(x, drawStartY));
            vertBar.setSize(Vector2f(1, lineHeight));
            window.draw(vertBar);
        }

        Vector2f getHitPos(const Vector2f& rayOrigin, const Vector2f& rayDir, const float rayDistPerpendicular, const float angleOffset) const
        {
            return Vector2f{ rayOrigin.x + rayDir.x * rayDistPerpendicular * abs(cos(angleOffset)), 
                rayOrigin.y + rayDir.y * rayDistPerpendicular * abs(cos(angleOffset)) };
        }

        sf::VertexArray getRayLine2d(const Vector2f& rayOrigin, const Vector2f& hitPos) const
        {
            sf::VertexArray arrayLine2d(sf::Lines, 2);
            arrayLine2d[0].color = Color::Cyan;
            arrayLine2d[1].color = Color::Cyan;
\
            arrayLine2d[0].position = Vector2f(START_POS_X + GUI_SCALE * rayOrigin.x * TILE_SIZE, GUI_SCALE * rayOrigin.y * TILE_SIZE);
            arrayLine2d[1].position = Vector2f(START_POS_X + GUI_SCALE * hitPos.x * TILE_SIZE, GUI_SCALE * hitPos.y * TILE_SIZE);

            return arrayLine2d;
        }

        void draw2dRayLines()
        {
            for (auto& line : rayVector2d)
            {
                window.draw(line);
                hitCircle.setPosition(line[1].position);
                window.draw(hitCircle);
            }
        }

        void render(const Vector2f screenPos, const Vector2f playerDir, const float playerAngleVertical)
        {         
            //reserve memory for the 2d ray vector (one for each pixel)
            rayVector2d.reserve(static_cast<size_t>(SCREEN_SIZE.x));
            
            //converts our player position on the screen into tile coords
            Vector2f rayOrigin = toTileCoords(screenPos);

            //gets the amount of pixels which we need to shift our objects vertically to accomodate for player vertical rotation
            const float verticalPixelOffset = getVerticalPixelOffset(playerAngleVertical);

            //gets plane perpendicular to our character's direction at a distance of 2/3 of a unit away
            Vector2f plane = playerDir.getPerpendicularVector() * TWO_THIRDS;

            //draws the colored floor of our world in "3d" based on the vertical rotation of our player
            drawFloor(verticalPixelOffset);

            for (int x = 0; x < SCREEN_SIZE.x; ++x)
            {
                //gets us the angle of our ray targeting horizontal pixel x 
                //also returns us the amount which our angle strays from the direction of the player
                //types are Vector2f, float
                auto [rayDir, angleOffset] = setUpRayAngle(playerDir, plane, x);

                // which box of the map we're in
                Vector2i mapPos{ static_cast<int>(rayOrigin.x) , static_cast<int>(rayOrigin.y) };

                //length of ray from one x or y-side to next x or y-side
                Vector2f stepSize = getStepSize(rayDir);

                //what direction to step in x or y-direction (either +1 or -1)
                Vector2i step = getStep(rayDir);

                //length of ray from current position to next x or y-side
                Vector2f initRayLength1d = getInitialRayLength1d(rayDir, rayOrigin, mapPos, stepSize);

                //perform DDA - returns the color, length of the array, and whether it hit the side or not
                // Types are Color, Vector2f, bool
                auto [rayColor, rayLength1d, side] = castRayUntilHit(initRayLength1d, mapPos, stepSize, step);

                //get distance of ray perpendicular to the plane
                float rayDistPerpendicular = getRayDistPerpendicular(rayLength1d, stepSize, side);

                //applies simple shader based on distance and which side the ray hits
                shadeColor(rayColor, rayDistPerpendicular, side); 

                //draw 3d vertical bars
                drawVerticalBar3d(rayColor, rayDistPerpendicular, angleOffset, verticalPixelOffset, x);

                //for 2d only, gets hit position on the map
                Vector2f hitPos = getHitPos(rayOrigin, rayDir, rayDistPerpendicular, angleOffset);

                //set up 2d Lines and add to vector
                rayVector2d.emplace_back(getRayLine2d(rayOrigin, hitPos));
            }

            //draw wallMap
            wallMap.draw();

            //draw array of 2d rays onto map, alongside their hit markers
            draw2dRayLines();

            //erase rayVector for next cycle
            rayVector2d.clear();
        }
    };
	
}