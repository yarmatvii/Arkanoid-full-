#pragma once

#include "DynamicUnit.h"
#include <vector>

class BallUnit : public DynamicUnit {
public:

	BallUnit(Sprite* sprite, int x, int y, int width, int height);
	void launch(int cursorX, int cursorY);

};

