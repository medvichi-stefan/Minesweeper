#include "../include/gamegraphics.h"
#define GAME_TITLE "Minesweeper"
using namespace sf;

void GameGraphics::initialization()
{
	VideoMode videoMode;
	String title;

	videoMode = VideoMode::getDesktopMode();
	title = GAME_TITLE;
	this->window.create(videoMode, title);
	this->backgroundColor = Color::White;
}

void GameGraphics::setBackground(Color colorBackground)
{
	this->backgroundColor = colorBackground;
}

void GameGraphics::drawScreen()
{
	this->window.clear(this->backgroundColor);
	this->window.display();
}