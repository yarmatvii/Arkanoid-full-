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
	bool linesLintersects(double p0_x, double p0_y, double p1_x, double p1_y,
		double p2_x, double p2_y, double p3_x, double p3_y);
	virtual void draw();
};