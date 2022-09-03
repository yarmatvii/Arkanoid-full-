#include "BallUnit.h"

#define BALL_VELOCITY 2

BallUnit::BallUnit(Sprite* sprite, double x, double y, double width, double height) :
	DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(double cursorX, double cursorY) {
	if (this->velocity() == 0) {
		int dx = cursorX - this->x;
		int dy = cursorY - this->y;
		long double len = sqrt(pow(dx, 2) + pow(dy, 2));

		this->velocity(BALL_VELOCITY);
		this->setDirection(dx / len, dy / len);
	}
}