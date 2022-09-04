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
	//this->sizeAbility = createSprite(getResourcePath("sizeAbility.png").c_str());
	//setSpriteSize(sizeAbility, 200, 100);

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
	char first;
	char second;
	char third;

	first = scoreToStr(score)[0];
	if (score > 9) second = scoreToStr(score)[1];
	if (score > 99) third = scoreToStr(score)[2];

	switch (first) {
	case '0':
		drawSprite(this->numbers[0], width - 88, 34);
		break;
	case '1':
		drawSprite(this->numbers[1], width - 88, 34);
		break;
	case '2':
		drawSprite(this->numbers[2], width - 88, 34);
		break;
	case '3':
		drawSprite(this->numbers[3], width - 88, 34);
		break;
	case '4':
		drawSprite(this->numbers[4], width - 88, 34);
		break;
	case '5':
		drawSprite(this->numbers[5], width - 88, 34);
		break;
	case '6':
		drawSprite(this->numbers[6], width - 88, 34);
		break;
	case '7':
		drawSprite(this->numbers[7], width - 88, 34);
		break;
	case '8':
		drawSprite(this->numbers[8], width - 88, 34);
		break;
	case '9':
		drawSprite(this->numbers[9], width - 88, 34);
		break;
	}

	if (score > 9) switch (second) {
	case '0':
		drawSprite(this->numbers[0], width - 70, 34);
		break;
	case '1':
		drawSprite(this->numbers[1], width - 70, 34);
		break;
	case '2':
		drawSprite(this->numbers[2], width - 70, 34);
		break;
	case '3':
		drawSprite(this->numbers[3], width - 70, 34);
		break;
	case '4':
		drawSprite(this->numbers[4], width - 70, 34);
		break;
	case '5':
		drawSprite(this->numbers[5], width - 70, 34);
		break;
	case '6':
		drawSprite(this->numbers[6], width - 70, 34);
		break;
	case '7':
		drawSprite(this->numbers[7], width - 70, 34);
		break;
	case '8':
		drawSprite(this->numbers[8], width - 70, 34);
		break;
	case '9':
		drawSprite(this->numbers[9], width - 70, 34);
		break;
	}

	if (score > 99) switch (third) {
	case '0':
		drawSprite(this->numbers[0], width - 52, 34);
		break;
	case '1':
		drawSprite(this->numbers[1], width - 52, 34);
		break;
	case '2':
		drawSprite(this->numbers[2], width - 52, 34);
		break;
	case '3':
		drawSprite(this->numbers[3], width - 52, 34);
		break;
	case '4':
		drawSprite(this->numbers[4], width - 52, 34);
		break;
	case '5':
		drawSprite(this->numbers[5], width - 52, 34);
		break;
	case '6':
		drawSprite(this->numbers[6], width - 52, 34);
		break;
	case '7':
		drawSprite(this->numbers[7], width - 52, 34);
		break;
	case '8':
		drawSprite(this->numbers[8], width - 52, 34);
		break;
	case '9':
		drawSprite(this->numbers[9], width - 52, 34);
		break;
	}
}

std::string UI::scoreToStr(int score) {
	return std::to_string(score);
}