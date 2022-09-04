#define _WINDOWS
#include "UI.h"
#include "Framework.h"
#include "Tools.h"

UI::UI(int width, int height)
{
	this->scoreboardStart = createSprite(getResourcePath("49-Breakout-Tiles.png").c_str());
	setSpriteSize(scoreboardStart, 96, 44);

	this->speedAbility = createSprite(getResourcePath("speedAbilityOnRMB.png").c_str());
	setSpriteSize(speedAbility, 200, 100);

	this->zero = createSprite(getResourcePath("numbers/0.png").c_str());
	setSpriteSize(zero, 16, 16);
	this->one = createSprite(getResourcePath("numbers/1.png").c_str());
	setSpriteSize(one, 16, 16);
	this->two = createSprite(getResourcePath("numbers/2.png").c_str());
	setSpriteSize(two, 16, 16);
	this->three = createSprite(getResourcePath("numbers/3.png").c_str());
	setSpriteSize(three, 16, 16);
	this->four = createSprite(getResourcePath("numbers/4.png").c_str());
	setSpriteSize(four, 16, 16);
	this->five = createSprite(getResourcePath("numbers/5.png").c_str());
	setSpriteSize(five, 16, 16);
	this->six = createSprite(getResourcePath("numbers/6.png").c_str());
	setSpriteSize(six, 16, 16);
	this->seven = createSprite(getResourcePath("numbers/7.png").c_str());
	setSpriteSize(seven, 16, 16);
	this->eight = createSprite(getResourcePath("numbers/8.png").c_str());
	setSpriteSize(eight, 16, 16);
	this->nine = createSprite(getResourcePath("numbers/9.png").c_str());
	setSpriteSize(nine, 16, 16);

	this->addNumber(zero);
	this->addNumber(one);
	this->addNumber(two);
	this->addNumber(three);
	this->addNumber(four);
	this->addNumber(five);
	this->addNumber(six);
	this->addNumber(seven);
	this->addNumber(eight);
	this->addNumber(nine);
}

void UI::draw(int width, int height, int score, bool showboard)
{
	drawSprite(this->scoreboardStart, width - 110, 20);
	if (showboard) {
		drawSprite(this->speedAbility, width - 205, height - 105);
		//drawSprite(this->sizeAbility, 5, height - 105);
	}
	drawNumber(width, height, score);
}

void UI::update(int score)
{

}

void UI::tick(int score, int width, int height, bool showboard)
{
	this->update(score);
	this->draw(width, height, score, showboard);
}

void UI::addNumber(Sprite* num)
{
	this->numbers.push_back(num);
}

void UI::drawNumber(int width, int height, int score)
{
	std::string score_str = std::to_string(score);

	int x = width - 88;
	int y = 34;

	for (auto it = begin(score_str); it != end(score_str); it++, x += 18)
	{
		switch (*it) {
		case '0':
			drawSprite(this->numbers[0], x, y);
			break;
		case '1':
			drawSprite(this->numbers[1], x, y);
			break;
		case '2':
			drawSprite(this->numbers[2], x, y);
			break;
		case '3':
			drawSprite(this->numbers[3], x, y);
			break;
		case '4':
			drawSprite(this->numbers[4], x, y);
			break;
		case '5':
			drawSprite(this->numbers[5], x, y);
			break;
		case '6':
			drawSprite(this->numbers[6], x, y);
			break;
		case '7':
			drawSprite(this->numbers[7], x, y);
			break;
		case '8':
			drawSprite(this->numbers[8], x, y);
			break;
		case '9':
			drawSprite(this->numbers[9], x, y);
			break;
		}
	}
}