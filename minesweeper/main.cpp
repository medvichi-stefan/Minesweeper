#pragma once
#include				<SFML/Graphics.hpp>
#include				"include/gamegraphics.h"
#include				"include/io.h"
#include <iostream>

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
			{
				graphics.window.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					graphics.window.close();
				}
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				Vector2i mouseCoord;
				Vector2i windowCoord;
				mouseCoord.x = event.mouseButton.x;
				mouseCoord.y = event.mouseButton.y;
				std::cout << mouseCoord.x << " " << mouseCoord.y << '\n';
				windowCoord = graphics.window.getPosition();
				std::cout << windowCoord.x << ' ' << windowCoord.y << '\n';
				if (event.mouseButton.button == Mouse::Button::Left)
				{
					for (int i = 0; i < MAX_MENU_BUTTON; ++i)
					{
						if ( isTextClicked(graphics.textRect[i], mouseCoord) )
						{
							graphics.window.close();
						}
					}
				}
			}
		}

		graphics.drawScreen(0);
	}

	return 0;
}