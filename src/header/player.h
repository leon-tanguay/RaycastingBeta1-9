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

	class PlayerController
	{
	public:
        PlayerController(float maxPlayerSpeed);

        void updateKeyControls(const float dt,
            const bool isKeyForwardPressed, const bool isKeyBackPressed,
            const bool isKeyLeftPressed, const bool isKeyRightPressed);

        Vector2f getVelocity(const float dt);

        void rotatePlayer(Vector2i mousePos);

        float getAngle() const;
        
        float getVerticalAngle() const;

        float clampVelocity(float f) const;
        
        Vector2f getPos() const;
        
        void setPos(const Vector2f posIn);

	private:
        bool isAccelleratingForwardOrBack() const;

        bool isAccelleratingLeftOrRight() const;

        Vector2f getRotatedVelocity();

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