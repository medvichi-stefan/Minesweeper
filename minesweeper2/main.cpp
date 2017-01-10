#include "include/stdafx.h"
#include "include/map.h"

int windowRows, windowColumns;
enum gameState {MainMenu, Settings, Leaderboard, Playing};
Map map;

int main() 
{	
	short gameState;

	initializeSystem();
	map.setDimensions(24, 30, 50);
	map.initialize();

	bool finished = false;

	gameState = Playing;
	while (!finished)
	{
		switch (gameState)
		{
		case MainMenu:
			printMainMenu();
			break;
		case Settings:
			printSettingsMenu();
			break;
		case Leaderboard:
			printLeaderboard();
			break;
		case Playing:
			map.printOnScreen();
			map.processInput();
			break;
		}
	}

	return 0;
}