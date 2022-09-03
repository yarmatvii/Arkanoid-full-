#pragma once

#include "Unit.h"
#include <tuple>

class DynamicUnit : public Unit {
	double _velocity;
	double _dx;
	double _dy;
	double _directionX;
	double _directionY;

public:

	DynamicUnit(Sprite* sprite, double x, double y, double width, double height);

	virtual void velocity(double velocity);
	virtual double velocity();

	virtual void setDirection(double x, double y);
	virtual void setDirection(std::pair<double, double> direction);
	virtual double getDirectionX();
	virtual double getDirectionY();

	virtual void update();
	virtual void draw();
	virtual void accelerate(double coef);
	virtual void decelerate(double coef);

};