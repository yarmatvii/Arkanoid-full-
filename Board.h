#pragma once

#include "Framework.h"
#include "Unit.h"
#include "DynamicUnit.h"

#include <vector>

class Board {
public:

	int width;
	int height;
	std::vector<Unit*> units;
	DynamicUnit* platform;
	DynamicUnit* ball;
	Unit* coursor;


	Board(int width, int height);

	bool intersencts(Unit* other);
	bool addUnit(Unit* unit);
	bool addPlatform(DynamicUnit* platform);
	bool addBall(DynamicUnit* ball);
	void addCoursor(Unit* coursor);

	void update();
	void draw();
};