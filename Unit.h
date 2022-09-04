#pragma once

#include "Framework.h" 
#include "Side.h"

class Unit {
	// TODO getters & setters
	double _width;
	double _maxWidth;

public:

	Sprite* sprite;
	double x;
	double y;
	double height;

	Unit(Sprite* sprite, double x, double y, double width, double height);
	virtual double getCenterX();
	virtual double getCenterY();

	virtual void width(double width);
	virtual double width();

	virtual void maxWidth(double maxWidth);
	virtual double maxWidth();

	virtual void move(double x, double y);
	virtual void moveRelative(double xRelative, double yRelative);

	virtual bool intersects(Unit* other);
	virtual Side collides(Unit* other);

	void increase(double coef);
	void decrease(double coef);
  
	virtual void draw();
};