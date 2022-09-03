#include "PratformUnit.h"
#include <algorithm>
#include <cmath>

#define PLATFORM_VELOCITY 1
#define PLATFORM_ANIMATION_LATENCY 10

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height) :
	DynamicUnit(sprites[0], x, y, width, height) {
	this->sprites = sprites;
	this->currentSpriteIndex = 0;
	this->counter = 0;
	this->velocity = PLATFORM_VELOCITY;
}

void PratformUnit::update() {
	if (counter == 0) {
		this->sprite = sprites[currentSpriteIndex];
		currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
	}
	counter = (counter + 1) % PLATFORM_ANIMATION_LATENCY;
	DynamicUnit::update();
}

void PratformUnit::increase(double ñoef) {
	double newWidth = this->width * (1 + ñoef);
	this->moveRelative(-(newWidth - width) / 2, 0);
	this->width = newWidth;
}

void PratformUnit::decrease(double ñoef) {
	double newWidth = this->width / (1 + ñoef);
	this->moveRelative(-(newWidth - width) / 2, 0);
	this->width = newWidth;
}
