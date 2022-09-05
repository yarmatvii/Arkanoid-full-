#include "BallUnit.h"
#include "tools.h"
#include "constants.h"


BallUnit::BallUnit(Sprite* sprite, double x, double y, double width, double height) : DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(double cursorX, double cursorY) {
	direction(normalize(cursorX - this->x(), cursorY - this->y()));
	maxVelocity(MAX_BALL_VELOCITY);
	minVelocity(MIN_BALL_VELOCITY);
	velocity(BALL_VELOCITY);
}