#pragma once

#include "Unit.h"
#include <tuple>

class DynamicUnit : public Unit {
	// TODO getters & setters
public:

	double rotation;
	double velocity;

	DynamicUnit(Sprite* sprite, int x, int y, int width, int height);
	DynamicUnit(Sprite* sprite, int x, int y, int width, int height, double rotation, double velocity);

	virtual void setVelosity(double velocity);
	virtual void resetVelosity();
	//virtual double getDirectionX();
	//virtual double getDirectionY();

	virtual void setDirection(double x, double y);
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