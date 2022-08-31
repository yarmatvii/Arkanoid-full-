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
	virtual bool intersencts(Unit* other);
	virtual Side collides(Unit* other);
	virtual void draw();
};