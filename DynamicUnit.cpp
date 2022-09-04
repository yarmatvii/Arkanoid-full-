#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>
#include <algorithm>
#include <iostream>

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height) :
	Unit(sprite, x, y, width, height) {
	this->maxVelocity = -1;
	this->velocity = 0;
	this->dx = 0;
	this->dy = 0;
	this->directionX = 0;
	this->directionY = 0;
}

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity) :
	Unit(sprite, x, y, width, height) {
	this->maxVelocity = -1;
	this->velocity = velocity;
	this->dx = 0;
	this->dy = 0;
	this->directionX = 0;
	this->directionY = 0;
}

DynamicUnit::DynamicUnit(Sprite* sprite, double x, double y, double width, double height, double velocity, double maxVelocity) :
	Unit(sprite, x, y, width, height) {
	this->velocity = maxVelocity;
	this->setVelocity(velocity);
	this->dx = 0;
	this->dy = 0;
	this->directionX = 0;
	this->directionY = 0;
}

void DynamicUnit::setVelocity(double velocity) {
	this->velocity = velocity;

	this->dx = this->getVelocity() * this->getDirectionX();
	this->dy = this->getVelocity() * this->getDirectionY();
}

double DynamicUnit::getVelocity() {
	if (this->getMaxVelocity() >= 0) {
		return std::min(this->velocity, this->getMaxVelocity());
	}
	return this->velocity;
}

void DynamicUnit::setMaxVelocity(double maxVelocity) {
	this->maxVelocity = maxVelocity;
}

double DynamicUnit::getMaxVelocity() {
	return this->maxVelocity;
}

void DynamicUnit::setDirection(std::pair<double, double> direction) {
	this->setDirection(direction.first, direction.second);
}

void DynamicUnit::setDirection(double x, double y) {
	directionX = x;
	directionY = y;

	this->dx = directionX * this->getVelocity();
	this->dy = directionY * this->getVelocity();
}

double DynamicUnit::getDirectionX() {
	return this->directionX;
}

double DynamicUnit::getDirectionY() {
	return this->directionY;
}

void DynamicUnit::update() {
	if (this->getVelocity() != 0) {
		moveRelative(this->dx, this->dy);
	}
}

void DynamicUnit::draw() {
	Unit::draw();
}

void DynamicUnit::accelerate(double coef) {
	this->setVelocity(this->velocity * (1 + coef));
}

void DynamicUnit::decelerate(double coef) {
	this->setVelocity(this->velocity / (1 + coef));
}
