#pragma once
#include "Unit.h"
#include <cmath>

class BlockUnit : public Unit {
public:
	BlockUnit(Sprite* sprite, int x, int y, int width, int height);
	BlockUnit(Sprite* sprite, int x, int y, int width, int height, int hp);

	void doDamage(int damage);
	bool isAlive();

private:
	int hp;
};
