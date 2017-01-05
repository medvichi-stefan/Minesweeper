#ifndef	GAME_H
#define GAME_H

#pragma once

#include							"gamegraphics.h"
#include							<iostream>

#define MIN_WIDTH_MAP				9
#define MIN_HEIGHT_MAP				9
#define MIN_BOMBS_MAP				10

using namespace sf;

struct Game
{
	short int gameState; //-1 - main-menu, 0 - playing, 1 - settings, 2 - leaderboard, 3 - quit
	short int difficulty; // 0 easy, 1 medium, 2 hard, 3 custom
	unsigned int noBombs;
	std::string inputStrings[MAX_INPUT_FIELDS];

	void initialization();

	void handleEvent(const Event &currentEvent, GameGraphics &graphics);
	void handleMainMenuEvent(const Event &currentEvent, GameGraphics &graphics);
	void handlePlayEvent(const Event &currentEvent, GameGraphics &graphics);
	void handleSettingsEvent(const Event &currentEvent, GameGraphics &graphics);
	void handleLeaderboardEvent(const Event &currentEvent, GameGraphics &graphics);

	bool Game::setCustomDifficulty(GameGraphics &graphics, const std::string inputStrings[]);
};

unsigned int getNumberFromString(const std::string &string);

#endif