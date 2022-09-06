#pragma once
#include "DynamicUnit.h"
#include <vector>

class PratformUnit : public DynamicUnit {
	std::vector<Sprite*> sprites;
	int currentSpriteIndex;
	int animationCounter;
	double _minX;
	double _maxX;

public:
	PratformUnit(std::vector<Sprite*> sprites, double x, double y, double width, double height, double minX = -1, double maxX = -1);
	virtual void update();

	virtual double x();
	virtual double maxX();
	virtual void maxX(double maxX);
	virtual double minX();
	virtual void minX(double minX);
};
