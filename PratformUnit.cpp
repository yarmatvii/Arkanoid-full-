#include "PratformUnit.h"
#include <algorithm>
#include <cmath>

#define PLATFORM_VELOCITY 4
#define PLATFORM_ANIMATION_LATENCY 10
#define PLATFORM_VELOCITY_COEF 2

PratformUnit::PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height) : DynamicUnit(sprites[0], x, y, width, height)
{
	this->sprites = sprites;
	this->currentSpriteIndex = 0;
	this->counter = 0;
	this->setMaxVelocity(PLATFORM_VELOCITY * PLATFORM_VELOCITY_COEF);
	this->setMinVelocity(PLATFORM_VELOCITY / PLATFORM_VELOCITY_COEF);
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
