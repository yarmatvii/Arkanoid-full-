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
	Unit* cursor;


	Board(int width, int height);
	Board(int width, int height, Sprite* wall, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball);

	bool intersects(Unit* other);
	bool addUnit(Unit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(DynamicUnit* ball);
	void addcursor(Unit* cursor);
	Side checkIfCollideWithEdges(DynamicUnit* ball);
	Side checkIfCollideWithPlatform(DynamicUnit* other, DynamicUnit* platform);

	void update();
	void draw();

private:
	std::pair<double, double> reflectionVector(std::pair<double, double> d,
		std::pair<double, double> n);
};