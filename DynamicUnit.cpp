#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>
#include <iostream>

DynamicUnit::DynamicUnit(Sprite* sprite, int x, int y, int width, int height) :
	Unit(sprite, x, y, width, height) {
	this->velocity = 0;
	dx = 0;
	dy = 0;
}

void DynamicUnit::setVelosity(double velocity) {
	this->velocity = velocity;
}

void DynamicUnit::resetVelosity() {
	this->velocity = 0;
}

void DynamicUnit::setDirection(std::pair<double, double> direction) {
	directionX = direction.first;
	directionY = direction.second;

	dx = directionX * velocity;
	dy = directionY * velocity;
}

void DynamicUnit::setDirection(double x, double y) {
	directionX = x;
	directionY = y;

	dx = directionX * velocity;
	dy = directionY * velocity;
}

double DynamicUnit::getDirectionX() {
	return this->directionX;
}

double DynamicUnit::getDirectionY() {
	return this->directionY;
}

void DynamicUnit::update() {
	if (velocity != 0) {
		moveRelative(this->dx, this->dy);
	}
}

void DynamicUnit::draw() {
	Unit::draw();
}

void DynamicUnit::accelerate(double coef) {
	this->velocity *= 1 + coef;
}

void DynamicUnit::decelerate(double coef) {
	this->velocity *= 1 - coef;
}
