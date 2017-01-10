#include "include/stdafx.h"

using namespace std;

int windowRows, windowColumns;
enum gameState {MainMenu, Settings, Leaderboard, Playing};
Map map;

int main() 
{	
	char playerInput[16];
	short gameState;

	initializeConsole();
	map.setSize(24, 30, 10);
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