#pragma once
#include "Unit.h"
#include <cmath>

class BlockUnit : public Unit {
protected:
	int hp;
	int baseHp;
	int points;

public:
	BlockUnit(Sprite* sprite, double x, double y, double width, double height);
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp);
	BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp, int points);

	void doDamage(int damage);
	bool isAlive();
	int getHp();
	int getPoints();	
};
