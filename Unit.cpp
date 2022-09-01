
#define _WINDOWS

#include "Unit.h"
#include <iostream>

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
	//double a = (this->getCenterY() - other->getCenterY()) / (this->getCenterX() - other->getCenterX());
	//double b = this->getCenterY() - this->getCenterX() * a;
	//
	//double y = a * other->x + b;
	//if (other->y <= y && y <= other->y + other->height) {
	//	std::cout << "right";
	//	return Side::RIGHT;
	//}
	//
	//y = a * other->x + other->width + b;
	//if (other->y <= y && y <= other->y + other->height) {
	//	std::cout << "left";
	//	return Side::LEFT;
	//}
	//
	//double x = (other->y - b) / a;
	//if (other->x <= x && x <= other->x + width) {
	//	std::cout << "top";
	//	return Side::TOP;
	//}
	//
	//x = (other->y + other->height - b) / a;
	//if (other->x <= x && x <= other->x + width) {
	//	std::cout << "bottom";
	//	return Side::BOTTOM;
	//}

	if ((other->y + other->height + 1 > this->y) &&
		(other->y + other->height < this->y + 16) &&
		(other->x + other->width + 1 > this->x) &&
		(other->x - 1 < this->x + this->width)) {
		return Side::TOP;
	}

	if ((other->y - 1 < this->y + this->height) &&
		(other->y > this->y + this->height - 16) &&
		(other->x + other->width + 1 > this->x) &&
		(other->x - 1 < this->x + this->width)) {
		return Side::BOTTOM;
	}

	if ((other->x - 1 < this->x + this->width) &&
		(other->x > this->x + this->width - 16) &&
		(other->y + other->height > this->y) &&
		(other->y < this->y + this->height)) {
		std::cout << "right";
		return Side::RIGHT;
	}

	if ((other->x + other->width + 1 > this->x) &&
		(other->x + other->width < this->x + 16) &&
		(other->y + other->height > this->y) &&
		(other->y < this->y + this->height)) {
		std::cout << "left";
		return Side::LEFT;
	}
}

void Unit::draw() {
	setSpriteSize(sprite, width, height);
	drawSprite(sprite, x, y);

}