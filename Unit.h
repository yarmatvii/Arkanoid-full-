#pragma once

#include "Framework.h" 
#include "Side.h"

class Unit {
	double _x;
	double _y;
	
	double _height;
	double _width;
	double _minWidth;
	double _maxWidth;

	Sprite* _sprite;

public:
	Unit(Sprite* sprite, double x, double y, double width, double height);

	virtual Sprite* sprite();
	virtual void sprite(Sprite*);
	virtual double x();
	virtual void x(double x);
	virtual double y();
	virtual void y(double y);
	virtual void height(double height);
	virtual double height();
	virtual void width(double width);
	virtual double width();
	virtual void minWidth(double minWidth);
	virtual double minWidth();
	virtual void maxWidth(double maxWidth);
	virtual double maxWidth();
	virtual double centerX();
	virtual double centerY();

	virtual void move(double x, double y);
	virtual void moveRelative(double xRelative, double yRelative);

	virtual bool intersects(Unit* other);
	virtual Side collides(Unit* other);

	void increase(double coef);
	void decrease(double coef);
  
	virtual void draw();
};