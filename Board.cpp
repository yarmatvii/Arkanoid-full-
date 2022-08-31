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
		r = reflectionVector({ directionX, directionY }, { 0, -1 });
		this->ball->setDirection(r.first, r.second);
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

std::pair<double, double> Board::reflectionVector(std::pair<double, double> d,
	std::pair<double, double> n) {
	double dotProduct = d.first * n.first + d.second * n.second;
	return {
		d.first - 2 * dotProduct * n.first,
		d.second - 2 * dotProduct * n.second
	};
}