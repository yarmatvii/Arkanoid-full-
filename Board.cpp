#define _WINDOWS

#include <algorithm>
#include <iostream>
#include <numbers>
#include <numeric>
#include <functional>
#include <random>

#include "constants.h"
#include "Board.h"

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
}

Board::Board(int width, int height, Sprite* wall, Sprite* yellowBlock, Sprite* goldBlock, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball) {
	this->width = width;
	this->height = height;
	this->score = 0;
	this->streak = 0;

	int centerX = (0 + width) / 2;
	double xСoefficient = double(width) / 800;
	double yСoefficient = double(height) / 600;
	int wallX = 100 * xСoefficient;
	int wallY = 50 * yСoefficient;

	damagedBlock = createSprite(getResourcePath("14-Breakout-Tiles.png").c_str());

	this->addBlock(new BlockUnit(wall, centerX - wallX, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + 0, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, 0, wallX, wallY, 1, BLUE_BLOCK_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY, wallX / 2, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY, wallX / 2, wallY, 1, BLUE_BLOCK_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + 0, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX, wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));

	this->addBlock(new BlockUnit(wall, centerX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX / 2 - 1, wallY + wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX - wallX - wallX - wallX - 1, wallY + wallY + wallY, wallX / 2, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX, wallY, 1, BLUE_BLOCK_POINTS));
	this->addBlock(new BlockUnit(wall, centerX + wallX + wallX + wallX / 2 + 1, wallY + wallY + wallY, wallX / 2, wallY, 1, BLUE_BLOCK_POINTS));

	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + 0, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));
	this->addBlock(new BlockUnit(yellowBlock, centerX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 2, wallX, wallY / 2, 2, YELLOW_BLOCK_POINTS));

	this->addUndestructableBlock(new BlockUnit(goldBlock, centerX - wallX - wallX - wallX - wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));
	this->addUndestructableBlock(new BlockUnit(goldBlock, centerX + wallX + wallX + wallX, wallY + wallY + wallY + wallY + wallY / 4, wallX, wallY + wallY, 999));

	this->addPlatform(new PratformUnit(platforms, width / 2 - 80, height - 100, 160, 40));
	this->addBall(new BallUnit(ball, (platform->x() + platform->width() / 2) - 8, height - 160, 16, 16));
	this->addCursor(new Unit(cursor, -50, -50, 16, 16));
}

bool Board::intersects(Unit* other) {
	for (auto block : blocks) {
		if (block->intersects(other)) {
			return true;
		}
	}
	for (auto block : undestructableBlocks) {
		if (block->intersects(other))
		{
			return true;
		}
	}
	return false;
}

bool Board::addBlock(BlockUnit* unit) {
	if (intersects(unit))
	{
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

void Board::addCursor(Unit* cursor)
{
	this->cursor = cursor;
}

bool Board::addBall(BallUnit* ball)
{
	if (intersects(ball)) {
		return false;
	}
	this->ball = ball;
	return true;
}

void Board::addEffect(Effect* effect) {
	effects.push_back(effect);
};

void Board::addRandomEffect() {
	if (this->score >= ABILITY_COST) {
		this->score -= ABILITY_COST;

		std::vector<std::function<Effect* (DynamicUnit* unit, double coef, int duration)>> effectsList = {
			[this](DynamicUnit* unit, double coef, int duration) { return new AccelerateEffect(unit, coef, duration); },
			[this](DynamicUnit* unit, double coef, int duration) { return new DecelerateEffect(unit, coef, duration); },
		};

		std::srand(std::time(NULL));
		int randomIndex = std::rand() % effectsList.size();
		std::function<Effect* (DynamicUnit* unit, double coef, int duration)> randomEffectConstructor = effectsList[randomIndex];
		this->addEffect(randomEffectConstructor(platform, ACCELERATION_COEF, EFFECT_DURATION));
	}
}

void Board::updateEffects() {
	int now = getTickCount();
	for (auto effect : effects) {
		if (effect->expired(now)) {
			eraseEffect(effect);
			delete effect;
		}
	}
};

void Board::launchBall() {
	this->ball->launch(cursor->x(), cursor->y());
}

bool Board::checkDefeat() {
	this->isDefeat = ball->y() + ball->height() > platform->y() + platform->height();
	return this->isDefeat;
}

bool Board::checkVictory() {
	this->isVictory = blocks.size() == 0;
	return isVictory;
}

void Board::update() {
	this->ball->update();
	this->platform->update();

	updateEffects();

	platformCollision();
	checkIfPLatformCollidesWithEdges();
	edgesCollision();
	blockCollision();
	undestructableBlockCollision();
}

void Board::draw() {
	for (auto block : blocks) {
		block->draw();
	}
	for (auto block : undestructableBlocks) {
		block->draw();
	}
	this->ball->draw();
	this->platform->draw();
	this->cursor->draw();

}

Side Board::checkIfCollideWithEdges(DynamicUnit* unit)
{
	if (unit->x() + unit->width() >= width) {
		return Side::RIGHT;
	}
	else if (unit->x() < 0) {
		return Side::LEFT;
	}
	else if (unit->y() + unit->height() >= height) {
		return Side::BOTTOM;
	}
	else if (unit->y() < 0) {
		return Side::TOP;
	}
}

Side Board::checkIfCollideWithPlatform()
{
	if (((ball->y() + ball->height() + 1) > platform->y() &&
		(ball->x() + ball->width() + 1 > platform->x() + platform->width() / 2) &&
		(ball->x() - 1 < (platform->x() + platform->width())))) {
		return Side::LEFT;
	}
	else if (((ball->y() + ball->height() + 1) > platform->y() &&
		(ball->x() + ball->width() + 1 > platform->x() &&
		(ball->x() - 1 < platform->x() + platform->width() / 2)))) {
		return Side::RIGHT;
	}
}

void Board::edgesCollision() {
	switch (checkIfCollideWithEdges(ball)) {
	case Side::RIGHT:
		ball->direction(-ball->directionX(), ball->directionY());
		break;
	case Side::LEFT:
		ball->direction(-ball->directionX(), ball->directionY());
		break;
	case Side::BOTTOM:
		ball->direction(ball->directionX(), -ball->directionY());
		break;
	case Side::TOP:
		ball->direction(ball->directionX(), -ball->directionY());
		break;
	}
}

void Board::platformCollision()
{

	switch (checkIfCollideWithPlatform()) {
	case Side::LEFT:
		this->checkVictory();
		streak = 0;

		if (ball->directionX() < 0)
		{
			ball->direction(normalize(-ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		else
		{
			ball->direction(normalize(ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		break;
	case Side::RIGHT:
		checkVictory();
		streak = 0;

		if (ball->directionX() < 0) {
			ball->direction(normalize(ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		else {
			ball->direction(normalize(-ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		break;
	}
}

void Board::blockCollision()
{
	for (auto block : blocks) {
		if (block->intersects(ball)) {

			if (block->hp() > 1) block->sprite(damagedBlock);
			block->doDamage(1);

			if (!block->isAlive()) {
				if (streak >= 3) {
					score += 3 * block->points();
				}
				else {
					score += block->points();
					streak++;
				}

				eraseBlock(block);
			}

			switch (block->collides(ball)) {
			case Side::TOP:
				ball->move(ball->x(), block->y() - ball->height() - 1);
				ball->direction(ball->directionX(), -ball->directionY());
				break;
			case Side::BOTTOM:
				ball->move(ball->x(), block->y() + block->height() + 1);
				ball->direction(ball->directionX(), -ball->directionY());
				break;
			case Side::RIGHT:
				ball->move(block->x() + block->width() + 1, ball->y());
				ball->direction(-ball->directionX(), ball->directionY());
				break;
			case Side::LEFT:
				ball->move(block->x() - ball->width() - 1, ball->y());
				ball->direction(-ball->directionX(), ball->directionY());
				break;
			}
		}
	}
}

void Board::undestructableBlockCollision()
{
	for (auto block : undestructableBlocks) {
		if (block->intersects(ball)) {

			switch (block->collides(ball)) {
			case Side::TOP:
				ball->move(ball->x(), block->y() - ball->height() - 1);
				ball->direction(ball->directionX(), -ball->directionY());
				break;
			case Side::BOTTOM:
				ball->move(ball->x(), block->y() + block->height() + 1);
				ball->direction(ball->directionX(), -ball->directionY());
				break;
			case Side::RIGHT:
				ball->move(block->x() + block->width() + 1, ball->y());
				ball->direction(-ball->directionX(), ball->directionY());
				break;
			case Side::LEFT:
				ball->move(block->x() - ball->width() - 1, ball->y());
				ball->direction(-ball->directionX(), ball->directionY());
				break;
			}
		}
	}
}

void Board::checkIfPLatformCollidesWithEdges()
{
	if (platform->x() + platform->width() - 1 > width) {
		platform->x(width - platform->width() - 1);
	}
	if (platform->x() < 0) {
		platform->x(0);
	}
}

bool Board::tick(bool showBoard, Sprite* gameOver, Sprite* victory, Sprite* bg)
{
	if (showBoard) {
		setSpriteSize(bg, width, height);
		drawSprite(bg, 0, 0);
		if (checkDefeat() || isVictory) {
			delete this->ball;
			delete this->cursor;
			delete this->platform;
			blocks.clear();
			undestructableBlocks.clear();
			return false;
		}
		update();
		draw();

	}
	else {
		if (isDefeat) {
			setSpriteSize(gameOver, width, height);
			drawSprite(gameOver, 0, 0);
		}
		if (isVictory) {
			setSpriteSize(victory, width, height);
			drawSprite(victory, 0, 0);
		}
		return false;
	}
	return true;
}

void Board::eraseEffect(Effect* effect)
{
	auto position = std::find(begin(effects), end(effects), effect);
	if (position != end(effects))
		effects.erase(position);
};
