#define _WINDOWS

#define WALL_POINTS 1
#define YELLOW_BLOCK_POINTS 1

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
	this->score = 0;
	this->streak = 0;

	int centerX = (0 + this->width) / 2;
	double xСoefficient = double(this->width) / 800;
	double yСoefficient = double(this->height) / 600;
	int wallX = 100 * xСoefficient;
	int wallY = 50 * yСoefficient;

	this->damagedBlock = createSprite(getResourcePath("14-Breakout-Tiles.png").c_str());

	this->addBlock(new BlockUnit(wall, centerX - wallX, 0, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, 0, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, 0, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + 0, 0, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX, 0, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, 0, wallX, wallY, 1, WALL_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY, wallX / 2, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY, wallX / 2, wallY, 1, WALL_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX, wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + 0, wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX, wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, wallY + wallY, wallX, wallY, 1, WALL_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY + wallY + wallY, wallX / 2, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY, 1, WALL_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX / 2, wallY, 1, WALL_POINTS));

	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + 0, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));

	this->addUndestructableBlock(new BlockUnit(goldBlock, centerX - wallX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));
	this->addUndestructableBlock(new BlockUnit(goldBlock, centerX + wallX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));

	this->addPlatform(new PratformUnit(platforms, this->width / 2 - 80, this->height - 100, 160, 40));
	this->addBall(new BallUnit(ball, (this->platform->x + this->platform->getWidth() / 2) - 8, this->height - 160, 16, 16));
	this->addCursor(new Unit(cursor, -50, -50, 16, 16));
}

bool Board::intersects(Unit* other) {
	for (auto block : blocks) {
		if (block->intersects(other)) {
			return true;
		}
	}
	for (auto block : undestructableBlocks) {
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

bool Board::addUndestructableBlock(BlockUnit* unit) {
	if (intersects(unit)) {
		return false;
	}
	this->undestructableBlocks.push_back(unit);
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

void Board::addEffect(Effect* effect) {
	this->effects.push_back(effect);
};

void Board::updateEffects() {
	int now = getTickCount();
	for (auto effect : effects) {
		if (effect->expired(now)) {
			this->eraseEffect(effect);
			delete effect;
		}
	}
};

void Board::launchBall() {
	ball->launch(cursor->x, cursor->y);
}

bool Board::checkDefeat() {
	this->isDefeat = this->ball->y + this->ball->height > this->platform->y + this->platform->height;
	return this->isDefeat;
}

bool Board::checkVictory() {
	this->isVictory = this->blocks.size() == 0 && ball->intersects(platform);
	return this->isVictory;
}

void Board::update() {
	ball->update();
	platform->update();

	updateEffects();

	this->checkIfPLatformCollidesWithEdges();
	this->edgesCollision();
	this->platformCollision();
	this->blockCollision();
	this->undestructableBlockCollision();
}

void Board::draw() {
	for (auto block : blocks) {
		block->draw();
	}
	for (auto block : undestructableBlocks) {
		block->draw();
	}
	ball->draw();
	platform->draw();
	cursor->draw();

}

Side Board::checkIfCollideWithEdges(DynamicUnit* unit)
{
	if (unit->x + unit->getWidth() >= this->width) {
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
		(ball->x + ball->getWidth() + 1 > platform->x + platform->getWidth() / 2) &&
		(ball->x - 1 < (platform->x + platform->getWidth()))) {
		return Side::LEFT;
	}
	else if (((ball->y + ball->height + 1) > platform->y) &&
		(ball->x + ball->getWidth() + 1 > platform->x) &&
		(ball->x - 1 < platform->x + platform->getWidth() / 2)) {
		return Side::RIGHT;
	}
}

void Board::edgesCollision() {
	switch (checkIfCollideWithEdges(ball)) {
	case Side::RIGHT:
		this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
		break;
	case Side::LEFT:
		this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
		break;
	case Side::BOTTOM:
		this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
		break;
	case Side::TOP:
		this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
		break;
	}
}

void Board::platformCollision() {

	switch (checkIfCollideWithPlatform()) {
	case Side::LEFT:
		this->checkVictory();
		this->streak = 0;

		if (this->ball->getDirectionX() < 0) {
			this->ball->setDirection(normalizeVector(-this->ball->getDirectionX() + this->platform->getDirectionX(), -this->ball->getDirectionY()));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		else {
			this->ball->setDirection(normalizeVector(this->ball->getDirectionX() + this->platform->getDirectionX(), -this->ball->getDirectionY()));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		break;
	case Side::RIGHT:
		this->checkVictory();
		this->streak = 0;

		if (this->ball->getDirectionX() < 0) {
			this->ball->setDirection(normalizeVector(this->ball->getDirectionX() + this->platform->getDirectionX(), -this->ball->getDirectionY()));
			this->ball->move(this->ball->x, platform->y - ball->height - 1);
		}
		else {
			this->ball->setDirection(normalizeVector(-this->ball->getDirectionX() + this->platform->getDirectionX(), -this->ball->getDirectionY()));
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
				if (streak >= 3) {
					this->score += 3 * block->getPoints();
				}
				else {
					this->score += block->getPoints();
					streak++;
				}

				std::cout << this->score << std::endl;
				this->eraseBlock(block);
			}

			switch (block->collides(ball))
			{
			case Side::TOP:
				this->ball->move(this->ball->x, block->y - ball->height - 1);
				this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
				break;
			case Side::BOTTOM:
				this->ball->move(this->ball->x, block->y + block->height + 1);
				this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
				break;
			case Side::RIGHT:
				this->ball->move(block->x + block->getWidth() + 1, this->ball->y);
				this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
				break;
			case Side::LEFT:
				this->ball->move(block->x - this->ball->getWidth() - 1, this->ball->y);
				this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
				break;
			}
		}
	}
}

void Board::undestructableBlockCollision() {
	for (auto block : undestructableBlocks) {
		if (block->intersects(ball)) {

			switch (block->collides(ball))
			{
			case Side::TOP:
				this->ball->move(this->ball->x, block->y - ball->height - 1);
				this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
				break;
			case Side::BOTTOM:
				this->ball->move(this->ball->x, block->y + block->height + 1);
				this->ball->setDirection(this->ball->getDirectionX(), -this->ball->getDirectionY());
				break;
			case Side::RIGHT:
				this->ball->move(block->x + block->getWidth() + 1, this->ball->y);
				this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
				break;
			case Side::LEFT:
				this->ball->move(block->x - this->ball->getWidth() - 1, this->ball->y);
				this->ball->setDirection(-this->ball->getDirectionX(), this->ball->getDirectionY());
				break;
			}
		}
	}
}

void Board::checkIfPLatformCollidesWithEdges() {
	if (this->platform->x + this->platform->getWidth() - 1 > this->width) {
		this->platform->x = this->width - this->platform->getWidth() - 1;
	}
	if (this->platform->x < 0) {
		this->platform->x = 0;
	}
}

bool Board::tick(bool showBoard, Sprite* gameOver, Sprite* victory, Sprite* bg) {
	if (showBoard) {
		setSpriteSize(bg, this->width, this->height);
		drawSprite(bg, 0, 0);
		if (this->checkDefeat() || this->isVictory) {
			delete this->ball;
			delete this->cursor;
			delete this->platform;
			this->blocks.clear();
			this->undestructableBlocks.clear();
			return false;
		}
		this->update();
		this->draw();

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

void Board::eraseEffect(Effect* effect) {
	auto position = std::find(begin(this->effects), end(this->effects), effect);
	if (position != end(this->effects)) {
		this->effects.erase(position);
	}
};
