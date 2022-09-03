#pragma once

#include "Framework.h" 
#include "Side.h"

class Unit {
	// TODO getters & setters
public:

	Sprite* sprite;
	double x;
	double y;
	double width;
	double height;

	Unit(Sprite* sprite, double x, double y, double width, double height);
	virtual double getCenterX();
	virtual double getCenterY();

	virtual void move(double x, double y);
	virtual void moveRelative(double xRelative, double yRelative);

	virtual bool intersects(Unit* other);
	virtual Side collides(Unit* other);
	bool linesIntersects(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y);

	void increase(double coef);
	void decrease(double coef);
  
	virtual void draw();
};