#pragma once
#include "DynamicUnit.h"
#include <vector>

class PratformUnit : public DynamicUnit {
	std::vector<Sprite*> sprites;
	int currentSpriteIndex;
	int animationCounter;

public:
	PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height);
	virtual void update();
};
