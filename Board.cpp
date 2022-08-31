#include "Board.h"
#include <algorithm>
#include "iostream"
#include <numbers>
#include <numeric>

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

	double directionX = this->ball->getDirectionX();
	double directionY = this->ball->getDirectionY();
	std::pair<double, double> r;

	switch (checkIfCollideWithEdges(ball)) {
	case 1:
		r = reflectionVector({ directionX, directionY }, { -1, 0 });
		this->ball->setDirection(r.first, r.second);
		break;
	case 2:
		r = reflectionVector({ directionX, directionY }, { 1, 0 });
		this->ball->setDirection(r.first, r.second);
		break;
	case 3:
		r = reflectionVector({ directionX, directionY }, { 0, 1 });
		this->ball->setDirection(r.first, r.second);
		break;
	case 4:
		r = reflectionVector({ directionX, directionY }, { 0, -1 });
		this->ball->setDirection(r.first, r.second);
		break;
	}

	switch (checkIfCollideWithPlatform(ball, platform)) {
	case 4:
		r = reflectionVector({ directionX, directionY }, { 0, 1 });
		this->ball->setDirection(r.first, r.second);
		break;
	}

	if (this->platform->intersencts(this->ball)) {
		switch (this->platform->collides(this->ball))
		{
		case Side::TOP:
			std::cout << "top" << std::endl;
			r = reflectionVector({ directionX, directionY }, { 0, 1});
			this->ball->setDirection(r.first, r.second);
			break;
		case Side::RIGHT:
			std::cout << "right" << std::endl;
			r = reflectionVector({ directionX, directionY }, { -1, 0});
			this->ball->setDirection(r.first, r.second);
			break;
		case Side::BOTTOM:
			std::cout << "bot" << std::endl;
			r = reflectionVector({ directionX, directionY }, { 0, -1});
			this->ball->setDirection(r.first, r.second);
			break;
		case Side::LEFT:
			std::cout << "left" << std::endl;
			r = reflectionVector({ directionX, directionY }, { 1, 0});
			this->ball->setDirection(r.first, r.second);
			break;
		default:
			std::cout << "inter" << std::endl;
			break;
		}
	}
}

void Board::draw() {
	for (auto unit : units) {
		unit->draw();
	}
	coursor->draw();

}

int Board::checkIfCollideWithEdges(DynamicUnit* unit)
{
	if (unit->x + unit->width >= this->width) {
		//std::cout << "right" << std::endl;
		return 1;
	}
	else if (unit->x < 0) {
		//std::cout << "left" << std::endl;
		return 2;
	}
	else if (unit->y + unit->height >= this->height) {
		//std::cout << "bottom" << std::endl;
		return 3;
	}
	else if (unit->y < 0) {
		//std::cout << "up" << std::endl;
		return 4;
	}
}

int Board::checkIfCollideWithPlatform(DynamicUnit* ball, DynamicUnit* platform)
{
	if (((ball->y + ball->height + 1) > platform->y) &&
		(ball->x + ball->width > platform->x) &&
		(ball->x < this->width - (platform->x + platform->width))) {
		return 4;
	}
}

std::pair<double, double> Board::reflectionVector(std::pair<double, double> d,
	std::pair<double, double> n) {
	double dotProduct = d.first * n.first + d.second * n.second;
	return {
		d.first - 2 * dotProduct * n.first,
		d.second - 2 * dotProduct * n.second
	};
}