
#define _WINDOWS

#include "Unit.h"
#include <iostream>
#include "Tools.h"

Unit::Unit(Sprite* sprite, int x, int y, int width, int height) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int Unit::getCenterX() {
	return this->x + this->width / 2;
}

int Unit::getCenterY() {
	return this->y + this->height / 2;
}

void Unit::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void Unit::moveRelative(int xRelative, int yRelative) {
	this->x += xRelative;
	this->y += yRelative;
}

bool Unit::intersects(Unit* other) {
	return !(this->x + this->width - 1 < other->x ||
		this->x > other->x + other->width - 1 ||
		this->y > other->y + other->height - 1 ||
		this->y + this->height - 1 < other->y
		);
}
Side Unit::collides(Unit* other) {
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x + this->width, this->y)) {
		return Side::TOP;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y + this->height, this->x + this->width, this->y + this->height)) {
		return Side::BOTTOM;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x, this->y + this->height)) {
		return Side::LEFT;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x + this->width, this->y, this->x + this->width, this->y + this->height)) {
		return Side::RIGHT;
	}
}

void Unit::draw() {
	setSpriteSize(sprite, width, height);
	drawSprite(sprite, x, y);
}