#pragma once

#include "Unit.h"
#include <tuple>

class DynamicUnit : public Unit {
	double _velocity;
	double _minVelocity;
	double _maxVelocity;
	double _dx;
	double _dy;
	double _directionX;
	double _directionY;

public:
	DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity = 0, double minVelocity = -1, double maxVelocity = -1);

	virtual void velocity(double velocity);
	virtual double velocity();
	virtual void resetVelocity();
	virtual void maxVelocity(double velocity);
	virtual double maxVelocity();
	virtual void minVelocity(double velocity);
	virtual double minVelocity();

	virtual void direction(double x, double y);
	virtual void direction(std::pair<double, double> direction);
	virtual double directionX();
	virtual double directionY();

	virtual Side reflect(Unit* other);
	virtual void accelerate(double coef);
	virtual void decelerate(double coef);

	virtual void update();
};