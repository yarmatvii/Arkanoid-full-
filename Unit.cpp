
#define _WINDOWS

#include "Unit.h"

Unit::Unit(Sprite* sprite, int x, int y, int width, int height) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Unit::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void Unit::moveRelative(int xRelative, int yRelative) {
	this->x += xRelative;
	this->y += yRelative;
}

bool Unit::intersencts(Unit* other) {
	return !(this->x + this->width - 1 < other->x ||
		this->x > other->y + other->width - 1 ||
		this->y > other->y + other->height - 1 ||
		this->y + this->height - 1 < other->y
		);

}

void Unit::draw() {
	setSpriteSize(sprite, width, height);
	drawSprite(sprite, x, y);

}