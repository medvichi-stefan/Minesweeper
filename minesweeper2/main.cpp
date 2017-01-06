#include "include/stdafx.h"

using namespace std;

int windowRows, windowColumns;

Map map;

int main() 
{	
	initializeConsole();
	map.setSize(24, 30);
	map.initialize();
	map.print(35, 5);

	bool quit = false;

	while (quit == false)
	{
		Sleep(1500);
	}
	return 0;
}