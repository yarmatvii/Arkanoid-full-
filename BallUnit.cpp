#include "BallUnit.h"
#include "lib.h"
#include "constants.h"


BallUnit::BallUnit(Sprite* sprite, double x, double y, double width, double height) : DynamicUnit(sprite, x, y, width, height) {
}

void BallUnit::launch(double cursorX, double cursorY) {
	direction(normalize(cursorX - this->x(), cursorY - this->y()));
	maxVelocity(BALL_VELOCITY * BALL_VELOCITY_COEF);
	minVelocity(BALL_VELOCITY / BALL_VELOCITY_COEF);
	velocity(BALL_VELOCITY);
}