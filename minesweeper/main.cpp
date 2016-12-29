#pragma once
#include				<SFML/Graphics.hpp>
#include				"include/gamegraphics.h"
#include				"include/game.h"

using namespace sf;


int main()
{
	GameGraphics graphics;
	Game mainGame;

	graphics.initialization();
	mainGame.initialization();
	while (graphics.window.isOpen())
	{

		Event currentEvent;
		while (graphics.window.pollEvent(currentEvent))
		{
			mainGame.handleEvent(currentEvent, graphics);
		}

		graphics.drawScreen(mainGame.gameState);
	}

	return 0;
}