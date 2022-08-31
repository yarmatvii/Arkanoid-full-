#include "Board.h"
#include <algorithm>
#include "iostream"
#include <numbers>
#include <numeric>

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
}

bool Board::intersects(Unit* other) {
	for (auto unit : units) {
		if (unit->intersects(other)) {
			return true;
		}
	}
	return false;
}

bool Board::addUnit(Unit* unit) {
	if (intersects(unit)) {
		return false;
	}
	this->units.push_back(unit);
	return true;
}

bool Board::addPlatform(PratformUnit* platform) {
	//if (!addUnit(platform)) {
	//	return false;
	//}
	this->platform = platform;
	return true;
}

bool Board::addBall(DynamicUnit* ball) {
	//if (!addUnit(ball)) {
	//	return false;
	//}
	this->ball = ball;
	return true;
}

void Board::addCoursor(Unit* coursor) {
	this->coursor = coursor;
}


void Board::update() {
	//if (ball->y + ball->height < platform->y + platform->height)
	ball->update();
	platform->update();

	double directionX = this->ball->getDirectionX();
	double directionY = this->ball->getDirectionY();

	switch (checkIfCollideWithEdges(ball)) {
	case Side::RIGHT:
		this->ball->setDirection(-directionX, directionY);
		break;
	case Side::LEFT:
		this->ball->setDirection(-directionX, directionY);
		break;
	case Side::BOTTOM:
		this->ball->setDirection(directionX, -directionY);
		break;
	case Side::TOP:
		this->ball->setDirection(directionX, -directionY);
		break;
	}

	switch (checkIfCollideWithPlatform(ball, platform)) {
	case Side::LEFT:
		if (directionX < 0)
			this->ball->setDirection(-directionX, -directionY);
		else this->ball->setDirection(directionX, -directionY);
		break;
	case Side::RIGHT:
		if (directionX < 0)
			this->ball->setDirection(directionX, -directionY);
		else this->ball->setDirection(-directionX, -directionY);
		break;
	}
}

void Board::draw() {
	for (auto unit : units) {
		if (unit->intersects(ball))
		{
			std::cout << "intersects";
			double directionX = this->ball->getDirectionX();
			double directionY = this->ball->getDirectionY();
			switch (unit->collides(ball))
			{
			case Side::TOP:
				this->ball->setDirection(directionX, -directionY);
				break;
			case Side::BOTTOM:
				this->ball->setDirection(directionX, -directionY);
				break;
			case Side::RIGHT:
				this->ball->setDirection(-directionX, directionY);
				break;
			case Side::LEFT:
				this->ball->setDirection(-directionX, directionY);
				break;
			}
		}
		unit->draw();
	}
	ball->draw();
	platform->draw();
	coursor->draw();

}

Side Board::checkIfCollideWithEdges(DynamicUnit* unit)
{
	if (unit->x + unit->width >= this->width) {
		//std::cout << "right" << std::endl;
		return Side::RIGHT;
	}
	else if (unit->x < 0) {
		//std::cout << "left" << std::endl;
		return Side::LEFT;
	}
	else if (unit->y + unit->height >= this->height) {
		//std::cout << "bottom" << std::endl;
		return Side::BOTTOM;
	}
	else if (unit->y < 0) {
		//std::cout << "top" << std::endl;
		return Side::TOP;
	}
}

Side Board::checkIfCollideWithPlatform(DynamicUnit* ball, DynamicUnit* platform)
{
	if (((ball->y + ball->height + 1) > platform->y) &&
		(ball->x + ball->width + 1 > platform->x + platform->width / 2) &&
		(ball->x - 1 < (platform->x + platform->width))) {
		return Side::LEFT;
	}
	else if (((ball->y + ball->height + 1) > platform->y) &&
		(ball->x + ball->width + 1 > platform->x) &&
		(ball->x - 1 < platform->x + platform->width / 2)) {
		return Side::RIGHT;
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
