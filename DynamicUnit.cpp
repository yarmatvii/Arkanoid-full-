#define _WINDOWS
#include "DynamicUnit.h"
#include <cmath>

DynamicUnit::DynamicUnit(Sprite* sprite, int x, int y, int width, int height) :
	Unit(sprite, x, y, width, height) {
	this->rotation = 0;
	this->velocity = 0;
	this->directionStartX = x;
	this->directionStartY = y;
}

DynamicUnit::DynamicUnit(Sprite* sprite, int x, int y, int width, int height, double rotation, double velocity) :
	Unit(sprite, x, y, width, height) {
	this->rotation = rotation;
	this->velocity = velocity;
}

void DynamicUnit::setVelosity(double velocity) {
	this->velocity = velocity;
}
void DynamicUnit::resetVelosity() {
	this->velocity = 0;
}
void DynamicUnit::setRotation(double rotation) {
	this->rotation = rotation;
	this->directionStartX = this->x;
	this->directionStartY = this->y;
	this->directionStartTick = getTickCount();

}
double DynamicUnit::getRotation() {
	return this->rotation;
}
void DynamicUnit::resetRotation() {
	this->rotation = 0;
}

void DynamicUnit::update() {
	int x = directionStartX + std::cos(rotation) * velocity * (getTickCount() - directionStartTick);
	int y = directionStartY + std::sin(rotation) * velocity * (getTickCount() - directionStartTick);
	move(x, y);
}

void DynamicUnit::draw() {
	update();
	Unit::draw();
}