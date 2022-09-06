#pragma once

#include "Unit.h"
#include <functional>
#include "Framework.h"
#include "DynamicUnit.h"

class Area : public Unit {
	std::function<void()> onEnter;
	std::function<void()> onLeave;
	bool isInside;

public:
	Area(Sprite* sprite, double x, double y, double width, double height, std::function<void()> onEnter, std::function<void()> onLeave);
	void update(Unit* unit);
};