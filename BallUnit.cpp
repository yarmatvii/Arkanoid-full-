#include "BallUnit.h"
#include "Tools.h"

#define BALL_VELOCITY 0.5

BallUnit::BallUnit(Sprite* sprite, int x, int y, int width, int height) :
	DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(int cursorX, int cursorY) {
	if (this->velocity == 0) {
		int dx = cursorX - this->x;
		int dy = cursorY - this->y;

		setVelosity(BALL_VELOCITY);
		setDirection(normalizeVector(dx, dy));
	}
}