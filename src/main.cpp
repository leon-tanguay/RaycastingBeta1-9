#include <utility>
#include <array>
#include <filesystem> 
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>

#include "header/hueShift.h"
#include "header/map.h"
#include "header/player.h"
#include "header/ray.h"
#include "header/rcvector.h";
#include "header/resourcemanager.h"
#include "header/drawhandler.h"

//Constants
const std::string WINDOW_TITLE{ "RayCasting" }; 
const sf::Vector2u SCREEN_SIZE = { 1000u, 1000u }; //dimensions of window
const unsigned int FRAME_RATE{ 60u }; 
const float PI_OVER_180 = 0.01745329251;
const std::string RESOURCE_DIR{ "resource" }; //path of resource, can be relative or absolute, if not found use bin dir
const std::string MAP_FILE{ "worldMap2.png" }; //file name, must be in resource folder
const std::string SPRITE_FILE{ "playerSprite.png" }; //file name, must be in resource folder
const std::string FONT_FILE{ "arial.ttf" }; //file name, must be in resource folder

const float GUI_SCALE = 0.3f;
const float PLAYER_MAX_SPEED = 3.f;

bool loadResources(ResourceManager& resourceManager)
{
    if (!resourceManager.loadImage("map", MAP_FILE))
    {
        std::cout << "Couldn't load world map\n";
        return false;
    }
    if (!resourceManager.loadTexture("player", SPRITE_FILE))
    {
        std::cout << "Couldn't load player texture\n";
        return false;
    }
    if (!resourceManager.loadFont("default", FONT_FILE))
    {
        std::cout << "Couldn't load font\n";
    }
    return true;
}

int main()
{
    //load graphics needed
    ResourceManager resources{ RESOURCE_DIR };
    if (!loadResources(resources))
    {
        return -1;
    }

    //set up SFML window
    sf::RenderWindow window = sf::RenderWindow{ sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), WINDOW_TITLE };
    window.setFramerateLimit(FRAME_RATE);
    const rc::Vector2f screenCenterPos{ static_cast<float> (window.getSize().x) / 2.f,  static_cast<float> (window.getSize().y) / 2.f };
    
    //set up player sprite
    sf::Sprite playerSprite{ resources.getTexture("player") };
    playerSprite.setOrigin(sf::Vector2f(resources.getTexture("player").getSize() / 2u));

    //set up the map
    rc::Map wallMap{ window, resources.getImage("map"), GUI_SCALE };
    const float tileSize = wallMap.getTileSizeF();

    //set up the player sprite's controller
    rc::PlayerController player{ PLAYER_MAX_SPEED };
    player.setPos(screenCenterPos);

    //set up the handler for raycasting
    rc::RayHandler rayHandler(wallMap, window, GUI_SCALE);

    //initialize variables
    rc::Vector2f tileSizeVector(tileSize, tileSize);
    sf::RectangleShape wallHitBox(tileSizeVector);
    bool captureMouseForMovement = true;
    window.setMouseCursorVisible(!captureMouseForMovement);

    //set mouse to center of screen
    sf::Mouse::setPosition(screenCenterPos.toInt(), window);

    //set up SFML clock
    sf::Clock clock;

    //unused at the moment
    //std::vector<sf::Drawable> drawList;

    while (window.isOpen())
    {
        
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            //close window if the window's close button is clicked
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyReleased)
            {
                //Escape key will toggle whether mouse movements are captured to move player or move cursor
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (captureMouseForMovement = !captureMouseForMovement)
                    {
                        sf::Mouse::setPosition(screenCenterPos.toInt(), window);
                    }
                    window.setMouseCursorVisible(!captureMouseForMovement);
                }
            }
        }

        //movement keys
        const bool isKeyForwardPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        const bool isKeyBackPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
        const bool isKeyLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        const bool isKeyRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

        //get relative mouse movement from fixed position, then reset mouse to fixed position again for next iteration
        rc::Vector2i relativeMousePos = rc::Vector2i(sf::Mouse::getPosition(window)) - screenCenterPos.toInt();
        if (captureMouseForMovement)
        {
            player.rotatePlayer(relativeMousePos);
            if (relativeMousePos != rc::Vector2i(0, 0)) sf::Mouse::setPosition(screenCenterPos.toInt(), window);
        }

        //update velocity and position based on keys pressed and prevouis state (velocity/accel)
        const float dt = clock.restart().asSeconds();
        player.updateKeyControls(dt, isKeyForwardPressed, isKeyBackPressed, isKeyLeftPressed, isKeyRightPressed);
        rc::Vector2f velocity = player.getVelocity(dt);
        rc::Vector2f position = player.getPos();

        //handle collissions
        wallMap.handleCollisions(position, velocity, playerSprite.getGlobalBounds());

        position.x += velocity.x * tileSize;
        position.y += velocity.y * tileSize;
        player.setPos(position);

        bool pause = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            pause = true;
        }
        rc::Vector2f rayDir{ cos(player.getAngle() * PI_OVER_180), sin(player.getAngle() * PI_OVER_180) };

        float playerAngleVertical = player.getVerticalAngle();

        window.clear();
        rayHandler.render(position, rayDir, playerAngleVertical);

        //resizing sprite back to normal after running the render
        playerSprite.setRotation(player.getAngle());
        playerSprite.setPosition(window.getSize().x * (1.f - GUI_SCALE) + position.x * GUI_SCALE, position.y * GUI_SCALE);
        playerSprite.setScale(GUI_SCALE*2, GUI_SCALE*2);
        window.draw(playerSprite);
        window.display();

        playerSprite.setPosition(position);
        playerSprite.setScale(1.f, 1.f);
    }
}