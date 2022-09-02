#pragma once

#include "Unit.h"
#include <tuple>

class DynamicUnit : public Unit {
	// TODO getters & setters
public:

	double velocity;

	DynamicUnit(Sprite* sprite, int x, int y, int width, int height);

	virtual void setVelosity(double velocity);
	virtual void resetVelosity();

	virtual void setDirection(double x, double y);
	virtual void setDirection(std::pair<double, double> direction);
	virtual double getDirectionX();
	virtual double getDirectionY();


	virtual void update();
	virtual void draw();

	int directionStartX;
	int directionStartY;
	double directionX;
	double directionY;
	int directionStartTick;
};