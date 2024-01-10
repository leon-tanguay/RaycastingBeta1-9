#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>
#include <utility>
#include <array>
#include "hueShift.h"
#include <iostream>
#include "wallMap.h"

namespace wall
{
	class Wall
	{
	public:
		Wall(sf::Vector2i pos1, sf::Vector2i pos2, sf::Color color= sf::Color::White) : pos1{pos1}, pos2{pos2}, color{color}, is2Points(true)
		{	
		}
		Wall(sf::Vector2i pos, sf::Color color = sf::Color::White) : pos1{ pos }, pos2(-1, -1), color{color}, is2Points(false)
		{
		}
		sf::Vector2i getPos1() const
		{
			return pos1;
		}
		sf::Vector2i getPos2() const
		{
			return pos2;
		}
		sf::Color getColor() const
		{
			return color;
		}
		int getWidth() const
		{
			if (!is2Points) return 1;
			return abs(pos2.x - pos1.x) + 1;
		}
		int getHeight() const
		{
			if (!is2Points) return 1;
			return abs(pos2.y - pos1.y) + 1;
		}
		bool isHorizontal() const
		{
			return (pos1.x == pos2.x);
		}
		bool isVertical() const
		{
			return (pos1.y == pos2.y);
		}
		static bool isAdjacent(const sf::Vector2i pos1, const sf::Vector2i pos2)
		{
			if (pos1.x < 0 || pos2.x < 0 || pos1.y < 0 || pos2.y < 0)
			{
				return false;
			}
			if (((abs(pos1.x - pos2.x) == 1) && (abs(pos1.y - pos2.y) == 0)) || ((abs(pos1.x - pos2.x) == 0) && (abs(pos1.y - pos2.y) == 1)))
			{
				return true;
			}
			return false;
		}
		static bool isEqual(const sf::Vector2i pos1, const sf::Vector2i pos2)
		{
			if (pos1.x==pos2.x && pos1.y==pos2.y)
			{
				return true;
			}
			return false;
		}
		int adjDist(const sf::Vector2i pos1, const sf::Vector2i pos2) const
		{
			return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
		}
		bool addVertex(const sf::Vector2i posIn, sf::Color colorIn)
		{
			if (color != colorIn) return false;
			if (!is2Points)
			{
				if (isAdjacent(posIn, pos1))
				{
					pos2 = posIn;
					is2Points = true;
					return true;
				}
			}
			if (isAdjacent(pos1, posIn) && ((pos2.x == posIn.x) || (pos2.y == posIn.y)))
			{
				if (adjDist(posIn, pos2) > adjDist(pos1, pos2))
				{
					pos1 = posIn;
					return true;
				}
				return false;
			}

			if (isAdjacent(pos2, posIn) && ((pos1.x == posIn.x) || (pos1.y == posIn.y)))
			{
				if (adjDist(posIn, pos1) > adjDist(pos1, pos2))
				{
					pos2 = posIn;
					return true;
				}
				return false;
			}
			return false;
		}
	private:
		sf::Vector2i pos1;
		sf::Vector2i pos2;
		sf::Color color;
		bool is2Points;
	};
}
