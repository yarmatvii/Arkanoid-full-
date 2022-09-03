#define _WINDOWS
#include "UI.h"
#include "Framework.h"
#include "Tools.h"

UI::UI(int width, int height) {
	this->scoreboardStart = createSprite(getResourcePath("49-Breakout-Tiles.png").c_str());
	setSpriteSize(scoreboardStart, 75, 40);
}

int UI::getScore() {
	return this->score;
}

void UI::draw(int width, int height) {
	drawSprite(scoreboardStart, width - 100, 25);
}

void UI::update(int score) {

}

void UI::tick(int score, int width, int height) {

	this->update(score);
	this->draw(width, height);
}
