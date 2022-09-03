#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>
#include <iostream>

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height) :
	Unit(sprite, x, y, width, height) {
	this->_velocity = 0;
	this->_dx = 0;
	this->_dy = 0;
}

void DynamicUnit::velocity(double velocity) {
	this->_velocity = velocity;
	this->_dx = velocity * this->_directionX;
	this->_dy = velocity * this->_directionY;
}

double DynamicUnit::velocity() {
	return this->_velocity;
}

void DynamicUnit::setDirection(std::pair<double, double> direction) {
	directionX = direction.first;
	directionY = direction.second;

	dx = directionX * velocity;
	dy = directionY * velocity;
}

void DynamicUnit::setDirection(double x, double y) {
	_directionX = x;
	_directionY = y;

	this->_dx = _directionX * _velocity;
	this->_dy = _directionY * _velocity;
}

double DynamicUnit::getDirectionX() {
	return this->_directionX;
}

double DynamicUnit::getDirectionY() {
	return this->_directionY;
}

void DynamicUnit::update() {
	if (_velocity != 0) {
		moveRelative(this->_dx, this->_dy);
	}
}

void DynamicUnit::draw() {
	Unit::draw();
}

void DynamicUnit::accelerate(double coef) {
	this->velocity(this->velocity() * (1 + coef));
}

void DynamicUnit::decelerate(double coef) {
	this->velocity(this->velocity() / (1 + coef));
}
