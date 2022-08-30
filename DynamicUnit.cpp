#include "DynamicUnit.h"
#include <cmath>

DynamicUnit::DynamicUnit(Sprite* sprite, int x, int y, int width, int height) :
	Unit(sprite, x, y, width, height) {
	this->rotation = 0;
	this->velocity = 0;
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
}
void DynamicUnit::resetRotation() {
	this->rotation = 0;
}

void DynamicUnit::update() {
	int dx = velocity * std::cos(rotation);
	int dy = velocity * std::sin(rotation);
	moveRelative(dx, dy);
}

void DynamicUnit::draw() {
	update();
	Unit::draw();
}