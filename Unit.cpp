
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
	if (linesLintersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x + this->width, this->y)) {
		return Side::TOP;
	}
	if (linesLintersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y + this->height, this->x + this->width, this->y + this->height)) {
		return Side::BOTTOM;
	}
	if (linesLintersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x, this->y, this->x, this->y + this->height)) {
		return Side::LEFT;
	}
	if (linesLintersects(other->getCenterX(), other->getCenterY(), this->getCenterX(), this->getCenterY(),
		this->x + this->width, this->y, this->x + this->width, this->y + this->height)) {
		return Side::RIGHT;
	}
}

bool Unit::linesLintersects(double p0_x, double p0_y, double p1_x, double p1_y,
	double p2_x, double p2_y, double p3_x, double p3_y)
{
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

	double s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		return true;
	}
	return false;
}

void Unit::draw() {
	setSpriteSize(sprite, width, height);
	drawSprite(sprite, x, y);
}