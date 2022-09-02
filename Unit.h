#pragma once

#include "Framework.h" 
#include "Side.h"

class Unit {
	// TODO getters & setters
public:

	Sprite* sprite;
	int x;
	int y;
	int width;
	int height;

	Unit(Sprite* sprite, int x, int y, int width, int height);
	virtual int getCenterX();
	virtual int getCenterY();


	virtual void move(int x, int y);
	virtual void moveRelative(int xRelative, int yRelative);
	virtual bool intersects(Unit* other);
	virtual Side collides(Unit* other);
	bool linesIntersects(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y);
	virtual void draw();
};