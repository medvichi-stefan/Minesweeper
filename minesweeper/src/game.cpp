#pragma once
#include "../include/game.h"

using namespace sf;

void Game::initialization()
{
	this->difficulty = 0;
	this->gameState = -1; //main-menu
	for (int i = 0; i < MAX_INPUT_FIELDS; ++i)
		this->inputStrings[i] = "";

}

void Game::handleEvent(const Event &currentEvent, GameGraphics &graphics)
{
	if (currentEvent.type == Event::Closed)
	{
		graphics.window.close();
	}

	switch (this->gameState)
	{
	case -1:
		handleMainMenuEvent(currentEvent, graphics);
		break;
	case 0:
		handlePlayEvent(currentEvent, graphics);
		break;
	case 1:
		handleSettingsEvent(currentEvent, graphics);
		break;
	case 2:
		handleLeaderboardEvent(currentEvent, graphics);
		break;
	}
}

void Game::handleMainMenuEvent(const Event &currentEvent, GameGraphics &graphics)
{
	if (currentEvent.type == Event::KeyPressed)
	{
		if (currentEvent.key.code == Keyboard::Escape)
		{
			graphics.window.close();
		}
	}
	else if (currentEvent.type == Event::MouseButtonPressed)
	{
		/* DEBUG */
		Vector2i mouseCoord;
		Vector2i windowCoord;
		mouseCoord.x = currentEvent.mouseButton.x;
		mouseCoord.y = currentEvent.mouseButton.y;
		std::cout << mouseCoord.x << " " << mouseCoord.y << '\n';
		windowCoord = graphics.window.getPosition();
		std::cout << windowCoord.x << ' ' << windowCoord.y << '\n';
		/**/
		for (int i = 0; i < MAX_MENU_BUTTON; ++i)
		{
			if (isTextClicked(graphics.textRect[0][i], mouseCoord))
			{
				this->gameState = i;
			}
			if (i == 0)
			{
				graphics.map.initializeMap(graphics.videoMode);
			}
		}
	}
}

void Game::handlePlayEvent(const Event &currentEvent, GameGraphics &graphics)
{

}

void Game::handleSettingsEvent(const Event &currentEvent, GameGraphics &graphics)
{
	std::string string;
	if (currentEvent.type == Event::TextEntered)
	{
		for (int i = 0; i < MAX_INPUT_FIELDS_SETTINGS; ++i)
		{
			if (graphics.inputFieldFocus[i] == 1)
			{
				if (currentEvent.text.unicode == '\b')
				{
					if (this->inputStrings[i].size() > 0)
						this->inputStrings[i].erase(this->inputStrings[i].size() - 1, 1);
				}
				else if (currentEvent.text.unicode >= '0' && currentEvent.text.unicode <= '9' && this->inputStrings[i].size() < 2)
				{
					string = currentEvent.text.unicode;
					this->inputStrings[i].append(string);
				}

				graphics.drawTextOnScreen(i, graphics.textBox[i].left + 20, graphics.textBox[i].top + 3, this->inputStrings[i], graphics.fonts[0], NORMAL_TEXT_SIZE - 2, Color::Black);
				
				if (this->inputStrings[0].size() > 0 && this->inputStrings[1].size() > 0 && this->inputStrings[2].size() > 0)
				{
					if ( this->setCustomDifficulty(graphics, this->inputStrings) )
					{
						graphics.updateDifficultyText(3);
						this->difficulty = 3;
						graphics.map.difficulty = 3;
					}
					else
					{
						graphics.updateDifficultyText(0);
						this->difficulty = 0;
						graphics.map.difficulty = 0;
					}
				}
			}
		}
	}
	else if (currentEvent.type == Event::MouseButtonPressed)
	{
		/* DEBUG */
		Vector2i mouseCoord;
		Vector2i windowCoord;
		mouseCoord.x = currentEvent.mouseButton.x;
		mouseCoord.y = currentEvent.mouseButton.y;
		std::cout << mouseCoord.x << " " << mouseCoord.y << '\n';
		windowCoord = graphics.window.getPosition();
		std::cout << windowCoord.x << ' ' << windowCoord.y << '\n';
		/**/
		if (currentEvent.mouseButton.button == Mouse::Button::Left)
		{
			for (int i = 0; i < MAX_INPUT_FIELDS; ++i)
				graphics.inputFieldFocus[i] = 0;

			if (isTextClicked(graphics.textRect[1][9], mouseCoord))
			{
				this->gameState = -1;
			}
			else if (isTextClicked(graphics.textRect[1][7], mouseCoord))
			{
				graphics.nightMode = 1 - graphics.nightMode;
				graphics.updateNightMode(this->difficulty);
			}
			else
			{
				for (int i = 2; i < 2 + MAX_NO_DIFFICULTIES; ++i)
				{
					if (isTextClicked(graphics.textRect[1][i], mouseCoord))
					{
						this->difficulty = i - 2;
						graphics.map.difficulty = i - 2;
						graphics.updateDifficultyText(i - 2);	
					}
				}
				for (int i = 0; i < MAX_INPUT_FIELDS; ++i)
				{
					if (isTextClicked(graphics.textBox[i], mouseCoord))
					{
						graphics.inputFieldFocus[i] = 1;
					}
				}
			}
		}
	}
}

void Game::handleLeaderboardEvent(const Event &currentEvent, GameGraphics &graphics)
{

}

bool Game::setCustomDifficulty(GameGraphics &graphics, const std::string inputStrings[])
{
	unsigned int customWidth, customHeight, customBombs;
	customWidth = getNumberFromString(inputStrings[0]);
	customHeight = getNumberFromString(inputStrings[1]);
	customBombs = getNumberFromString(inputStrings[2]);

	std::cout << "CUSTOM:\n";
	std::cout << customWidth << ' ' << customHeight << ' ' << customBombs << '\n';

	if (customWidth >= MIN_WIDTH_MAP && customWidth <= MAX_WIDTH_MAP 
		&&customHeight >= MIN_HEIGHT_MAP && customHeight <= MAX_HEIGHT_MAP 
		&& customBombs >= MIN_BOMBS_MAP && customBombs <= MAX_BOMBS_MAP)
	{
		graphics.map.width = customWidth;
		graphics.map.height = customHeight;
		this->noBombs = customBombs;
		return true;
	}
	else
	{
		return false;
	}
}

unsigned int getNumberFromString(const std::string &string)
{
	unsigned int currentNumber = 0;

	for (int i = 0; string[i]; ++i)
	{
		currentNumber = currentNumber * 10 + string[i] - '0';
	}
	return currentNumber;
}