#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>
#include <iostream>

DynamicUnit::DynamicUnit(Sprite* sprite, int x, int y, int width, int height) :
	Unit(sprite, x, y, width, height) {
	this->velocity = 0;
	this->directionStartX = x;
	this->directionStartY = y;
}

void DynamicUnit::setVelosity(double velocity) {
	this->velocity = velocity;
}
void DynamicUnit::resetVelosity() {
	this->velocity = 0;
}

void DynamicUnit::setDirection(double x, double y) {
	directionX = x;
	directionY = y;

	directionStartX = this->x;
	directionStartY = this->y;
	directionStartTick = getTickCount();
}

double DynamicUnit::getDirectionX() {
	return this->directionX;
}

double DynamicUnit::getDirectionY() {
	return this->directionY;
}

void DynamicUnit::update() {
	if (velocity != 0) {
		int x = directionStartX + directionX * velocity * (getTickCount() - directionStartTick);
		int y = directionStartY + directionY * velocity * (getTickCount() - directionStartTick);
		move(x, y);
	}
}

void DynamicUnit::draw() {
	update();
	Unit::draw();
}

