#include "Board.h"
#include <algorithm>

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
}

bool Board::intersencts(Unit* other) {
	for (auto unit : units) {
		if (unit->intersencts(other)) {
			return true;
		}
	}
	return false;
}

bool Board::addUnit(Unit* unit) {
	if (intersencts(unit)) {
		return false;
	}
	this->units.push_back(unit);
	return true;
}

bool Board::addPlatform(DynamicUnit* platform) {
	if (!addUnit(platform)) {
		return false;
	}
	this->platform = platform;
}

bool Board::addBall(DynamicUnit* ball) {
	if (!addUnit(ball)) {
		return false;
	}
	this->ball = ball;
}

void Board::addCoursor(Unit* coursor) {
	this->coursor = coursor;
}

//void Board::movePlatformRight(int xrelative) {
//	int newX = std::min(this->width, this->platform->x + xrelative);
//	this->platform->move(newX, this->platform->y);
//};
//
//void Board::movePlatformLeft(int xrelative) {
//	int newX = std::max(0, this->platform->x - xrelative);
//	this->platform->move(newX, this->platform->y);
//
//};

void Board::update() {
	ball->update();
	platform->update();

}

void Board::draw() {
	for (auto unit : units) {
		unit->draw();
	}
	coursor->draw();

}


