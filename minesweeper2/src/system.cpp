#include "../include/system.h"

void initializeSystem()
{
	srand(time(0));
	setCursorSize(80);
	setCursorVisible(false);
}

void quit()
{
	exit(EXIT_SUCCESS);
}

void gotoXY(const int &x, const int &y)
{
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void clearConsole(COORD position)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		// 32 = space
		FillConsoleOutputCharacter(hStdOut, (CHAR)32, csbi.dwSize.X * csbi.dwSize.Y, position, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, position, &count);
		SetConsoleCursorPosition(hStdOut, position);
	}
}

COORD getConsoleCursorPosition()
{
	COORD position = { 0, 0 };
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		position.X = csbi.dwCursorPosition.X;
		position.Y = csbi.dwCursorPosition.Y;
	}
	return position;
}

short getNumberOfDigits(short number)
{
	short noDigits = 0;
	do
	{
		noDigits++;
		number /= 10;
	} while (number);
	return noDigits;
}

void setCursorSize(const unsigned short int &size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	cursor.dwSize = size;

	SetConsoleCursorInfo(hStdOut, &cursor);
}

void setCursorVisible(const bool &show)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hStdOut, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(hStdOut, &cursorInfo);


}

void setFont(const unsigned short &x, const unsigned short &y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX *lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}

void setTextColor(const int &color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

void readPlayerInput(char *playerInput, const int &inputSizeLimit)
{
	std::cin.getline(playerInput, INPUT_SIZE);
	std::cin.clear();
}

void processMainMenuInput(char &gameState)
{
	char playerInput[MAX_INPUT_SIZE];
	readPlayerInput(playerInput, INPUT_SIZE_MAIN);
	if (playerInput[0] == '1')
	{
		gameState = 1;
	}
	else if (playerInput[0] == '2')
	{
		quit();
	}
}

void processSettingsInput(char &gameState, short &rows, short &columns, short &bombs)
{
	char playerInput[MAX_INPUT_SIZE];

	readPlayerInput(playerInput, INPUT_SIZE_SETTINGS);
	if (playerInput[0] < '1' || playerInput[0] > '6')
	{
		return;
	}
	gameState = 2;
	if (playerInput[0] == '1')
	{
		rows = EASY_NO_ROWS;
		columns = EASY_NO_COLUMNS;
		bombs = EASY_NO_BOMBS;
	}
	else if (playerInput[0] == '2')
	{
		rows = MEDIUM_NO_ROWS;
		columns = MEDIUM_NO_COLUMNS;
		bombs = MEDIUM_NO_BOMBS;
	}
	else if (playerInput[0] == '3')
	{
		rows = HARD_NO_ROWS;
		columns = HARD_NO_COLUMNS;
		bombs = HARD_NO_BOMBS;
	}
	else if (playerInput[0] == '4')
	{
		processCustomDimension(rows, columns, bombs);
	}
	else if (playerInput[0] == '5')
	{
		gameState = 0;
	}
}

void processCustomDimension(short &rows, short &columns, short &bombs)
{
	char playerInput[MAX_INPUT_SIZE];
	int x, y;
	x = MENU_POSITION_X; y = MENU_POSITION_Y;

	clearConsole();

	gotoXY(x, y);
	
	printf("Choose dimensions:");
	y += 1;
	COORD newConsolePosition = {0, 0};
	do
	{
		rows = 0;
		gotoXY(x, y);
		printf("Number of rows (%d->%d): ", MIN_ROWS, MAX_ROWS);
		newConsolePosition = getConsoleCursorPosition();
		readPlayerInput(playerInput, INPUT_SIZE_DIMENSION);
		if (strlen(playerInput) <= getNumberOfDigits(MAX_ROWS))
		{
			rows = getNumberFromString(playerInput);
		}
		if (rows < MIN_ROWS || rows > MAX_ROWS)
		{
			clearConsole(newConsolePosition);
		}
	} while (rows < MIN_ROWS || rows > MAX_ROWS);
	
	y += 1;
	do
	{
		columns = 0;
		gotoXY(x, y);
		printf("Number of columns (%d->%d):", MIN_COLUMNS, MAX_COLUMNS);
		newConsolePosition = getConsoleCursorPosition();
		readPlayerInput(playerInput, INPUT_SIZE_DIMENSION);
		if (strlen(playerInput) <= getNumberOfDigits(MAX_COLUMNS))
		{
			columns = getNumberFromString(playerInput);
		}
		if (columns < MIN_COLUMNS || columns > MAX_COLUMNS)
		{
			clearConsole(newConsolePosition);
		}
	} while (columns < MIN_COLUMNS || columns > MAX_COLUMNS);

	y += 1;
	short newMaxBombs = MAX_NO_BOMBS;
	if (MAX_NO_BOMBS >= rows * columns)
	{
		newMaxBombs = (6 * rows * columns) / 10;
	}
	do
	{
		bombs = 0;	
		gotoXY(x, y);
		printf("Number of bombs (%d -> %d):", MIN_NO_BOMBS, newMaxBombs);
		newConsolePosition = getConsoleCursorPosition();
		readPlayerInput(playerInput, INPUT_SIZE_DIMENSION);
		if (strlen(playerInput) <= getNumberOfDigits(newMaxBombs))
		{
			bombs = getNumberFromString(playerInput);
		}
		if (bombs < MIN_NO_BOMBS || bombs > newMaxBombs)
		{
			clearConsole(newConsolePosition);
		}
	} while (bombs < MIN_NO_BOMBS || bombs > newMaxBombs);
}

void printMainMenu()
{
	clearConsole();
	int x, y;
	x = MENU_POSITION_X; y = MENU_POSITION_Y;
	gotoXY(x, y);
	printf("Main Menu");
	
	char text[][20] = { "Play", "Quit"};
	int i;

	for (i = 0, y += 2; i < MAX_MAIN_MENU_BUTTONS; ++i, y += 2)
	{
		gotoXY(x, y);
		printf("%d. %s", i + 1, text[i]);
	}
	gotoXY(x, y);
	printf("Choose [1-%d]:", MAX_MAIN_MENU_BUTTONS);
}

void printSettingsMenu()
{
	clearConsole();
	int x, y;
	x = MENU_POSITION_X; y = MENU_POSITION_Y;
	gotoXY(x, y);
	printf("Play - Settings");
	y += 2;
	gotoXY(x, y);
	printf("Choose the difficulty:");
	char text[][50] = {"1. Easy - 9x9 tile grid, 10 mines", "2. Medium - 16x16 tile grid, 40 mines", "3. Hard - 16x30 tile grid, 99 mines",
						"4. Custom - Choose your own dimensions", "5. Back to main menu"};
	int i;
	for (y += 2, i = 0; i < 5; ++i, y += 2)
	{
		gotoXY(x, y);
		printf("%s", text[i]);
	}
	gotoXY(x, y);
	printf("Choose [1-5]:");
}

void printLeaderboard()
{
	exit(0);
}

unsigned short getNumberFromString(const char *string)
{
	unsigned short number = 0;

	for (int i = 0; string[i] && string[i] >= '0' && string[i] <= '9'; ++i)
	{
		number = number * 10 + string[i] - '0';
	}
	return number;
}