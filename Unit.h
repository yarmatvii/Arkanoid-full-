#pragma once

#include "Framework.h"

class Unit {
	// TODO getters & setters
public:

	Sprite* sprite;
	int x;
	int y;
	int width;
	int height;

	Unit(Sprite* sprite, int x, int y, int width, int height);

	virtual void move(int x, int y);
	virtual void moveRelative(int xRelative, int yRelative);
	virtual bool intersencts(Unit* other);
	virtual void draw();
};