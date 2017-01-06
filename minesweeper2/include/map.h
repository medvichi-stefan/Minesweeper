#ifndef GAME_MAP_H
#define GAME_MAP_H


#define MAX_ROWS			24
#define MAX_COLUMNS			30
#define MAX_NO_BOMBS		500

struct Map
{
	unsigned short int rows, columns;
	char map[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool hasBomb[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool isCovered[MAX_ROWS + 1][MAX_COLUMNS + 1];
	unsigned short int noBombs;

	void initialize();
	void setSize(const unsigned short &rows, const unsigned short &columns);
	void print(const int &x, const int &y);
};

#endif