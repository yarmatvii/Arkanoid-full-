#include "BlockUnit.h"

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height) : Unit(sprite, x, y, width, height)
{
	this->hp = 1;
}

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp) : Unit(sprite, x, y, width, height)
{
	this->hp = hp;
}

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp, int points) : Unit(sprite, x, y, width, height)
{
	this->hp = hp;
	this->points = points;
}

void BlockUnit::doDamage(int damage)
{
	hp = std::max(0, this->hp - damage);
}

bool BlockUnit::isAlive()
{
	return hp > 0;
}
