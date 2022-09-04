#pragma once

#include "Unit.h"
#include <utility>

class DynamicUnit : public Unit {
public:

	double velocity;
	double maxVelocity;
	double minVelocity;
	double dx;
	double dy;
	double directionX;
	double directionY;

	DynamicUnit(Sprite* sprite, double x, double y, double width, double height);
	DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity);
	DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity, double minVelocity, double maxVelocity);

	virtual void setVelocity(double velocity);
	virtual double getVelocity();

	virtual void setMaxVelocity(double velocity);
	virtual double getMaxVelocity();

	virtual void setMinVelocity(double velocity);
	virtual double getMinVelocity();

	virtual void setDirection(double x, double y);
	virtual void setDirection(std::pair<double, double> direction);
	virtual double getDirectionX();
	virtual double getDirectionY();

	virtual void update();
	virtual void draw();
	virtual void accelerate(double coef);
	virtual void decelerate(double coef);

};