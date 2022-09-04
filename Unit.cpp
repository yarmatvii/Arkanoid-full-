
#define _WINDOWS

#include "Unit.h"
#include <iostream>
#include "Tools.h"

Unit::Unit(Sprite* sprite, double x, double y, double width, double height) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->_width = width;
	this->_maxWidth = -1;
	this->height = height;
}

double Unit::getCenterX() {
	return this->x + this->getWidth() / 2;
}

double Unit::getCenterY() {
	return this->y + this->height / 2;
}

void Unit::setWidth(double width) {
	this->_width = width;
}

double Unit::getWidth() {
	if (this->getMaxWidth() >= 0) {
		return std::min(this->getMaxWidth(), this->_width);
	}
	return this->_width;
}

void Unit::setMaxWidth(double maxWidth) {
	this->_maxWidth = maxWidth;
}

double Unit::getMaxWidth() {
	return this->_maxWidth;
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
	return !(this->x + this->getWidth() - 1 < other->x ||
		this->x > other->x + other->getWidth() - 1 ||
		this->y > other->y + other->height - 1 ||
		this->y + this->height - 1 < other->y
		);
}
Side Unit::collides(Unit* other) {
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x + this->getWidth(), this->y)) {
		return Side::TOP;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y + this->height, this->x + this->getWidth(), this->y + this->height)) {
		return Side::BOTTOM;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x, this->y + this->height)) {
		return Side::LEFT;
	}
	if (linesIntersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x + this->getWidth(), this->y, this->x + this->getWidth(), this->y + this->height)) {
		return Side::RIGHT;
	}
}

void Unit::increase(double coef) {
	double prevWith = this->getWidth();
	this->_width *= 1 + coef;
	this->moveRelative((prevWith - this->getWidth()) / 2, 0);
}

void Unit::decrease(double coef) {
	double prevWith = this->getWidth();
	this->_width /= 1 + coef;
	this->moveRelative((prevWith - this->getWidth()) / 2, 0);
}

void Unit::draw() {
	setSpriteSize(this->sprite, this->getWidth(), this->height);
	drawSprite(sprite, x, y);
}