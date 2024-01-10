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
		Map(sf::RenderWindow& window, const sf::Image& mapImg, float scale);

		char getChar(const Vector2i tilePos) const;
		sf::Color getColor(const Vector2i tilePos) const;
		float getTileSizeF() const;

		void handleCollisions(const Vector2f& playerPos, Vector2f& playerVelocity, const sf::FloatRect& spriteGlobalBounds) const;
		bool isOOB(const Vector2i gridPos) const;
		
		void draw() const;

	private:
		void printWalls() const;
		void fillVectors(const sf::Image& mapImg);
		//std::vector<char> getCharVector() const { return charVector; }
		//Vector2i getMapSize() const { return mapSize; }
		//int getMapArea() const { return mapArea; }


		void setChar(Vector2i tilePos, char val);
		int getIndexFromTilePos(Vector2i tilePos) const;

		Vector2i getTilePosFromCoords(const Vector2f coordPos) const;
		Vector2f getCoordsFromTilePos(const Vector2i tilePos) const;
		Vector2i getCharPos(const int index) const;

		sf::Color getImageColor(const sf::Image& mapImg, const Vector2i pixelPos) const;

	private:
		sf::RenderWindow& window;
		std::vector<sf::RectangleShape> rectangleVector;
		sf::RectangleShape wallHitBox;
		std::vector<char> charVector;
		const float scale;
		Vector2i mapSize;
		const unsigned int mapArea;
	};
}