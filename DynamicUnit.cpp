#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>
#include <algorithm>
#include <iostream>

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height) :
	Unit(sprite, x, y, width, height) {
	this->_maxVelocity = -1;
	this->_velocity = 0;
	this->_dx = 0;
	this->_dy = 0;
	this->_directionX = 0;
	this->_directionY = 0;
}

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity) :
	Unit(sprite, x, y, width, height) {
	this->_maxVelocity = -1;
	this->_velocity = velocity;
	this->_dx = 0;
	this->_dy = 0;
	this->_directionX = 0;
	this->_directionY = 0;
}

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity, double maxVelocity) :
	Unit(sprite, x, y, width, height) {
	this->_maxVelocity = maxVelocity;
	this->velocity(velocity);
	this->_dx = 0;
	this->_dy = 0;
	this->_directionX = 0;
	this->_directionY = 0;
}

void DynamicUnit::velocity(double velocity) {
	this->_velocity = velocity;

	this->_dx = this->velocity() * this->getDirectionX();
	this->_dy = this->velocity() * this->getDirectionY();
}

double DynamicUnit::velocity() {
	if (this->maxVelocity() >= 0) {
		return std::min(this->_velocity, this->maxVelocity());
	}
	return this->_velocity;
}

void DynamicUnit::maxVelocity(double maxVelocity) {
	this->_maxVelocity = maxVelocity;
}

double DynamicUnit::maxVelocity() {
	return this->_maxVelocity;
}

void DynamicUnit::setDirection(std::pair<double, double> direction) {
	this->setDirection(direction.first, direction.second);
}

void DynamicUnit::setDirection(double x, double y) {
	_directionX = x;
	_directionY = y;

	this->_dx = _directionX * this->velocity();
	this->_dy = _directionY * this->velocity();
}

double DynamicUnit::getDirectionX() {
	return this->_directionX;
}

double DynamicUnit::getDirectionY() {
	return this->_directionY;
}

void DynamicUnit::update() {
	if (this->velocity() != 0) {
		moveRelative(this->_dx, this->_dy);
		std::cout << this->_dx << " : " << this->_dy << std::endl;
	}
}

void DynamicUnit::draw() {
	Unit::draw();
}

void DynamicUnit::accelerate(double coef) {
	this->velocity(this->_velocity * (1 + coef));
}

void DynamicUnit::decelerate(double coef) {
	this->velocity(this->_velocity / (1 + coef));
}
