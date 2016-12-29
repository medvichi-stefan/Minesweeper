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
	else if (currentEvent.type == Event::KeyPressed)
	{
		if (currentEvent.key.code == Keyboard::Escape)
		{
			graphics.window.close();
		}
	}
	else if (currentEvent.type == Event::TextEntered)
	{
		if (this->gameState == 1)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (graphics.inputFieldFocus[i] == 1)
				{
					if (currentEvent.text.unicode == '\b')
					{
						if (this->inputStrings[i].getSize() > 0)
							this->inputStrings[i].erase(this->inputStrings[i].getSize() - 1, 1);
					}
					else if (currentEvent.text.unicode >= '0' && currentEvent.text.unicode <= '9' && this->inputStrings[i].getSize() <= 2)
					{
						this->inputStrings[i].insert(this->inputStrings[i].getSize(), currentEvent.text.unicode);
					}
					graphics.drawTextOnScreen(i, graphics.textBox[i].left + 20, graphics.textBox[i].top + 3, this->inputStrings[i], graphics.fonts[0], NORMAL_TEXT_SIZE - 2, Color::Black);
					if (this->inputStrings[0].getSize() > 0 && this->inputStrings[1].getSize() > 0 && this->inputStrings[2].getSize() > 0)
					{
						graphics.updateDifficultyText(3);
						this->difficulty = 3;
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
			if (this->gameState == -1)
			{
				for (int i = 0; i < MAX_MENU_BUTTON; ++i)
				{
					if (isTextClicked(graphics.textRect[0][i], mouseCoord))
					{
						this->gameState = i;
					}
				}
			}
			else if (this->gameState == 1)
			{
				for (int i = 0; i < 2; ++i)
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
					for (int i = 2; i < 5; ++i)
					{
						if (isTextClicked(graphics.textRect[1][i], mouseCoord))
						{
							this->difficulty = i - 2;
							graphics.updateDifficultyText(i - 2);
						}
					}
					for (int i = 0; i < 3; ++i)
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
}