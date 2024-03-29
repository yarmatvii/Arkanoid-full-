#include "BallUnit.h"
#include "Tools.h"

#define BALL_VELOCITY 4
#define MAX_BALL_VELOCITY 8
#define MIN_BALL_VELOCITY 2

BallUnit::BallUnit(Sprite* sprite, double x, double y, double width, double height) : DynamicUnit(sprite, x, y, width, height)
{
}

void BallUnit::launch(double cursorX, double cursorY)
{
	if (getVelocity() == 0)
	{
		int dx = cursorX - x;
		int dy = cursorY - y;

		setMaxVelocity(MAX_BALL_VELOCITY);
		setMinVelocity(MIN_BALL_VELOCITY);
		setVelocity(BALL_VELOCITY);
		setDirection(normalizeVector(dx, dy));
	}
}