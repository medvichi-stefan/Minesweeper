#ifndef GAME_GRAPHICS_H
#define GAME_GRAPHICS_H
#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

struct GameGraphics
{
	RenderWindow window;
	Color backgroundColor;

	void initialization();
	void setBackground(Color backgroundColor);
	void drawScreen();
};
#endif