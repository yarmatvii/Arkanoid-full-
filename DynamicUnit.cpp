#define _WINDOWS
#include <cmath>
#include <algorithm>
#include <numeric>

#include "DynamicUnit.h"

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity, double minVelocity, double maxVelocity) : Unit(sprite, x, y, width, height) {
	this->_maxVelocity = maxVelocity;
	this->_minVelocity = minVelocity;
	this->velocity(velocity);
	this->_dx = 0;
	this->_dy = 0;
	this->_directionX = 0;
	this->_directionY = 0;
}

void DynamicUnit::velocity(double velocity) {
	this->_velocity = velocity;

	this->_dx = directionX() * this->velocity();
	this->_dy = directionY() * this->velocity();
}

void DynamicUnit::resetVelocity() {
	this->_velocity = 0;

	this->_dx = 0;
	this->_dy = 0;
}

double DynamicUnit::velocity() {
	return std::clamp(_velocity, this->minVelocity(), this->maxVelocity());
}

void DynamicUnit::maxVelocity(double maxVelocity) {
	this->_maxVelocity = maxVelocity;
}

double DynamicUnit::maxVelocity() {
	return this->_maxVelocity >= 0 ? this->_maxVelocity : HUGE_VAL;
}

void DynamicUnit::minVelocity(double minVelocity) {
	this->_minVelocity = minVelocity;
}

double DynamicUnit::minVelocity() {
	return this->_minVelocity >= 0 ? this->_minVelocity : -HUGE_VAL;
}

void DynamicUnit::direction(std::pair<double, double> direction) {
	this->direction(direction.first, direction.second);
}

void DynamicUnit::direction(double x, double y) {
	this->_directionX = x;
	this->_directionY = y;

	this->_dx = this->directionX() * this->velocity();
	this->_dy = this->directionY() * this->velocity();
}

double DynamicUnit::directionX() {
	return this->_directionX;
}

double DynamicUnit::directionY() {
	return this->_directionY;
}

void DynamicUnit::update() {
	if (this->velocity() != 0) {
		this->moveRelative(_dx, _dy);
	}
}

Side DynamicUnit::reflect(Unit* other) {
	switch (other->collides(this)) {
	case Side::TOP:
		this->move(this->x(), other->y() - this->height() - 1);
		this->direction(this->directionX(), -this->directionY());
		return Side::TOP;
	case Side::BOTTOM:
		this->move(this->x(), other->y() + other->height() + 1);
		this->direction(this->directionX(), -this->directionY());
		return Side::BOTTOM;
	case Side::RIGHT:
		this->move(other->x() + other->width() + 1, this->y());
		this->direction(-this->directionX(), this->directionY());
		return Side::RIGHT;
	case Side::LEFT:
		this->move(other->x() - this->width() - 1, this->y());
		this->direction(-this->directionX(), this->directionY());
		return Side::LEFT;
	};
}

void DynamicUnit::accelerate(double coef) {
	this->velocity(_velocity * (1 + coef));
}

void DynamicUnit::decelerate(double coef) {
	this->velocity(_velocity / (1 + coef));
}
