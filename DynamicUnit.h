#pragma once

#include "Unit.h"
#include <tuple>

class DynamicUnit : public Unit {
protected:
	double _velocity;
	double _maxVelocity;
	double _dx;
	double _dy;
	double _directionX;
	double _directionY;

public:

	DynamicUnit(Sprite* sprite, double x, double y, double width, double height);
	DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity);
	DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity, double maxVelocity);

	virtual void velocity(double velocity);
	virtual double velocity();

	virtual void maxVelocity(double velocity);
	virtual double maxVelocity();


	virtual void setDirection(double x, double y);
	virtual void setDirection(std::pair<double, double> direction);
	virtual double getDirectionX();
	virtual double getDirectionY();

	virtual void update();
	virtual void draw();
	virtual void accelerate(double coef);
	virtual void decelerate(double coef);

};