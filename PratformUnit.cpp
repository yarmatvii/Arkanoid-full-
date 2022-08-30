#include "PratformUnit.h"
#define PLATFORM_ANIMATION_LATENCY 10

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, int x, int y, int width, int height) :
	DynamicUnit(sprites[0], x, y, width, height) {
	this->sprites = sprites;
	this->currentSpriteIndex = 0;
	this->counter = 0;
}

void PratformUnit::update() {
	if (counter == 0) {
		this->sprite = sprites[currentSpriteIndex];
		currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
	}
	counter = (counter + 1) % PLATFORM_ANIMATION_LATENCY;
	DynamicUnit::update();
}
