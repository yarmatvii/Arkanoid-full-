#pragma once
#include "Unit.h"
#include <cmath>

class BlockUnit : public Unit {
public:
	int hp;
	int baseHp;
	int points;

	BlockUnit(Sprite* sprite, double x, double y, double width, double height);
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp);
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp, int points);

	void doDamage(int damage);
	bool isAlive();
};
