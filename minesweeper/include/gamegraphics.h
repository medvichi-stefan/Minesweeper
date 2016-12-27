#ifndef	GAME_GRAPHICS_H
#define GAME_GRAPHICS_H
#pragma once

#include					<SFML/Graphics.hpp>

#define MAX_MENU_BUTTON	4

using namespace sf;

struct GameGraphics
{
	RenderWindow window;
	VideoMode videoMode;
	Color backgroundColor;
	Text menuText[MAX_MENU_BUTTON];
	IntRect textRect[MAX_MENU_BUTTON];
	
	bool nightMode;

	void drawScreen(const bool &isPlaying);
	void initialization();
	void setBackground(const Color &backgroundColor);
	void drawMenuOnScreen();
	void setMenuTextPosition(unsigned int &posX, unsigned int &posY);

	Color getBackgroundColor();
};

bool isTextClicked(const IntRect &text, const Vector2i &mouseCoord);
IntRect setIntRect(const unsigned int &posX, const unsigned int &posY, const unsigned int &width, const unsigned int &height);
Text setText(const unsigned int &posX, const unsigned int &posY, const Font &textFont, const String &text, const unsigned int &textSize, const Color &textColor);

#endif