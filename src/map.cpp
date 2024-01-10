#include "header/map.h"

namespace rc
{
	Map::Map(sf::RenderWindow& window, const sf::Image& mapImg, float scale) : window(window), mapSize(static_cast<int>(mapImg.getSize().x), static_cast<int>(mapImg.getSize().y)), mapArea(mapSize.x* mapSize.y), scale(scale)
	{
		charVector.assign(mapArea, '0');

		fillVectors(mapImg);
	}

	char Map::getChar(const Vector2i tilePos) const
	{
		int index = tilePos.y * mapSize.x + tilePos.x;
		return charVector[index];
	}

	sf::Color Map::getColor(const Vector2i tilePos) const
	{
		int index = tilePos.y * mapSize.x + tilePos.x;
		return rectangleVector[index].getFillColor();
	}
	
	void Map::setChar(const Vector2i tilePos, char val)
	{
		int index = tilePos.y * mapSize.x + tilePos.x;
		charVector[index] = val;
	}
	
	int Map::getIndexFromTilePos(const Vector2i tilePos) const
	{
		return tilePos.y * mapSize.x + tilePos.x;
	}

	void Map::handleCollisions(const Vector2f& playerPos, Vector2f& playerVelocity, const sf::FloatRect& spriteGlobalBounds) const
	{
		const Vector2i posOffsets[4] = { Vector2i{ 1, 0 },Vector2i{ 0, 1 },Vector2i{ -1, 0 },Vector2i{ 0, -1 } };
		const Vector2i tilePos = getTilePosFromCoords(playerPos);

		sf::RectangleShape wallHitBox(Vector2f{ getTileSizeF(), getTileSizeF() });
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

	Vector2i Map::getTilePosFromCoords(Vector2f coordPos) const
	{
		Vector2i tilePos
		{
			static_cast<int> ((coordPos.x / getTileSizeF())),
			static_cast<int> ((coordPos.y / getTileSizeF()))
		};
		return tilePos;
	}
	Vector2f Map::getCoordsFromTilePos(Vector2i tilePos) const
	{
		Vector2f coords{ tilePos.x * getTileSizeF(), tilePos.y * getTileSizeF() };
		return coords;
	}
	
	bool Map::isOOB(Vector2i gridPos) const
	{
		return (gridPos.x < 0 || gridPos.x >= mapSize.x || gridPos.y < 0 || gridPos.y >= mapSize.y);
	}
	
	Vector2i Map::getCharPos(int index) const
	{
		Vector2i charPos{ index % mapSize.x, index / mapSize.x };
		return charPos;
	}
	
	float Map::getTileSizeF() const
	{
		return static_cast<float>(window.getSize().y) / mapSize.y;
	}

	void Map::fillVectors(const sf::Image& mapImg)
	{
		rectangleVector.reserve(mapSize.x * mapSize.y);
		const sf::Vector2f wallDimensions{ scale * getTileSizeF() - 1, scale * getTileSizeF() - 1 };
		const float startX = window.getSize().x - static_cast<float>(mapSize.x) * getTileSizeF() * scale;
		for (int y = 0; y < mapSize.y; ++y)
		{
			for (int x = 0; x < mapSize.x; ++x)
			{
				sf::RectangleShape& wallRect = rectangleVector.emplace_back(wallDimensions);

				//set the position
				const Vector2f wallPos(startX + scale * getTileSizeF() * x, scale * getTileSizeF() * y);
				wallRect.setPosition(wallPos.x, wallPos.y);

				//set the color based on the image color at this location
				const Vector2i pixelPos{ x, y };
				const sf::Color pixelColor = getImageColor(mapImg, pixelPos);
				wallRect.setFillColor(pixelColor);

				//set char for collision detection
				if (pixelColor != sf::Color::Black)
				{
					setChar(pixelPos, '1');
				}
			}
		}
	}

	sf::Color Map::getImageColor(const sf::Image& mapImg, const Vector2i pixelPos) const
	{
		const sf::Uint8* pByteBuffer = mapImg.getPixelsPtr();

		unsigned int byteIndex = 4 * (pixelPos.y * mapSize.x + pixelPos.x);

		const sf::Uint8 red = pByteBuffer[byteIndex];
		const sf::Uint8 green = pByteBuffer[++byteIndex];
		const sf::Uint8 blue = pByteBuffer[++byteIndex];
		const sf::Uint8 alpha = pByteBuffer[++byteIndex];
		
		return sf::Color{ red, green, blue, alpha };
	}

	void Map::printWalls() const
	{
		int i = 0;
		for (auto& c : charVector)
		{
			if (c != '0')
				std::cout << "Wall at Pos (" << getCharPos(i).x << ", " << getCharPos(i).y << ")\n";
			++i;
		}
		std::cout << '\n';
	}

	void Map::draw() const
	{
		float startX = window.getSize().x - static_cast<float>(mapSize.x) * getTileSizeF() * scale;
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

}