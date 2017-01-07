#include "include/stdafx.h"

using namespace std;

int windowRows, windowColumns;

Map map;

int main() 
{	
	char playerInput[16];
	short gameState;

	initializeConsole();
	map.setSize(24, 30, 10);
	map.initialize();

	bool finished = false;

	gameState = 0;
	while (!finished)
	{
		if (gameState == 0)
		{
			map.printOnScreen();
			map.processInput();
		}
		else
		{
			printOnScreen(gameState);
		}
	}

	return 0;
}