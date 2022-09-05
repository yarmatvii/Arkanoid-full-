#define _WINDOWS
#include <cmath>
#include <algorithm>
#include <iostream>
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

double DynamicUnit::velocity() {
	return std::clamp(_velocity, this->minVelocity(), this->maxVelocity());
}

void DynamicUnit::maxVelocity(double maxVelocity) {
	this->_maxVelocity = maxVelocity;
}

double DynamicUnit::maxVelocity() {
	return this->_maxVelocity > 0 ? this->_maxVelocity : HUGE_VAL;
}

void DynamicUnit::minVelocity(double minVelocity) {
	this->_minVelocity = minVelocity;
}

double DynamicUnit::minVelocity() {
	return this->_minVelocity > 0 ? this->_minVelocity : -HUGE_VAL;
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

void DynamicUnit::accelerate(double coef) {
	this->velocity(_velocity * (1 + coef));
}

void DynamicUnit::decelerate(double coef) {
	this->velocity(_velocity / (1 + coef));
}
