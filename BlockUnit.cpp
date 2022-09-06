#include "BlockUnit.h"

BlockUnit::BlockUnit(Sprite* sprite, double x, double y, double width, double height, int hp, int points) : Unit(sprite, x, y, width, height) {
	this->_hp = hp;
	this->_baseHp = hp;
	this->_points = points;
}

int BlockUnit::hp() {	return this->_hp;
}

int BlockUnit::points() {
	return this->_points;
}

void BlockUnit::doDamage(int damage) {
	this->_hp = std::max(0, this->_hp - damage);
}

bool BlockUnit::isAlive() {
	return this->_hp > 0;
}


