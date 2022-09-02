﻿#define _WINDOWS
#include "Board.h"
#include <algorithm>
#include "iostream"
#include <numbers>
#include <numeric>

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
}

Board::Board(int width, int height, Sprite* wall, Sprite* yellowBlock, Sprite* goldBlock, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball) {
	this->width = width;
	this->height = height;

	int centerX = (0 + this->width) / 2;
	double xСoefficient = double(this->width) / 800;
	double yСoefficient = double(this->height) / 600;
	int wallX = 100 * xСoefficient;
	int wallY = 50 * yСoefficient;

	this->damagedBlock = createSprite(getResourcePath("14-Breakout-Tiles.png").c_str());

	this->addBlock(new BlockUnit(wall, centerX - wallX, 0, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, 0, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, 0, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + 0, 0, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX, 0, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, 0, wallX, wallY));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY, wallX / 2, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY, wallX / 2, wallY));

	this->addBlock(new BlockUnit(wall, centerX - wallX, wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + 0, wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX, wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, wallY + wallY, wallX, wallY));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY + wallY + wallY, wallX / 2, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX / 2, wallY));

	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));
	this->addBlock(new BlockUnit(yellowBlock, centerX + 0, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2));

	this->addBlock(new BlockUnit(goldBlock, centerX - wallX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));
	this->addBlock(new BlockUnit(goldBlock, centerX + wallX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));

	this->addPlatform(new PratformUnit(platforms, this->width / 2 - 80, this->height - 100, 160, 40));
	this->addBall(new BallUnit(ball, (this->platform->x + this->platform->width / 2) - 8, this->height - 160, 16, 16));
	this->addCursor(new Unit(cursor, -50, -50, 16, 16));
}

bool Board::intersects(Unit* other) {
	for (auto block : blocks) {
		if (block->intersects(other)) {
			return true;
		}
	}
	return false;
}

bool Board::addBlock(BlockUnit* unit) {
	if (intersects(unit)) {
		return false;
	}
	this->blocks.push_back(unit);
	return true;
}

void Board::eraseBlock(BlockUnit* unit) {
	auto position = std::find(begin(this->blocks), end(this->blocks), unit);
	if (position != end(this->blocks)) {
		this->blocks.erase(position);
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

bool Board::checkDefeat() {
	return this->ball->y + this->ball->height > this->platform->y + this->platform->height;
}

bool Board::checkVictory() {
	return (this->blocks.size() == 0 && ball->intersects(platform));
}

void Board::update() {
	ball->update();
	checkIfPLatformCollidesWithEdges();
	platform->update();

	this->edgesCollision();
	this->platformCollision();
	this->blockCollision();

}

void Board::draw() {
	for (auto block : blocks) {
		block->draw();
	}
	ball->draw();
	platform->draw();
	cursor->draw();

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

Side Board::checkIfCollideWithPlatform() {
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

	switch (checkIfCollideWithPlatform()) {  
	case Side::LEFT:
		if (this->ball->directionX < 0) {
			this->ball->setDirection(normalizeVector(-this->ball->directionX + this->platform->directionX, -this->ball->directionY));
			this->ball->move(this->ball->x, platform->y - ball->height - 1 );
		}
		else {
			this->ball->setDirection(normalizeVector(this->ball->directionX + this->platform->directionX, -this->ball->directionY));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		break;
	case Side::RIGHT:
		if (this->ball->directionX < 0) {
			this->ball->setDirection(normalizeVector(this->ball->directionX + this->platform->directionX, -this->ball->directionY));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		else {
			this->ball->setDirection(normalizeVector(-this->ball->directionX + this->platform->directionX, -this->ball->directionY));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		break;
	}
}

void Board::blockCollision() {
	for (auto block : blocks) {
		if (block->intersects(ball)) {

			if (block->getHp() > 1) block->sprite = damagedBlock;
			block->doDamage(1);

			if (!block->isAlive()) {
				this->eraseBlock(block);
			}

			switch (block->collides(ball))
			{
			case Side::TOP:
				this->ball->move(this->ball->x, block->y - block->height - 1);
				this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
				break;
			case Side::BOTTOM:
				this->ball->move(this->ball->x, block->y + block->height + 1);
				this->ball->setDirection(this->ball->directionX, -this->ball->directionY);
				break;
			case Side::RIGHT:
				this->ball->move(block->x + block->width + 1, this->ball->y);
				this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
				break;
			case Side::LEFT:
				this->ball->move(block->x - this->ball->width - 1, this->ball->y);
				this->ball->setDirection(-this->ball->directionX, this->ball->directionY);
				break;
			}
		}
	}
}

void Board::checkIfPLatformCollidesWithEdges() {
	if (this->platform->x + this->platform->width + 1 > this->width) {
		this->platform->velocity = 0;
		this->platform->x -= 1;
	}
	if (this->platform->x - 1 < 0) {
		this->platform->velocity = 0;
		this->platform->x += 1;
	}
}

bool Board::tick(bool showBoard, Sprite* gameOver, Sprite* victory, Sprite* bg) {
	if (showBoard) {
		setSpriteSize(bg, this->width, this->height);
		drawSprite(bg, 0, 0);
		this->update();
		this->draw();

		if (this->checkDefeat() || this->checkVictory()) {
			if (this->checkDefeat()) isDefeat = true;
			if (this->checkVictory()) isVictory = true;
			delete this->ball;
			delete this->cursor;
			delete this->platform;
			this->blocks.clear();
			return false;
		}
	}
	else {
		if (isDefeat) {
			setSpriteSize(gameOver, this->width, this->height);
			drawSprite(gameOver, 0, 0);
		}
		if (isVictory) {
			setSpriteSize(victory, this->width, this->height);
			drawSprite(victory, 0, 0);
		}
		return false;
	}
	return true;
}
