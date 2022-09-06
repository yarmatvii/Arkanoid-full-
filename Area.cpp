#include "Area.h"

Area::Area(Sprite* sprite, double x, double y, double width, double height, std::function<void()> onEnter, std::function<void()> onLeave) :
	Unit(sprite, x, y, width, height) {
	this->onEnter = onEnter;
	this->onLeave = onLeave;
	this->isInside = false;
}

void Area::update(Unit* unit) {
	bool intersects = this->intersects(unit);
	if (isInside == false && intersects == true) {
		this->onEnter();
	}
	if (isInside == true && intersects == false) {
		this->onLeave();
	}
	this->isInside = intersects;
}