
#define _WINDOWS
#include <algorithm>

#include "Unit.h"
#include "lib.h"

Unit::Unit(Sprite* sprite, double x, double y, double width, double height) {
	this->_sprite = sprite;
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_maxWidth = -1;
	this->_height = height;
}

Sprite* Unit::sprite() {
	return this->_sprite;
};

void Unit::sprite(Sprite* sprite) {
	this->_sprite = sprite;
}

double Unit::x() {
	return this->_x;
}

void Unit::x(double x) {
	this->_x = x;
}

double Unit::y() {
	return this->_y;
}

void Unit::y(double y) {
	this->_y = y;
}

void Unit::height(double height) {
	this->_height = height;
}

double Unit::height() {
	return this->_height;
}

void Unit::width(double width) {
	this->_width = width;
}

double Unit::width() {
	return std::clamp(this->_width, this->minWidth(), this->maxWidth());
}

void Unit::minWidth(double minWidth) {
	this->_minWidth = minWidth;
}

double Unit::minWidth() {
	return this->_minWidth >= 0 ? this->_minWidth : -HUGE_VAL;
}

void Unit::maxWidth(double maxWidth) {
	this->_maxWidth = maxWidth;
}

double Unit::maxWidth() {
	return this->_maxWidth >= 0 ? this->_maxWidth : HUGE_VAL;
}

double Unit::Unit::centerX() {
	return this->x() + this->width() / 2;
}

double Unit::centerY() {
	return this->y() + this->height() / 2;
}

void Unit::move(double x, double y) {
	this->x(x);
	this->y(y);
}

void Unit::moveRelative(double xRelative, double yRelative) {
	this->x(this->x() + xRelative);
	this->y(this->y() + yRelative);
}

bool Unit::intersects(Unit* other) {
	return !(this->x() + this->width() <= other->x() ||
		this->x() >= other->x() + other->width() ||
		this->y() >= other->y() + other->height() ||
		this->y() + this->height() <= other->y()
		);
}

Side Unit::collides(Unit* other) {
	if (linesIntersection(other->centerX(), other->centerY(), this->centerX(), this->centerY(),
		this->x(), this->y(), this->x() + this->width(), this->y())) {
		return Side::TOP;
	}
	if (linesIntersection(other->centerX(), other->centerY(), this->centerX(), this->centerY(),
		this->x(), this->y() + this->height(), this->x() + this->width(), this->y() + this->height())) {
		return Side::BOTTOM;
	}
	if (linesIntersection(other->centerX(), other->centerY(), this->centerX(), this->centerY(),
		this->x(), this->y(), this->x(), this->y() + this->height())) {
		return Side::LEFT;
	}
	if (linesIntersection(other->centerX(), other->centerY(), this->centerX(), this->centerY(),
		this->x() + this->width(), this->y(), this->x() + this->width(), this->y() + this->height())) {
		return Side::RIGHT;
	}
}

void Unit::increase(double coef) {
	double prevWidth = this->width();
	this->_width *= (1 + coef);
	moveRelative((prevWidth - width()) / 2, 0);
}

void Unit::decrease(double coef) {
	double prevWidth = this->width();
	this->_width /= (1 + coef);
	moveRelative((prevWidth - width()) / 2, 0);
}

void Unit::draw() {
	setSpriteSize(this->sprite(), this->width(), this->height());
	drawSprite(this->sprite(), this->x(), this->y());
}