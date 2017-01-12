#include "include/stdafx.h"
#include "include/map.h"

int windowRows, windowColumns;
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
		switch (gameState)
		{
		case 0:
			printMainMenu();
			processMainMenuInput(gameState);
			break;
		case 1:
			printSettingsMenu();
			processSettingsInput(gameState, mapRows, mapColumns, mapBombs);
			if (gameState == 3)
			{
				map.initialize(mapRows, mapColumns, mapBombs);
			}
			break;
		case 2:
			printLeaderboard();
			processLeaderboardInput();
			break;
		case 3:
			map.printOnScreen();
			map.processInput();
			break;
		}
	}

	return 0;
}