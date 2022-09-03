#pragma once
#include "DynamicUnit.h"
#include <vector>

class PratformUnit : public DynamicUnit {
public:
	std::vector<Sprite*> sprites;
	int currentSpriteIndex;
	int counter;

	PratformUnit(std::vector<Sprite*> sprites, int x, int y, int width, int height);
	virtual void update();
	void increase(double ñoef);
	void decrease(double ñoef);
};
