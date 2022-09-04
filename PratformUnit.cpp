#include "PratformUnit.h"
#include <algorithm>
#include <cmath>

#define PLATFORM_VELOCITY 4
#define MAX_PLATFORM_VELOCITY 8
#define PLATFORM_ANIMATION_LATENCY 10
#define MAX_WIDTH_COEF 2

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height) : DynamicUnit(sprites[0], x, y, width, height)
{
	this->sprites = sprites;
	this->currentSpriteIndex = 0;
	this->counter = 0;
	this->setMaxVelocity(MAX_PLATFORM_VELOCITY);
	this->setMaxWidth(MAX_WIDTH_COEF * width);
	this->setVelocity(PLATFORM_VELOCITY);
}

void PratformUnit::update()
{
	if (counter == 0)
	{
		sprite = sprites[currentSpriteIndex];
		currentSpriteIndex = (currentSpriteIndex + 1) % sprites.size();
	}
	counter = (counter + 1) % PLATFORM_ANIMATION_LATENCY;
	DynamicUnit::update();
}
