#pragma once
#include "Unit.h"
#include <cmath>

class BlockUnit : public Unit {
protected:
	int hp;
	int baseHp;

public:
	BlockUnit(Sprite* sprite, double x, double y, double width, double height);
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp);

	void doDamage(int damage);
	bool isAlive();
	int getHp();
};
