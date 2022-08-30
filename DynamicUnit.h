#pragma once

#include "Unit.h"

class DynamicUnit : public Unit {
	// TODO getters & setters
public:

	double rotation;
	double velocity;

	DynamicUnit(Sprite* sprite, int x, int y, int width, int height);
	DynamicUnit(Sprite* sprite, int x, int y, int width, int height, double rotation, double velocity);

	void setVelosity(double velocity);
	void resetVelosity();
	void setRotation(double rotation);
	void resetRotation();

	virtual void update();
	virtual void draw();
};