#pragma once

#include <SFML/Graphics.hpp>

namespace rc
{
	void updateWindow(sf::RenderWindow window, std::vector<sf::Drawable> objectsToDraw)
	{
		for (object : objectsToDraw)
		{
			window.draw(object);
		}
	}
}