#include "BlockUnit.h"

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height) : Unit(sprite, x, y, width, height) {
	this->hp = 1;
}

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp) : Unit(sprite, x, y, width, height) {
	this->hp = hp;
}

void BlockUnit::doDamage(int damage) {
	this->hp = std::max(0, this->hp - damage);
}

bool BlockUnit::isAlive() {
	return this->hp > 0;
}
