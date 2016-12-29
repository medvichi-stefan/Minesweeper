#ifndef	GAME_H
#define GAME_H

#pragma once

#include							"gamegraphics.h"
#include							<iostream>

using namespace sf;

struct Game
{
	short int gameState; //-1 - main-menu, 0 - playing, 1 - settings, 2 - leaderboard, 3 - quit
	short int difficulty;
	String inputStrings[MAX_INPUT_FIELDS];

	void initialization();
	void handleEvent(const Event &currentEvent, GameGraphics &graphics);
};


#endif