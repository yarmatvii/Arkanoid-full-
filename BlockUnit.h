#pragma once
#include "Unit.h"
#include <cmath>

class BlockUnit : public Unit {
	int _hp;
	int _baseHp;
	int _points;

public:
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp = 0, int points = 0);

	int hp();
	int points();

	void doDamage(int damage);
	bool isAlive();
};
