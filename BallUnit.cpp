#include "BallUnit.h"

#define BALL_VELOCITY 2

BallUnit::BallUnit(Sprite* sprite, int x, int y, int width, int height) :
	DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(int cursorX, int cursorY) {
	if (this->velocity == 0) {
		int dx = cursorX - this->x;
		int dy = cursorY - this->y;
		long double len = sqrt(pow(dx, 2) + pow(dy, 2));

		setVelosity(BALL_VELOCITY);
		setDirection(dx / len, dy / len);
	}
}