#include "header/player.h"

namespace rc
{

    PlayerController::PlayerController(float maxPlayerSpeed) : maxPlayerSpeed(maxPlayerSpeed), oldVelocity(0.f, 0.f), playerAngle(0.f), playerAngleVertical(0.f)
    {
    }

    void PlayerController::updateKeyControls(const float dt,
        const bool isKeyForwardPressed, const bool isKeyBackPressed,
        const bool isKeyLeftPressed, const bool isKeyRightPressed)
    {
        if (isKeyForwardPressed) keyForwardTimeDown += dt; else keyForwardTimeDown = 0.f;
        if (isKeyBackPressed) keyBackTimeDown += dt; else keyBackTimeDown = 0.f;
        if (isKeyLeftPressed) keyLeftTimeDown += dt; else keyLeftTimeDown = 0.f;
        if (isKeyRightPressed) keyRightTimeDown += dt; else keyRightTimeDown = 0.f;
    }

    Vector2f PlayerController::getVelocity(const float dt)
    {
        Vector2f velocity = getRotatedVelocity() * dt;
        return velocity;
    }

    void PlayerController::rotatePlayer(Vector2i mousePos)
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

    float PlayerController::getAngle() const
    {
        return playerAngle;
    }

    float PlayerController::getVerticalAngle() const
    {
        return playerAngleVertical;
    }

    float PlayerController::clampVelocity(float f) const
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

    Vector2f PlayerController::getPos() const
    {
        return playerPos;
    }

    void PlayerController::setPos(const Vector2f posIn)
    {
        playerPos = posIn;
    }

    bool PlayerController::isAccelleratingForwardOrBack() const
    {
        return (keyForwardTimeDown > 0.001f || keyBackTimeDown > 0.001f);
    }

    bool PlayerController::isAccelleratingLeftOrRight() const
    {
        return (keyLeftTimeDown > 0.001f || keyRightTimeDown > 0.001f);
    }

    Vector2f PlayerController::getRotatedVelocity()
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

        Vector2f rotatedVector = newVelocity.getRotatedVector( playerAngle + 90.f);
        rotatedVector *= maxPlayerSpeed;

        //std::cout << "Velocity: (" << rotatedVector.y << ", " << rotatedVector.x << ")\n";
        return rotatedVector;
    }
}