#pragma once
#include								"../include/gamegraphics.h"
#include								<iostream>

using namespace sf;

void GameGraphics::drawScreen(const short int &gameState)
{
	this->window.clear(this->backgroundColor);

	switch (gameState)
	{
	case -1:
		this->drawMenu();
		break;
	case 0:
		this->drawBoard();
		break;
	case 1:
		this->drawSettings();
		break;
	case 2:
		this->drawLeaderboard();
		break;
	case 3:
		this->window.close();
		break;
	default:
		this->drawMenu();
	}

	this->window.display();
}

void GameGraphics::initialization()
{
	String title;
	Color defaultBackground(Color::White);
	Uint32 style = WINDOW_WINDOWED;

	this->videoMode = VideoMode::getDesktopMode();
	title = GAME_TITLE;

	this->window.create(videoMode, title, style);
	this->backgroundColor = defaultBackground;
	this->initializeNightMode();
	this->initializeFonts();
	this->initializeMenuText();
	this->initializeSettingsText();
}

void GameGraphics::initializeFonts()
{
	Font textFont;
	textFont.loadFromFile("fonts/OpenSans-Regular.ttf");
	this->fonts[0] = textFont;
}

inline void GameGraphics::initializeNightMode()
{
	this->nightMode = OFF;
}

void GameGraphics::initializeMenuText()
{
	String text[] = { "PLAY", "SETTINGS", "LEADERBOARD", "QUIT" };
	Color textColor = Color::Black;
	unsigned int currentX, currentY;

	this->setMenuTextPosition(currentX, currentY);

	if (this->nightMode == ON)
	{
		textColor = Color::White;
	}

	for (int i = 0; i < MAX_MENU_BUTTON; ++i, currentY += PIXELS_BETWEEN_MENU_BUTTONS)
	{
		this->textRect[0][i] = setIntRect(currentX, currentY, text[i].getSize() * PIXELS_PER_CHARACTER, MENU_TEXT_SIZE);
		this->menuText[0][i] = setText(currentX, currentY, this->fonts[0], text[i], MENU_TEXT_SIZE, textColor);

	}
}

void GameGraphics::initializeSettingsText()
{
	String text[] = { "SETTINGS", "Difficulty:", "Easy (10 mines, 9 x 9 tile grid)", "Medium (40 mines, 16 x 16 tile grid)", "Hard (99 mines, 16 x 30 tile grid)", "Custom:", "Night Mode: ", "ON", "OFF", "Back to main menu" };
	Color textColor = Color::Black, difficultyTextColor = Color::Green;

	unsigned int currentX, currentY;

	if (this->nightMode == ON)
	{
		textColor = Color::White;
	}

	currentX = this->videoMode.width / 2 - text[0].getSize()*PIXELS_PER_CHARACTER / 2; currentY = (10 * this->videoMode.height / 2) / 100;
	this->menuText[1][0] = setText(currentX, currentY, this->fonts[0], text[0], SETTINGS_TITLE_SIZE, textColor);
	
	currentX = 10 * this->videoMode.width / 100;
	currentY = (50 * this->videoMode.height / 2) / 100;
	this->menuText[1][1] = setText(currentX, currentY, this->fonts[0], text[1], NORMAL_TEXT_SIZE, textColor);

	int i;
	for (currentX += 100, i = 0; i < 3; ++i, currentY += 30)
	{
		this->textRect[1][i + 2] = setIntRect(currentX, currentY, text[i + 2].getSize() * (NORMAL_TEXT_SIZE - 10), MENU_TEXT_SIZE);
		this->menuText[1][i + 2] = setText(currentX, currentY, this->fonts[0], text[i + 2], NORMAL_TEXT_SIZE, textColor);
	}
	this->updateDifficultyText(0);

	currentX -= 100; currentY += 20;
	this->menuText[1][5] = setText(currentX, currentY, this->fonts[0], text[5], NORMAL_TEXT_SIZE, textColor);
	
	Color inputFieldColor = Color::White, outlineInputFieldColor = Color::Black;

	for (currentX += 100, i = 0; i < 3; ++i, currentX += 75)
	{
		this->inputFields[i] = setRectangle(currentX, currentY, 70, 30, inputFieldColor, outlineInputFieldColor);
		this->textBox[i] = setIntRect(currentX, currentY, 70, 30);
		this->inputFieldFocus[i] = 0;
	}

	currentX = 10 * this->videoMode.width / 100;
	currentY += 50;
	this->menuText[1][6] = setText(currentX, currentY, this->fonts[0], text[6], NORMAL_TEXT_SIZE, textColor);
	currentX += 120;
	this->textRect[1][7] = setIntRect(currentX, currentY, text[7].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
	this->menuText[1][7] = setText(currentX, currentY, this->fonts[0], text[7], NORMAL_TEXT_SIZE, textColor);
	if (this->nightMode == OFF)
	{
		this->textRect[1][7] = setIntRect(currentX, currentY, text[8].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
		this->menuText[1][7].setString(text[8]);
	}

	currentX = 10 * this->videoMode.width / 100; currentY += 50;
	this->textRect[1][9] = setIntRect(currentX, currentY, text[9].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
	this->menuText[1][9] = setText(currentX, currentY, this->fonts[0], text[9], NORMAL_TEXT_SIZE, textColor);
}

void GameGraphics::drawMenu()
{
	for (int i = 0; i < MAX_MENU_BUTTON; ++i)
	{
		this->window.draw(this->menuText[0][i]);
	}
}

void GameGraphics::drawSettings()
{
	for (int i = 0; i < MAX_SETTINGS_TEXT; ++i)
	{
		this->window.draw(this->menuText[1][i]);
	}
	for (int i = 0; i < 3; ++i)
	{
		this->window.draw(this->inputFields[i]);
		this->window.draw(this->playerInputSettingsString[i]);
	}
	
}

void GameGraphics::drawLeaderboard()
{

}

void GameGraphics::drawBoard()
{

}

void GameGraphics::drawTextOnScreen(const unsigned int &index, const unsigned int &posX, const unsigned int &posY, const String &text, const Font &font, const unsigned int &size, const Color &textColor)
{
	Text textToWrite;
	textToWrite.setString(text);
	textToWrite.setPosition(posX, posY);
	textToWrite.setCharacterSize(size);
	textToWrite.setFont(font);
	textToWrite.setFillColor(textColor);
	this->playerInputSettingsString[index] = textToWrite;
}

void GameGraphics::updateNightMode(const short int &difficulty)
{
	if (this->nightMode == ON)
	{
		this->backgroundColor = Color(COLOR_GREY);
	}
	else
	{
		this->backgroundColor = Color(COLOR_WHITE);
	}
	this->updateText(difficulty);
}

void GameGraphics::updateText(const short int &difficulty)
{
	Color textColor = Color::Black;
	this->menuText[1][7].setString("OFF");
	if (this->nightMode == ON)
	{
		textColor = Color::White;
		this->menuText[1][7].setString("ON");
	}

	for (int i = 0; i < MAX_NO_GAME_PARTS; ++i)
	{
		for (int j = 0; j < MAX_NO_TEXT; ++j)
		{
			this->menuText[i][j].setFillColor(textColor);
		}
	}
	this->updateDifficultyText(difficulty);
}

void GameGraphics::updateDifficultyText(const short int &difficulty)
{
	Color textColor = Color::Black;
	if (this->nightMode == ON) textColor = Color::White;

	for (int i = 2; i <= 5; ++i)
	{
		this->menuText[1][i].setFillColor(textColor);
	}
	this->menuText[1][2 + difficulty].setFillColor(Color::Blue);
}
void GameGraphics::setMenuTextPosition(unsigned int &posX, unsigned int &posY)
{
	posX = this->videoMode.width / 2 - 100;
	posY = 25 * this->videoMode.height / 100;
}

IntRect setIntRect(const unsigned int &posX, const unsigned int &posY, const unsigned int &width, const unsigned int &height)
{
	IntRect newRect(posX, posY, width, height);
	return newRect;
}

Text setText(const unsigned int &posX, const unsigned int &posY, const Font &textFont, const String &text, const unsigned int &textSize, const Color &textColor)
{
	Text newText;
	newText.setPosition(posX, posY);
	newText.setFont(textFont);
	newText.setString(text);
	newText.setCharacterSize(textSize);
	newText.setFillColor(textColor);
	return newText;
}

RectangleShape setRectangle(const unsigned int &posX, const unsigned int &posY, const unsigned int &width, const unsigned int &height, const Color &fillColor, const Color &outlineColor)
{
	RectangleShape newRect;
	Vector2f size;
	size.x = width; size.y = height;
	newRect.setPosition(posX, posY);
	newRect.setFillColor(fillColor);
	newRect.setOutlineColor(outlineColor);
	newRect.setSize(size);
	newRect.setOutlineThickness(1);
	return newRect;
}

bool isTextClicked(const IntRect &text, const Vector2i &mouseCoord)
{
	if (text.contains(mouseCoord))
	{
		return true;
	}
	else return false;
}