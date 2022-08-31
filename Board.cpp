#include "Board.h"
#include <algorithm>
#include "iostream"
#include <numbers>

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

bool Board::addPlatform(PratformUnit* platform) {
	if (!addUnit(platform)) {
		return false;
	}
	this->platform = platform;
	return true;
}

bool Board::addBall(DynamicUnit* ball) {
	if (!addUnit(ball)) {
		return false;
	}
	this->ball = ball;
	return true;
}

void Board::addCoursor(Unit* coursor) {
	this->coursor = coursor;
}


void Board::update() {
	ball->update();
	platform->update();
	switch (checkIfCollideWithEdges(ball)) {
	case 1:
		ball->setRotation((2 * (ball->getRotation() * 0) * 0 - ball->getRotation()) + std::numbers::pi);
		std::cout << ball->getRotation() << std::endl;
		break;
	case 2:
		ball->setRotation((2 * (ball->getRotation() * 0) * std::numbers::pi - ball->getRotation()) + std::numbers::pi);
		std::cout << ball->getRotation() << std::endl;
		break;
	case 3:
		ball->setRotation((2 * (ball->getRotation() * 0) * 3 * std::numbers::pi / 2 - ball->getRotation()) + 2 * std::numbers::pi);
		std::cout << ball->getRotation() << std::endl;
		break;
	case 4:
		ball->setRotation((2 * (ball->getRotation() * 0) * std::numbers::pi / 2 - ball->getRotation()) + 2 * std::numbers::pi);
		std::cout << ball->getRotation() << std::endl;
		break;
	}

	switch (checkIfCollideWithPlatform(ball, platform)) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
	case 4:
		ball->setRotation((2 * (ball->getRotation() * 0) * std::numbers::pi / 2 - ball->getRotation()) + 2 * std::numbers::pi);
		break;
	}

}

void Board::draw() {
	for (auto unit : units) {
		unit->draw();
	}
	coursor->draw();

}

int Board::checkIfCollideWithEdges(DynamicUnit* other)
{
	if (other->x + other->width + 1 > this->width) {
		//std::cout << "right" << std::endl;
		return 1;
	}
	else if (other->x - 1 < 0) {
		//std::cout << "left" << std::endl;
		return 2;
	}
	else if (other->y + other->height + 1 > this->height) {
		//std::cout << "bottom" << std::endl;
		return 3;
	}
	else if (other->y - 1 < 0) {
		//std::cout << "up" << std::endl;
		return 4;
	}
}

int Board::checkIfCollideWithPlatform(DynamicUnit* ball, DynamicUnit* platform)
{
	if (((ball->y + ball->height + 1) > platform->y) && (ball->x + ball->width > platform->x) && (ball->x < this->width - (platform->x + platform->width))) {
		return 4;
	}
}