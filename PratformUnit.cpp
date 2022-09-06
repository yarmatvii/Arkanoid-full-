#include <algorithm>
#include <cmath>

#include "PratformUnit.h"
#include "constants.h"

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height, double minX, double maxX) : DynamicUnit(sprites[0], x, y, width, height) {
	this->sprites = sprites;
	this->currentSpriteIndex = 0;
	this->animationCounter = 0;
	this->minX(minX);
	this->maxX(maxX);
	this->maxVelocity(PLATFORM_VELOCITY * PLATFORM_VELOCITY_COEF);
	this->minVelocity(PLATFORM_VELOCITY / PLATFORM_VELOCITY_COEF);
	this->maxWidth(width * PLATFOTM_WIDTH_COEF);
	this->velocity(PLATFORM_VELOCITY);
}

void PratformUnit::update() {
	if (animationCounter == 0) {
		sprite(sprites[currentSpriteIndex]);
		currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
	}
	animationCounter = (animationCounter + 1) % PLATFORM_ANIMATION_LATENCY;
	DynamicUnit::update();
}

double PratformUnit::x() {
	return std::clamp(DynamicUnit::x(), this->minX(), this->maxX());
}

double PratformUnit::maxX() {
	return this->_maxX >= 0 ? this->_maxX : HUGE_VAL;
}

void PratformUnit::maxX(double maxX) {
	this->_maxX = maxX;
}

double PratformUnit::minX() {
	return this->_minX >= 0 ? this->_minX : -HUGE_VAL;
}

void PratformUnit::minX(double minX) {
	this->_minX = minX;
}
