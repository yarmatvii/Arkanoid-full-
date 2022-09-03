
#define _WINDOWS

#include "Unit.h"
#include <iostream>
#include "Tools.h"

Unit::Unit(Sprite* sprite, double x, double y, double width, double height) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

double Unit::getCenterX() {
	return this->x + this->width / 2;
}

double Unit::getCenterY() {
	return this->y + this->height / 2;
}

void Unit::move(double x, double y) {
	this->x = x;
	this->y = y;
}

void Unit::moveRelative(double xRelative, double yRelative) {
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

bool Unit::linesIntersects(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) {
	double s1x = p1x - p0x;
	double s1y = p1y - p0y;
	double s2x = p3x - p2x;
	double s2y = p3y - p2y;

	double s = (-s1y * (p0x - p2x) + s1x * (p0y - p2y)) / (-s2x * s1y + s1x * s2y);
	double t = (s2x * (p0y - p2y) - s2y * (p0x - p2x)) / (-s2x * s1y + s1x * s2y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
		return true;
	}
	return false;
}

void Unit::increase(double coef) {
	double newWidth = this->width * (1 + coef);
	this->moveRelative(-(newWidth - width) / 2, 0);
	this->width = newWidth;
}

void Unit::decrease(double coef) {
	double newWidth = this->width / (1 + coef);
	this->moveRelative(-(newWidth - width) / 2, 0);
	this->width = newWidth;
}

void Unit::draw() {
	setSpriteSize(sprite, width, height);
	drawSprite(sprite, x, y);
}