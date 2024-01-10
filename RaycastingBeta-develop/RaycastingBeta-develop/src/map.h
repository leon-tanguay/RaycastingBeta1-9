#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>
#include <utility>
#include <array>
#include <iostream>
#include "rcvector.h"

namespace rc
{
	class Map
	{
	public:
		Map(sf::RenderWindow& window, const sf::Image& mapImg, float scale) : window(window), mapImg(mapImg), mapSize(static_cast<int>(mapImg.getSize().x), static_cast<int>(mapImg.getSize().y)), mapArea(mapSize.x * mapSize.y), scale(scale)
		{
			charVector.assign(mapArea, '0');
			
			fillVectors();
		}
		Vector2i getMapSize() const
		{
			return mapSize;
		}
		int getMapArea() const
		{
			return mapArea;
		}
		char getChar(Vector2i tilePos) const
		{
			int index = tilePos.y * getMapSize().x + tilePos.x;
			return charVector[index];
		}
		sf::Color getColor(Vector2i tilePos) const
		{
			int index = tilePos.y * getMapSize().x + tilePos.x;
			return rectangleVector[index].getFillColor();
		}
		void setChar(Vector2i tilePos, char val)
		{
			int index = tilePos.y * getMapSize().x + tilePos.x;
			charVector[index] = val;
		}
		int getIndexFromTilePos(Vector2i tilePos) const
		{
			return tilePos.y * getMapSize().x + tilePos.x;
		}
		void handleCollisions(const Vector2f &playerPos, Vector2f& playerVelocity, const sf::FloatRect& spriteGlobalBounds) const
		{
			Vector2i posOffsets[4] = { Vector2i{1,0},Vector2i{0,1},Vector2i{-1,0},Vector2i{0,-1} };
			sf::RectangleShape wallHitBox(Vector2f{ getTileSizeF(), getTileSizeF() });
			auto tilePos = getTilePosFromCoords(playerPos);
			for (auto offset : posOffsets)
			{
				auto adjPos = tilePos + offset;
				if (isOOB(adjPos) || getChar(adjPos) == '1')
				{
					wallHitBox.setPosition(adjPos.x * getTileSizeF(), adjPos.y * getTileSizeF());
					if (spriteGlobalBounds.intersects(wallHitBox.getGlobalBounds()))
					{
						if (playerVelocity.x < 0.f && offset.x < 0) playerVelocity.x = 0.f;
						if (playerVelocity.x > 0.f && offset.x > 0) playerVelocity.x = 0.f;
						if (playerVelocity.y < 0.f && offset.y < 0) playerVelocity.y = 0.f;
						if (playerVelocity.y > 0.f && offset.y > 0) playerVelocity.y = 0.f;
					}
				}
			}
		}
		Vector2i getTilePosFromCoords(Vector2f coordPos) const
		{
			Vector2i tilePos;
			tilePos.x = static_cast<int> ((coordPos.x / getTileSizeF()));
			tilePos.y = static_cast<int> ((coordPos.y / getTileSizeF()));
			return tilePos;
		}
		Vector2f getCoordsFromTilePos(Vector2i tilePos) const
		{
			Vector2f coords;
			coords.x = tilePos.x * getTileSizeF();
			coords.y = tilePos.y * getTileSizeF();
			return coords;
		}
		bool isOOB(Vector2i gridPos) const
		{
			if (gridPos.x < 0 || gridPos.x >= getMapSize().x)
				return true;
			if (gridPos.y < 0 || gridPos.y >= getMapSize().y)
				return true;
			return false;
		}
		Vector2i getCharPos(int index) const
		{
			int x = index % getMapSize().x;
			int y = index / getMapSize().x;
			return Vector2i{ x,y };
		}
		float getTileSizeF() const
		{
			return static_cast<float>(window.getSize().y) / getMapSize().y;
		}
		std::vector<char> getCharVector() const
		{
			return charVector;
		}
		void fillVectors()
		{
			const sf::Uint8* pByteBuffer = mapImg.getPixelsPtr();
			Vector2f wallDimensions(scale * getTileSizeF()-1, scale * getTileSizeF()-1);
			float startX = window.getSize().x - static_cast<float>(getMapSize().x) * getTileSizeF() * scale;
			for (int y = 0; y < getMapSize().y; ++y)
			{

				for (int x = 0; x < getMapSize().x; ++x)
				{
					int xy = y * getMapSize().x + x;
					const sf::Uint8 red = pByteBuffer[4 * xy];
					const sf::Uint8 green = pByteBuffer[4 * xy + 1];
					const sf::Uint8 blue = pByteBuffer[4 * xy + 2];
					const sf::Uint8 alpha = pByteBuffer[4 * xy + 3];
					sf::Color pixelColor{ red, green, blue, alpha };
					Vector2i pixelPos{ x,y };
					//std::cout << "pixel at (" << x << ", " << y << ")" << '\n';
					Vector2f wallPos(startX + scale * getTileSizeF() * x, scale * getTileSizeF() * y);
					sf::RectangleShape wallRect(wallDimensions);
					wallRect.setFillColor(pixelColor);
					wallRect.setPosition(wallPos);
					rectangleVector.emplace_back(wallRect);
					if (pixelColor != sf::Color::Black)
					{
						setChar(pixelPos, '1');
					}
				}
			}
		}

		void printWalls() const
		{
			int i = 0;
			for (auto &c : charVector)
			{
				if (c != '0')
					std::cout << "Wall at Pos ("  << getCharPos(i).x << ", " << getCharPos(i).y << ")\n";
				++i;
			}
			std::cout << '\n';
		}

		void draw() const
		{
			float startX = window.getSize().x - static_cast<float>(getMapSize().x) * getTileSizeF() * scale;
			Vector2f whiteSquareDimensions(getTileSizeF() * scale, getTileSizeF() * scale);
			Vector2f blackSquareDimensions(whiteSquareDimensions.x * scale - 1, whiteSquareDimensions.y * scale - 1);
			  
			sf::RectangleShape whiteGridRect{ whiteSquareDimensions };
			sf::RectangleShape blackGridRect{ blackSquareDimensions };

			whiteGridRect.setFillColor(sf::Color::White);
			blackGridRect.setFillColor(sf::Color::Black);

			
			for (int i = 0; i < charVector.size(); ++i)
			{
				Vector2f rectPos{ startX + getCharPos(i).x * getTileSizeF() * scale,getCharPos(i).y * getTileSizeF() * scale };
				blackGridRect.setPosition(rectPos);
				whiteGridRect.setPosition(rectPos);
				window.draw(whiteGridRect);
				window.draw(blackGridRect);
			}
			for (sf::RectangleShape wallRect : rectangleVector)
			{
				window.draw(wallRect);
			}
		}

	private:
		sf::RenderWindow& window;
		const sf::Image& mapImg;
		std::vector<sf::RectangleShape> rectangleVector;
		sf::RectangleShape wallHitBox;
		std::vector<char> charVector;
		const float scale;
		Vector2i mapSize;
		const unsigned int mapArea;
	};
}