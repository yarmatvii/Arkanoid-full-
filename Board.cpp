#include "Board.h"
#include <algorithm>
#include "iostream"
#include <numbers>
#include <numeric>

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
}

Board::Board(int width, int height, Sprite* wall, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball) {
	this->width = width;
	this->height = height;

	this->addUnit(new Unit(wall, 200, 200, 150, 50));
	this->addUnit(new Unit(wall, 150, 0, 150, 50));
	this->addUnit(new Unit(wall, 300, 0, 150, 50));
	this->addUnit(new Unit(wall, 450, 0, 150, 50));
	this->addUnit(new Unit(wall, 600, 0, 150, 50));
	this->addUnit(new Unit(wall, 750, 0, 50, 50));

	this->addPlatform(new PratformUnit(platforms, this->width / 2 - 80, this->height - 100, 160, 40));
	this->addBall(new BallUnit(ball, (this->platform->x + this->platform->width / 2) - 8, this->height - 160, 16, 16));
	this->addCursor(new Unit(cursor, -50, -50, 16, 16));
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

void Board::eraseUnit(Unit* unit) {
	auto position = std::find(begin(this->units), end(this->units), unit);
	if (position != end(this->units)) {
		this->units.erase(position);
	}
}

bool Board::addPlatform(PratformUnit* platform) {
	if (intersects(platform)) {
		return false;
	}
	this->platform = platform;
	return true;
}

void Board::addCursor(Unit* cursor) {
	this->cursor = cursor;
}

bool Board::addBall(BallUnit* ball) {
	if (intersects(ball)) {
		return false;
	}
	this->ball = ball;
	return true;
}

void Board::launchBall() {
	ball->launch(cursor->x, cursor->y);
}

void Board::update() {
	ball->update();
	platform->update();

	this->edgesCollision();
	this->platformCollision();
	this->blockCollision();

}

void Board::draw() {
	for (auto unit : units) {
		unit->draw();
	}
	ball->draw();
	platform->draw();
	cursor->draw();

}

std::pair<double, double> Board::reflectionVector(std::pair<double, double> d, std::pair<double, double> n) {
	double dotProduct = d.first * n.first + d.second * n.second;
	return {
		d.first - 2 * dotProduct * n.first,
		d.second - 2 * dotProduct * n.second
	};
}

Side Board::checkIfCollideWithEdges(DynamicUnit* unit)
{
	if (unit->x + unit->width >= this->width) {
		return Side::RIGHT;
	}
	else if (unit->x < 0) {
		return Side::LEFT;
	}
	else if (unit->y + unit->height >= this->height) {
		return Side::BOTTOM;
	}
	else if (unit->y < 0) {
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

void Board::edgesCollision() {
	switch (checkIfCollideWithEdges(ball)) {
	case Side::RIGHT:
		this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
		break;
	case Side::LEFT:
		this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
		break;
	case Side::BOTTOM:
		this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
		break;
	case Side::TOP:
		this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
		break;
	}
}

void Board::platformCollision() {
	switch (checkIfCollideWithPlatform(ball, platform)) {
	case Side::LEFT:
		if (this->ball->directionX < 0) {
			this->ball->setDirection(-this->ball->directionX, -this->ball->directionY);
		}
		else {
			this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
		}
		break;
	case Side::RIGHT:
		if (this->ball->directionX < 0) {
			this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
		}
		else {
			this->ball->setDirection(-this->ball->directionX, -this->ball->directionY);
		}
		break;
	}
}

void Board::blockCollision() {
	for (auto unit : units) {
		if (unit->intersects(ball)) {
			this->eraseUnit(unit);

			switch (unit->collides(ball))
			{
			case Side::TOP:
				this->ball->move(this->ball->x, unit->y - unit->height - 1);
				this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
				break;
			case Side::BOTTOM:
				this->ball->move(this->ball->x, unit->y + unit->height + 1);
				this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
				break;
			case Side::RIGHT:
				this->ball->move(unit->x + unit->width + 1, this->ball->y);
				this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
				break;
			case Side::LEFT:
				this->ball->move(unit->x - this->ball->width - 1, this->ball->y);
				this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
				break;
			}
		}
	}
}
