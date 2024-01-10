#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <stdio.h>
#include <math.h>
#include <utility>
#include <array>
#include <iostream>
#include "rcvector.h"

namespace rc
{
    static constexpr float PI = 3.14159265359;
    static constexpr float halfPI = PI * 0.5f;

    //Vector and math
    Vector2f rotateVector(const Vector2f v, const float angle)
    {
        return Vector2f
        {
            cos(angle * PI / 180.f) * v.x - sin(angle * PI / 180.f) * v.y,
            sin(angle * PI / 180.f) * v.x + cos(angle * PI / 180.f) * v.y
        };
    }

	class PlayerController
	{
    private:
        bool isAccelleratingForwardOrBack() const
        {
            return (keyForwardTimeDown > 0.001f || keyBackTimeDown > 0.001f);
        }

        bool isAccelleratingLeftOrRight() const
        {
            return (keyLeftTimeDown > 0.001f || keyRightTimeDown > 0.001f);
        }

        Vector2f getRotatedVelocity()
        {
            Vector2f newVelocity{ oldVelocity };

            if (!isAccelleratingForwardOrBack())
            {
                newVelocity.y *= decellerationSpeed;
                if (abs(newVelocity.y) < 0.1)
                {
                    newVelocity.y = 0.f;
                }
            }
            if (!isAccelleratingLeftOrRight())
            {
                newVelocity.x *= decellerationSpeed;
                if (abs(newVelocity.x) < 0.1)
                {
                    newVelocity.x = 0.f;
                }
            }

            newVelocity.y += (accelerationSpeed * (keyBackTimeDown - keyForwardTimeDown));
            newVelocity.x += (accelerationSpeed * (keyRightTimeDown - keyLeftTimeDown));
            newVelocity.x = clampVelocity(newVelocity.x);
            newVelocity.y = clampVelocity(newVelocity.y);

            float vectorMagnitude = newVelocity.magnitude();
            if (vectorMagnitude > 1)
            {
                newVelocity.x /= vectorMagnitude;
                newVelocity.y /= vectorMagnitude;
            }

            oldVelocity = newVelocity;

            Vector2f rotatedVector = rotateVector(newVelocity, playerAngle + 90.f);
            rotatedVector *= maxPlayerSpeed;

            //std::cout << "Velocity: (" << rotatedVector.y << ", " << rotatedVector.x << ")\n";
            return rotatedVector;
        }

	public:
        PlayerController(float maxPlayerSpeed) : maxPlayerSpeed(maxPlayerSpeed), oldVelocity(0.f, 0.f), playerAngle(0.f), playerAngleVertical(0.f)
		{
        }

        void updateKeyControls(const float dt,
            const bool isKeyForwardPressed, const bool isKeyBackPressed,
            const bool isKeyLeftPressed, const bool isKeyRightPressed)
        {
            if (isKeyForwardPressed) keyForwardTimeDown += dt; else keyForwardTimeDown = 0.f;
            if (isKeyBackPressed) keyBackTimeDown += dt; else keyBackTimeDown = 0.f;
            if (isKeyLeftPressed) keyLeftTimeDown += dt; else keyLeftTimeDown = 0.f;
            if (isKeyRightPressed) keyRightTimeDown += dt; else keyRightTimeDown = 0.f;
        }

        sf::Vector2f getVelocity(const float dt)
        {
            sf::Vector2f velocity = getRotatedVelocity() * dt;
            return velocity;
        }

        void rotatePlayer(Vector2i mousePos)
        {
            playerAngle += 0.2f * (mousePos.x);
            if (playerAngle >= 360.f)
            {
                playerAngle -= 360.f;
            }
            if (playerAngle < 0.f)
            {
                playerAngle += 360.f;
            }

            playerAngleVertical -= 0.2f * (mousePos.y);

            if (playerAngleVertical >= 30.f)
            {
                playerAngleVertical = 30.f;
            }
            if (playerAngleVertical < -30.f)
            {
                playerAngleVertical = -30.f;
            }
        }

        float getAngle() const
        {
            return playerAngle;
        }
        float getVerticalAngle() const
        {
            return playerAngleVertical;
        }

        float clampVelocity(float f) const
        {
            if (f < -1.f)
            {
                return -1.f;
            }
            else if (f > 1.f)
            {
                return 1.f;
            }
            return f;
        }
        Vector2f getPos()
        {
            return playerPos;
        }
        void setPos(Vector2f posIn)
        {
            playerPos = posIn;
        }

 

        /*
        Vector2i getGridPos()
        {
            return wallMap.getTilePosFromCoords(playerSprite.getPosition());
        }

        void highlightGridPos()
        {
            wallMap.highlightTile(getGridPos(), sf::Color::Magenta);
        }
        */



        /*
        void draw(sf::RenderWindow window)
        {
            highlightGridPos();
            window.draw(playerSprite);
        }
        */
	private:
        float keyForwardTimeDown = 0.f;
        float keyBackTimeDown = 0.f;  
        float keyLeftTimeDown = 0.f;   
        float keyRightTimeDown = 0.f;
        Vector2f oldVelocity;
        Vector2f playerPos;
		float maxPlayerSpeed;
        float playerAngle;
        const float accelerationSpeed = 3.f;
        const float decellerationSpeed = 0.8f;
        float playerAngleVertical;
	};
}