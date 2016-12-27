#include								"../include/gamegraphics.h"
#include								<iostream>
#define GAME_TITLE						"Minesweeper"
#define COLOR_WHITE						Color::White
#define COLOR_GREY						32, 32, 32
#define PIXELS_BETWEEN_MENU_BUTTONS		100
#define MENU_TEXT_SIZE					35
#define PIXELS_PER_CHARACTER			22
#define WINDOW_FULLSCREEN				Style::Fullscreen
#define WINDOW_WINDOWED					Style::Default
#define ON								1
#define OFF								0

using namespace sf;

void GameGraphics::initialization()
{
	String title;
	Color defaultBackground(Color::White);
	Uint32 style = WINDOW_WINDOWED;

	this->videoMode = VideoMode::getDesktopMode();
	title = GAME_TITLE;

	this->window.create(videoMode, title, style);
	this->nightMode = OFF;
	this->backgroundColor = defaultBackground;
	
}

void GameGraphics::drawScreen(const bool &isPlaying)
{
	if (this->nightMode == 1)
	{
		this->backgroundColor = Color(COLOR_GREY);
	}
	else
	{
		this->backgroundColor = Color(COLOR_WHITE);
	}

	this->window.clear(this->backgroundColor);

	if (isPlaying == 0)
	{
		this->drawMenuOnScreen();
	}

	this->window.display();
}

void GameGraphics::drawMenuOnScreen()
{
	String menuText[] = { "PLAY", "SETTINGS", "LEADERBOARD", "QUIT" };
	String fontPath = "fonts/";
	Font textFont;
	Text currentText;
	Color textColor = Color::Black;
	unsigned int currentX, currentY;

	textFont.loadFromFile(fontPath + "OpenSans-Regular.ttf");
	this->setMenuTextPosition(currentX, currentY);
	if (this->nightMode == 1)
	{
		textColor = Color::White;
	}


	for (int i = 0; i < MAX_MENU_BUTTON; ++i, currentY += PIXELS_BETWEEN_MENU_BUTTONS)
	{
		this->textRect[i] = setIntRect(currentX, currentY, menuText[i].getSize() * PIXELS_PER_CHARACTER, MENU_TEXT_SIZE);
		this->menuText[i] = setText(currentX, currentY, textFont, menuText[i], MENU_TEXT_SIZE, textColor);
		this->window.draw(this->menuText[i]);
	}

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

bool isTextClicked(const IntRect &text, const Vector2i &mouseCoord)
{
	std::cout << text.left << " " << text.top << " " << text.width << " " << text.height << '\n';
	
	if (text.contains(mouseCoord))
	{
		return true;
	}
	else return false;
}