#ifndef	GAME_GRAPHICS_H
#define GAME_GRAPHICS_H
#pragma once

#include					<SFML/Graphics.hpp>

#define GAME_TITLE						"Minesweeper"
#define MAX_NO_GAME_PARTS				4
#define MAX_MENU_BUTTON					4
#define MAX_SETTINGS_TEXT				10				
#define MAX_NO_FONTS					5
#define MAX_NO_TEXT						10
#define MAX_INPUT_STRINGS				3
#define COLOR_WHITE						Color::White
#define COLOR_GREY						32, 32, 32
#define PIXELS_BETWEEN_MENU_BUTTONS		100
#define MENU_TEXT_SIZE					35
#define NORMAL_TEXT_SIZE				20
#define MAX_INPUT_FIELDS				4
#define SETTINGS_TITLE_SIZE				40
#define PIXELS_PER_CHARACTER			22
#define WINDOW_FULLSCREEN				Style::Fullscreen
#define WINDOW_WINDOWED					Style::Default
#define ON								1
#define OFF								0

using namespace sf;

struct GameGraphics
{
	RenderWindow window;
	VideoMode videoMode;
	Color backgroundColor;
	Font fonts[MAX_NO_FONTS];
	Text menuText[MAX_NO_GAME_PARTS][MAX_NO_TEXT];
	IntRect textRect[MAX_NO_GAME_PARTS][MAX_NO_TEXT];
	RectangleShape inputFields[MAX_INPUT_FIELDS];
	bool inputFieldFocus[MAX_INPUT_FIELDS];
	IntRect textBox[4];
	Text playerInputSettingsString[MAX_INPUT_FIELDS];

	bool nightMode;

	void drawScreen(const short int &gameState);

	void initialization();
	void initializeFonts();
	inline void initializeNightMode();
	void initializeMenuText();
	void initializeSettingsText();
	
	void setBackground(const Color &backgroundColor);

	void drawMenu();
	void drawSettings();
	void drawLeaderboard();
	void drawBoard();
	void drawTextOnScreen(const unsigned int &index, const unsigned int &posX, const unsigned int &posY, const String &text, const Font &font, const unsigned int &size, const Color &textColor);

	void updateNightMode(const short int &difficulty);
	void updateText(const short int &difficulty);
	void updateDifficultyText(const short int &difficulty);

	void setMenuTextPosition(unsigned int &posX, unsigned int &posY);

	Color getBackgroundColor();
};

bool isTextClicked(const IntRect &text, const Vector2i &mouseCoord);
IntRect setIntRect(const unsigned int &posX, const unsigned int &posY, const unsigned int &width, const unsigned int &height);
Text setText(const unsigned int &posX, const unsigned int &posY, const Font &textFont, const String &text, const unsigned int &textSize, const Color &textColor);
RectangleShape setRectangle(const unsigned int &posX, const unsigned int &posY, const unsigned int &width, const unsigned int &height, const Color &fillColor, const Color &outlineColor);

#endif