#ifndef GAME_MAP_H
#define GAME_MAP_H


#define MAX_ROWS			24
#define MAX_COLUMNS			30
#define MAX_NO_BOMBS		668
#define MAX_INPUT_SIZE		16
#define INPUT_SIZE			5
#define MAP_X				10
#define TEXT_INFO_X			5

struct Position
{
	unsigned short row, column;
};

struct Map
{
	unsigned short int rows, columns;
	char map[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool hasBomb[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool isCovered[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool isFlagged[MAX_ROWS + 1][MAX_COLUMNS + 1];
	unsigned short int noBombs;
	bool firstUncover;

	void initialize();
	void setSize(const unsigned short &rows, const unsigned short &columns, const unsigned short &noBombs);
	void generateMines();
	void printOnScreen();
	void print(const int &x, const int &y);
	void printInfo(const int &x, const int &y);
	void processInput();
	Position getPositionFromInput(const char *playerInput);
	void updateSquare(const Position &currentPosition, const char *playerInput);
	void uncoverAllSquares(const Position &currentPosition);
};

inline bool isLetterInRange(const char &currentLetter, const char &maxLetter);
inline bool isNumberInRange(const unsigned short &currentNumber, const unsigned short &maxNumber);

#endif