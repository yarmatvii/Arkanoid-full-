#pragma once

#include "Framework.h" 
#include "Side.h"

class Unit {
public:
	double width;
	double maxWidth;

	Sprite* sprite;
	double x;
	double y;
	double height;

	Unit(Sprite* sprite, double x, double y, double width, double height);
	virtual double getCenterX();
	virtual double getCenterY();

	virtual void setWidth(double width);
	virtual double getWidth();

	virtual void setMaxWidth(double maxWidth);
	virtual double getMaxWidth();

	virtual void move(double x, double y);
	virtual void moveRelative(double xRelative, double yRelative);

	virtual bool intersects(Unit* other);
	virtual Side collides(Unit* other);

	void increase(double coef);
	void decrease(double coef);
  
	virtual void draw();
};