#pragma once

#include "DynamicUnit.h"
#include <vector>

class BallUnit : public DynamicUnit {
public:
	BallUnit(Sprite* sprite, double x, double y, double width, double height);
	void launch(double cursorX, double cursorY);
};
