#include "BallUnit.h"
#include "Tools.h"

#define BALL_VELOCITY 2

BallUnit::BallUnit(Sprite* sprite, double x, double y, double width, double height) :
	DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(double cursorX, double cursorY) {
	if (this->velocity() == 0) {
		int dx = cursorX - this->x;
		int dy = cursorY - this->y;

		this->velocity(BALL_VELOCITY);
		this->setDirection(normalizeVector(dx, dy));
	}
}