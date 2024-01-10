/*
#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>
#include <utility>
#include <array>
#include "wall.h"

namespace wall
{
	class WallMap
	{
	public:
		WallMap(sf::RenderWindow& window, const sf::Image& mapImg) : window(window), mapImg(mapImg)
		{
			wallVector.reserve(getMapArea());
			fillWallVector();
		}
		int getMapSizeX() const
		{
			return mapImg.getSize().x;
		}
		int getMapSizeY() const
		{
			return mapImg.getSize().y;
		}
		int getMapArea() const
		{
			return mapImg.getSize().x * mapImg.getSize().y;
		}
		void fillWallVector()
		{
			const sf::Uint8* pByteBuffer = mapImg.getPixelsPtr();
			{
		for (int y = 0; y < getMapSizeY(); ++y)
					for (int x = 0; x < getMapSizeX(); ++x)
				{
					int xy = y * getMapSizeX() + x;
					const sf::Uint8 red = pByteBuffer[4 * xy];
					const sf::Uint8 green = pByteBuffer[4 * xy + 1];
					const sf::Uint8 blue = pByteBuffer[4 * xy + 2];
					const sf::Uint8 alpha = pByteBuffer[4 * xy + 3];
					sf::Color pixelColor{ red, green, blue, alpha };

					if (pixelColor != sf::Color::Black)
					{
						bool makeNewWall = true;
						sf::Vector2i pos{ x,y };
						std::cout << "pixel at (" << x << ", " << y << ")" << '\n';
						for (auto &wall : wallVector)
						{
							if (wall.addVertex(pos, pixelColor))
							{
								makeNewWall = false;
								break;
							}
							//std::cout << "wall height: " << wall.getHeight() << std::endl;
						}
						if (makeNewWall)
						{
							wallVector.emplace_back(Wall{pos, pixelColor });
						}
					}
				}
			}
		}
		void printWalls()
		{
			int i = 0;
			for (auto wallPtr = wallVector.begin(); wallPtr < wallVector.end(); ++wallPtr)
			{
				std::cout << "Wall " << i << ": pos1(" << wallPtr->getPos1().x << ", " << wallPtr->getPos1().y << "), pos2(" << wallPtr->getPos2().x << ", " << wallPtr->getPos2().y << ")\n";
				++i;
			}
			std::cout << '\n';
		}

		void generateWalls()
		{
			int gridSizeX = window.getSize().x / getMapSizeX();
			int gridSizeY = window.getSize().y / getMapSizeX();
			for (const Wall &wall : wallVector)
			{
				//std::cout << "Width: " << wall.getWidth() << " Height: " << wall.getHeight() << std::endl;
				sf::Vector2f wallPos(gridSizeX * wall.getPos1().x, gridSizeY * wall.getPos1().y);
				sf::Vector2f wallDimensions(gridSizeX * wall.getWidth(), gridSizeY * wall.getHeight());
				sf::RectangleShape wallRect(wallDimensions);
				wallRect.setFillColor(wall.getColor());
				wallRect.setPosition(wallPos);
				rectangleVector.emplace_back(wallRect);
			}
		}
		void drawWalls()
		{
			for (sf::RectangleShape wallRect : rectangleVector)
			{
				window.draw(wallRect);
			}
		}
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getHitBoxes()
		{
			std::vector<std::pair<sf::Vector2f, sf::Vector2f>> retVect;
			for (sf::RectangleShape wallRect: rectangleVector)
			{
				auto bounds = wallRect.getGlobalBounds();
				sf::Vector2f pos1 = wallRect.getPosition();
				sf::Vector2f pos2{ wallRect.getPosition().x + wallRect.getSize().x, wallRect.getPosition().y + wallRect.getSize().y };
				retVect.emplace_back(std::make_pair(pos1, pos2));
			}
			return retVect;
		}
	private:
        sf::RenderWindow& window;
        const sf::Image& mapImg;
		std::vector<sf::RectangleShape> rectangleVector;
        std::vector<Wall> wallVector;
	};
}
*/