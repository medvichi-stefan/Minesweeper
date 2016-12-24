#pragma once
#include <SFML/Graphics.hpp>
#include "include/gamegraphics.h"
#include "include/io.h"

using namespace sf;

int main()
{
	GameGraphics graphics;
	graphics.initialization();

	while (graphics.window.isOpen())
	{

		Event event;
		while (graphics.window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				graphics.window.close();
		}

		graphics.drawScreen();
	}

	return 0;
}