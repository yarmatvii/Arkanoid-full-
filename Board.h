#pragma once

#include "Framework.h"
#include "Unit.h"
#include "DynamicUnit.h"
#include "PratformUnit.h"

#include <vector>

class Board {
public:

	int width;
	int height;
	std::vector<Unit*> units;
	PratformUnit* platform;
	DynamicUnit* ball;
	Unit* coursor;


	Board(int width, int height);

	bool intersencts(Unit* other);
	bool addUnit(Unit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(DynamicUnit* ball);
	void addCoursor(Unit* coursor);
	int checkIfCollideWithEdges(DynamicUnit* ball);

	void update();
	void draw();
};