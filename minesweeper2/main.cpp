#include "include/stdafx.h"
#include "include/map.h"

Map map;

int main() 
{	
	char gameState;
	short mapRows, mapColumns, mapBombs;

	initializeSystem();

	bool finished = false;

	gameState = 0;
	while (!finished)
	{
		if (map.lost)
		{
			map.lost = 1 ^ map.lost;
			gameState = 0;
		}
		else if (map.won)
		{
			map.won = 1 ^ map.won;
			gameState = 0;
		}
		switch (gameState)
		{
		case 0:
			printMainMenu();
			processMainMenuInput(gameState);
			break;
		case 1:
			printSettingsMenu();
			processSettingsInput(gameState, mapRows, mapColumns, mapBombs);
			if (gameState == 2)
			{
				map.initialize(mapRows, mapColumns, mapBombs);
			}
			break;
		case 2:
			map.printOnScreen();
			if (map.checkWinCondition() == true)
			{
				map.won = 1 ^ map.won;
				gameState = 0;
				continue;
			}
			map.processInput(gameState);
			break;
		}
	}

	return 0;
}