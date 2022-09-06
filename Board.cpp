#define _WINDOWS

#include <algorithm>
#include <numbers>
#include <numeric>
#include <functional>
#include <random>

#include "constants.h"
#include "Board.h"

Board::Board(int width, int height) : textures(*new Textures()), background(*new Unit(textures.background(), 0, 0, width, height)) {
	this->width = width;
	this->height = height;
	
	this->score = 0;
	this->playerHp = 3;
	this->scoreboard = {};

	this->loadLevel();
	double platformWidth = this->width * COEF_X;
	double platformHeight = this->height * COEF_Y;

	this->addPlatform(new PratformUnit(textures.platform(), (this->width - platformWidth) / 2, 0.9 * this->height - platformHeight,
		platformWidth, platformHeight, 0, this->width - platformWidth));
	this->platform->minWidth(0);
	this->platform->maxWidth(this->platform->width() * 2);
	this->addBall(new BallUnit(textures.ball(), (platform->x() + platform->width() / 2) - this->height * COEF_Y / 4, platform->y() - platformHeight / 2, this->height * COEF_Y / 2, this->height * COEF_Y / 2));
	this->addCursor(new Unit(textures.cursor(), -50, -50, 16, 16));
	this->savingWall = NULL;
	this->loadHp();
}

void Board::loadLevel() {
	int centerX = width / 2;
	int blockWidth = this->width * COEF_X * 3 / 5;
	int blockHeight = this->height * COEF_Y * 2 / 3;

	this->loadPyramid(11);
	this->loadAreas();
}


void Board::loadPyramid(int rows) {
	if (rows <= 0) {
		return;
	}

	int centerX = width / 2;
	int blockWidth = this->width * COEF_X * 3 / 5;
	int blockHeight = this->height * COEF_Y * 2 / 3;
	std::vector<Sprite*> sprites = { textures.blueBlock() , textures.violetBlock() , textures.lightBlueBlock() };

	if (rows == 1) {
		return;
	}
	Sprite* sprite;
	for (int i = 2; i < rows + 2; i++) {
		if (i % 2 == 0) {
			sprite = sprites[(i) % sprites.size()];
			this->addUnit(new Unit(sprite, centerX - 0.5 * blockWidth, (i - 2) * blockHeight, blockWidth, blockHeight));
			for (int j = 1; j < i / 2; j++) {
				sprite = sprites[(i + j) % sprites.size()];
				this->addUnit(new Unit(sprite, centerX - (j + 0.5) * blockWidth, (i - 2) * blockHeight, blockWidth, blockHeight));
				this->addUnit(new Unit(sprite, centerX + (j - 0.5) * blockWidth, (i - 2) * blockHeight, blockWidth, blockHeight));
			}
		}
		else {
			for (int j = 1; j < (i + 1) / 2; j++) {
				sprite = sprites[(i + j) % sprites.size()];
				this->addUnit(new Unit(sprite, centerX - j * blockWidth, (i - 2) * blockHeight, blockWidth, blockHeight));
				this->addUnit(new Unit(sprite, centerX + (j - 1) * blockWidth, (i - 2) * blockHeight, blockWidth, blockHeight));
			}
		}
	}
}

void Board::loadAreas() {
	int areaWidth = this->width * COEF_X * 5 / 4;
	int areaHeiht = this->height * COEF_Y * 3 / 2;

	this->addAccelerationArea(areaWidth / 2, areaWidth / 2, areaWidth, areaWidth);
	this->addAccelerationArea(this->width - areaWidth, areaWidth / 5, areaWidth / 2, areaWidth / 2);
	this->addDecelerationArea(this->width - 2 * areaWidth, 5 * areaWidth / 4, areaWidth * 1.5, areaWidth * 2 / 3);
	this->addDecelerationArea((this->width - areaWidth) / 2, this->height / 50, areaWidth / 2,3 * areaWidth / 2);
}

void Board::loadHp() {
	for (int i = 0; i < this->playerHp; i++) {

		int heartWidth = 150 * COEF_X;
		int heartHeight = 150 * COEF_X;

		this->hp.push_back(new Unit(textures.heart(), this->width - 1.5 * heartWidth - i * heartWidth, heartHeight / 2, heartWidth, heartWidth));
	}
}

void Board::reset() {

	for (auto area : this->areas) {
		delete area;
	}
	this->areas.clear();
	for (auto unit : this->units) {
		delete unit;
	}
	this->units.clear();
	if (this->savingWall != NULL) {
		delete savingWall;
	}
	delete this->ball;
	delete this->platform;
	for (auto score : scoreboard) {
		delete score;
	}
	scoreboard.clear();
	for (auto hp : this->hp) {
		delete hp;
	}
	this->hp.clear();

	delete this->cursor;
	delete this->hud;

	this->score = 0;
	this->playerHp = 3;
	this->scoreboard = {};
	this->isDefeat = false;
	this->isVictory = false;


	this->loadLevel();
	double platformWidth = this->width * COEF_X;
	double platformHeight = this->height * COEF_Y;

	this->addPlatform(new PratformUnit(textures.platform(), (this->width - platformWidth) / 2, 0.9 * this->height - platformHeight,
		platformWidth, platformHeight, 0, this->width));
	this->platform->minWidth(0);
	this->platform->maxWidth(this->platform->width() * 2);
	this->addBall(new BallUnit(textures.ball(), (platform->x() + platform->width() / 2) - this->height * COEF_Y / 4, platform->y() - platformHeight / 2, this->height * COEF_Y / 2, this->height * COEF_Y / 2));
	this->addCursor(new Unit(textures.cursor(), -50, -50, 16, 16));
	this->savingWall = NULL;
	this->loadHp();
}

bool Board::intersects(Unit* other) {
	for (auto unit : this->units) {
		if (unit->intersects(other)) {
			return true;
		}
	}
	return false;
}

bool Board::addUnit(Unit* unit) {
	this->units.push_back(unit);
	return true;
}

void Board::removeUnit(Unit* unit) {
	auto position = std::find(begin(this->units), end(this->units), unit);
	if (position != end(this->units)) {
		this->score += POINTS;
		this->units.erase(position);
	}
}

bool Board::addPlatform(PratformUnit* platform) {
	this->platform = platform;
	return true;
}

bool Board::addBall(BallUnit* ball) {
	this->ball = ball;
	return true;
}

void Board::addCursor(Unit* cursor) {
	this->cursor = cursor;
}

void Board::addArea(Area* area) {
	this->areas.push_back(area);
}

void Board::addAccelerationArea(double x, double y, double width, double height) {
	this->addArea(new Area(textures.accelerationArea(), x, y, width, height,
		[this]() { this->ball->accelerate(ACCELERATION_COEF); },
		[this]() { this->ball->decelerate(ACCELERATION_COEF); }
	));
}

void Board::addDecelerationArea(double x, double y, double width, double height) {
	this->addArea(new Area(textures.decelerationArea(), x, y, width, height,
		[this]() { this->ball->decelerate(ACCELERATION_COEF); },
		[this]() { this->ball->accelerate(ACCELERATION_COEF); }
	));
}

void Board::applyEffect(Effect* effect) {
	effects.push_back(effect);
};

void Board::addRandomEffect() {
	if (this->score >= ABILITY_COST) {
		this->score -= ABILITY_COST;

		std::srand(std::time(NULL));
		switch (std::rand() % 4) {
		case 0:
			this->applyEffect(new IncreaseEffect(this->platform, INCREASEMENT_COEF, 20000));
			break;
		case 1:
			this->applyEffect(new DecreaseEffect(this->platform, INCREASEMENT_COEF, 20000));
			break;
		case 2:
			this->spawnSavingWall();
			break;
		case 3:
			this->damagePlayer();
			break;
		}
	}
}

void Board::updateAreas() {
	for (auto area : this->areas) {
		area->update(this->ball);
	}
}

void Board::updateEffects() {
	int now = getTickCount();
	for (auto effect : effects) {
		if (effect->expired(now)) {
			removeEffect(effect);
			delete effect;
		}
	}
};

void Board::launchBall() {
	this->ball->launch(cursor->x(), cursor->y());
}

bool Board::checkVictory() {
	this->isVictory = units.size() == 0;
	return isVictory;
}

void Board::damagePlayer() {
	this->playerHp -= 1;
	delete this->hp.back();
	this->hp.pop_back();
	if (this->playerHp == 0) {
		this->isDefeat = true;
	}
}

void Board::spawnSavingWall() {
	this->savingWall = new Unit(textures.savingwall(), 0, this->height - 40, this->width, 20);
}

void Board::updateScore() {
	std::string score_str = std::to_string(this->score);
	for (int i = 0; i < score_str.size(); i++) {
		Sprite* sprite = NULL;
		switch (score_str[i]) {
		case '0':
			sprite = this->textures.zero();
			break;
		case '1':
			sprite = this->textures.one();
			break;
		case '2':
			sprite = this->textures.two();
			break;
		case '3':
			sprite = this->textures.three();
			break;
		case '4':
			sprite = this->textures.four();
			break;
		case '5':
			sprite = this->textures.five();
			break;
		case '6':
			sprite = this->textures.six();
			break;
		case '7':
			sprite = this->textures.seven();
			break;
		case '8':
			sprite = this->textures.eight();
			break;
		case '9':
			sprite = this->textures.nine();
			break;
		}
		double digitWidth = this->platform->height() / 2;
		double digitHeight = digitWidth;
		int len = this->scoreboard.size();

		int scoreboardWidth = scoreboard.size() * digitWidth;
		double x = this->platform->x() + (this->platform->width() - scoreboardWidth) / 2 + i * digitWidth;
		double y = this->platform->y() + digitHeight;
		if (len <= i) {
			this->scoreboard.push_back(new Unit(sprite, x, y, digitWidth, digitHeight));
		}
		if (scoreboard.size() > score_str.size()) {
			delete this->scoreboard.back();
			this->scoreboard.pop_back();
		}

		this->scoreboard[i]->sprite(sprite);
		this->scoreboard[i]->move(x, y);
	}
}

bool Board::tick() {
	this->background.draw();
	this->update();
	this->draw();
	if (isDefeat || isVictory) {
		this->ball->resetVelocity();
		this->platform->resetVelocity();
		int hudWidth = this->width / 3;
		int hudHeight = this->height / 3;
		this->hud = new Unit(textures.restart(), (this->width - hudWidth) / 2, (this->height - 0.5 * hudHeight) / 2, hudWidth, hudHeight);
		this->hud->draw();
		return true;
	}
	return false;
}

void Board::update() {
	this->ball->update();
	this->platform->update();

	this->updateAreas();
	this->updateEffects();

	this->savingWallCollision();
	this->platformCollision();
	this->edgesCollision(this->ball);
	this->blockCollision();
	this->updateScore();
}

void Board::draw() {
	for (auto area : this->areas) {
		area->draw();
	}
	for (auto unit : this->units) {
		unit->draw();
	}
	if (this->savingWall != NULL) {
		this->savingWall->draw();
	}
	this->ball->draw();
	this->platform->draw();
	for (auto score : scoreboard) {
		score->draw();
	}
	for (auto heart : this->hp) {
		heart->draw();
	}
	this->cursor->draw();

}

void Board::savingWallCollision() {
	if (this->savingWall != NULL) {
		if (this->savingWall->intersects(ball)) {
			ball->reflect(this->savingWall);
			delete this->savingWall;
			this->savingWall = NULL;
		}
	}
}

void Board::edgesCollision(DynamicUnit* unit) {
	if (unit->x() + unit->width() >= this->width) {
		ball->direction(-ball->directionX(), ball->directionY());
	}
	else if (unit->x() < 0) {
		ball->direction(-ball->directionX(), ball->directionY());
	}
	else if (unit->y() + unit->height() >= this->height) {
		isDefeat = true;
		ball->direction(ball->directionX(), -ball->directionY());
	}
	else if (unit->y() < 0) {
		ball->direction(ball->directionX(), -ball->directionY());
	}
}

void Board::platformCollision() {
	if (((ball->y() + ball->height() + 1) > platform->y() &&
		(ball->x() + ball->width() + 1 > platform->x() + platform->width() / 2) &&
		(ball->x() - 1 < (platform->x() + platform->width())))) {
		this->checkVictory();
		if (ball->directionX() < 0) {
			ball->direction(normalize(-ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		else {
			ball->direction(normalize(ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
	}
	else if (((ball->y() + ball->height() + 1) > platform->y() &&
		(ball->x() + ball->width() + 1 > platform->x() &&
			(ball->x() - 1 < platform->x() + platform->width() / 2)))) {
		this->checkVictory();
		if (ball->directionX() < 0) {
			ball->direction(normalize(ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
		else {
			ball->direction(normalize(-ball->directionX() + platform->directionX(), -ball->directionY()));
			ball->move(ball->x(), platform->y() - ball->height() - 1);
		}
	}
}

void Board::blockCollision() {
	for (auto unit : units) {
		if (unit->intersects(ball)) {
			removeUnit(unit);
			ball->reflect(unit);
		}
	}
}

void Board::removeEffect(Effect* effect) {
	auto position = std::find(begin(effects), end(effects), effect);
	if (position != end(effects))
		effects.erase(position);
};
