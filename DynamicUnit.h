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
	virtual double getDirectionX();
	virtual double getDirectionY();


	virtual void update();
	virtual void draw();
	virtual void accelerate(double coef);
	virtual void decelerate(double coef);

	double dx;
	double dy;
	double directionX;
	double directionY;
};