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
		this->drawMap();
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
	this->initializeGameBoard();
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

void GameGraphics::initializeGameBoard()
{
	this->map.initializeDifficulties();

	this->map.width = 70 * this->videoMode.width / 100;
	this->map.height = 70 * this->videoMode.height / 100;

	this->map.initializeField();
}

void GameGraphics::initializeSettingsText()
{
	String text[] = { "SETTINGS", "Difficulty:", "Easy (10 mines, 9 x 9 tile grid)", "Medium (40 mines, 16 x 16 tile grid)",
					"Hard (99 mines, 16 x 30 tile grid)", "Custom:", "Night Mode: ", "ON", "OFF", "Back to main menu", "Rows",
					"Columns", "Bombs", "Rows: 9 -> 24", "Columns: 9 -> 30", "Bombs: 10 -> 500" };
	Color textColor = Color::Black, difficultyTextColor = Color::Green;

	unsigned int currentX, currentY;

	if (this->nightMode == ON)
	{
		textColor = Color::White;
	}

	currentX = this->videoMode.width / 2 - text[0].getSize()*PIXELS_PER_CHARACTER / 2; currentY = (10 * this->videoMode.height / 2) / 100;
	this->menuText[GAME_PART_SETTINGS][0] = setText(currentX, currentY, this->fonts[0], text[0], SETTINGS_TITLE_SIZE, textColor);
	
	currentX = 10 * this->videoMode.width / 100;
	currentY = (50 * this->videoMode.height / 2) / 100;
	this->menuText[GAME_PART_SETTINGS][1] = setText(currentX, currentY, this->fonts[0], text[1], NORMAL_TEXT_SIZE, textColor);

	int i;
	for (currentX += 100, i = 0; i < 3; ++i, currentY += 30)
	{
		this->textRect[GAME_PART_SETTINGS][i + 2] = setIntRect(currentX, currentY, text[i + 2].getSize() * (NORMAL_TEXT_SIZE - 10), MENU_TEXT_SIZE);
		this->menuText[GAME_PART_SETTINGS][i + 2] = setText(currentX, currentY, this->fonts[0], text[i + 2], NORMAL_TEXT_SIZE, textColor);
	}
	this->updateDifficultyText(0);

	currentX -= 100; currentY += 20;
	this->menuText[GAME_PART_SETTINGS][5] = setText(currentX, currentY, this->fonts[0], text[5], NORMAL_TEXT_SIZE, textColor);
	
	Color inputFieldColor = Color::White, outlineInputFieldColor = Color::Black;

	for (currentX += 100, i = 0; i < 3; ++i, currentX += 75)
	{
		this->inputFields[i] = setRectangle(currentX, currentY, 70, 30, inputFieldColor, outlineInputFieldColor);
		this->textBox[i] = setIntRect(currentX, currentY, 70, 30);
		this->inputFieldFocus[i] = 0;

		this->menuText[GAME_PART_SETTINGS][i + 10] = setText(currentX + 5, currentY - 20, this->fonts[0], text[i + 10], NORMAL_TEXT_SIZE - 5, textColor);
	}

	currentX = 10 * this->videoMode.width / 100;
	currentY += 35;
	
	for (i = 13; i < 16; ++i, currentX +=  this->menuText[GAME_PART_SETTINGS][i - 1].getString().getSize() * (NORMAL_TEXT_SIZE - 12) )
	{
		this->menuText[GAME_PART_SETTINGS][i] = setText(currentX, currentY, this->fonts[0], text[i], NORMAL_TEXT_SIZE - 5, textColor);
	}

	currentX = 10 * this->videoMode.width / 100;
	currentY += 50;
	this->menuText[GAME_PART_SETTINGS][6] = setText(currentX, currentY, this->fonts[0], text[6], NORMAL_TEXT_SIZE, textColor);
	currentX += 120;
	this->textRect[GAME_PART_SETTINGS][7] = setIntRect(currentX, currentY, text[7].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
	this->menuText[GAME_PART_SETTINGS][7] = setText(currentX, currentY, this->fonts[0], text[7], NORMAL_TEXT_SIZE, textColor);
	if (this->nightMode == OFF)
	{
		this->textRect[GAME_PART_SETTINGS][7] = setIntRect(currentX, currentY, text[8].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
		this->menuText[GAME_PART_SETTINGS][7].setString(text[8]);
	}

	currentX = 10 * this->videoMode.width / 100; currentY += 50;
	this->textRect[GAME_PART_SETTINGS][9] = setIntRect(currentX, currentY, text[9].getSize() * NORMAL_TEXT_SIZE, MENU_TEXT_SIZE);
	this->menuText[GAME_PART_SETTINGS][9] = setText(currentX, currentY, this->fonts[0], text[9], NORMAL_TEXT_SIZE, textColor);
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
		this->window.draw(this->playerInputString[i]);
	}
	
}

void GameGraphics::drawLeaderboard()
{

}

void GameGraphics::drawMap()
{
	this->window.draw(this->map.background);
	for (int i = 0; i < this->map.width; ++i)
	{
		for (int j = 0; j < this->map.height; ++j)
			this->window.draw(this->map.mapField[i][j].fieldRect);
	}
}

void GameGraphics::drawTextOnScreen(const unsigned int &index, const unsigned int &posX, const unsigned int &posY, const std::string &text, const Font &font, const unsigned int &size, const Color &textColor)
{
	Text textToWrite;
	textToWrite.setString(text);
	textToWrite.setPosition(posX, posY);
	textToWrite.setCharacterSize(size);
	textToWrite.setFont(font);
	textToWrite.setFillColor(textColor);
	this->playerInputString[index] = textToWrite;
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
		this->menuText[GAME_PART_SETTINGS][i].setFillColor(textColor);
	}
	this->menuText[GAME_PART_SETTINGS][2 + difficulty].setFillColor(Color::Blue);
}
void GameGraphics::setMenuTextPosition(unsigned int &posX, unsigned int &posY)
{
	posX = this->videoMode.width / 2 - 100;
	posY = 25 * this->videoMode.height / 100;
}

void Map::initializeMap(const VideoMode &videoMode)
{

	unsigned int posX, posY, width, height;

	posX = videoMode.width / 2 - this->width / 2; posY = 100;
	width = this->width;
	height = this->height;

	this->background = setRectangle(posX, posY, width, height, Color(COLOR_GREY_LIGHT), Color::Black);
	this->initializeField();
}

void Map::initializeDifficulties()
{
	this->difficulty = 0;
	this->predefinedBackgroundSize[0][0] = this->predefinedBackgroundSize[0][1] = 9;
	this->predefinedBackgroundSize[1][0] = this->predefinedBackgroundSize[1][1] = 16;
	this->predefinedBackgroundSize[2][0] = 16; this->predefinedBackgroundSize[2][1] = 30;
}

void Map::initializeField()
{
	int rows, columns;
	unsigned int currentX, currentY, width, height;

	rows = this->predefinedBackgroundSize[this->difficulty][0];
	columns = this->predefinedBackgroundSize[this->difficulty][1];

	currentX = this->width; currentY = this->height;

	width = PIXELS_WIDTH;
	height = PIXELS_HEIGHT;

	for (int i = 0; i < rows; ++i, currentX += width)
	{
		for (int j = 0; j < columns; ++j, currentY += height)
		{
			this->mapField[i][j].initialize(currentX, currentY, width, height);
		}
	}
}

void Map::updateGameBoardSize()
{
	if (this->difficulty == 0)
	{
		this->width = this->predefinedBackgroundSize[0][0];
		this->height = this->predefinedBackgroundSize[0][1];
	}
	else if (this->difficulty == 1)
	{
		this->width = this->predefinedBackgroundSize[1][0];
		this->height = this->predefinedBackgroundSize[1][1];
	}
	else if (this->difficulty == 2)
	{
		this->width = this->predefinedBackgroundSize[1][0];
		this->height = this->predefinedBackgroundSize[2][1];
	}
}

void Field::initialize(const unsigned int &posX, const unsigned int &posY, const unsigned int &fieldWidth, const unsigned int &fieldHeight)
{
	Color fillColor = Color::Blue;
	RectangleShape newRect = setRectangle(posX, posY, fieldWidth, fieldHeight, fillColor, Color(COLOR_GREY_LIGHT));
	Texture newTexture;
	Sprite newSprite;
	
	this->hasBomb = false;
	this->covered = true;
	this->fieldRect = newRect;
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