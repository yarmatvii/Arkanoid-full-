#include "PratformUnit.h"
#include <algorithm>
#include <cmath>

#define PLATFORM_VELOCITY 1
#define PLATFORM_ANIMATION_LATENCY 10

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, int x, int y, int width, int height) :
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

void PratformUnit::increase(double �oef) {
	int offset = this->width * �oef / 2;
	this->moveRelative(-offset, 0);
	this->width *= 1 + �oef;
}

void PratformUnit::decrease(double �oef) {
	int decrement = this->width * �oef;
	this->x += decrement / 2;
	this->width /= 1 + �oef;
}
