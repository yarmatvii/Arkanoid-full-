#pragma once

#include "Unit.h"

class DynamicUnit : public Unit {
	// TODO getters & setters
public:

	double rotation;
	double velocity;

	DynamicUnit(Sprite* sprite, int x, int y, int width, int height);
	DynamicUnit(Sprite* sprite, int x, int y, int width, int height, double rotation, double velocity);

	virtual void setVelosity(double velocity);
	virtual void resetVelosity();
	virtual void setRotation(double rotation);
	virtual void resetRotation();
	virtual double getRotation();

	virtual void update();
	virtual void draw();

private:
	double directionStartX;
	double directionStartY;
	int directionStartTick;
};