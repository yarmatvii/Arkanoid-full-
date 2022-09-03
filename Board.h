#pragma once

#include "Framework.h"
#include "Unit.h"
#include "DynamicUnit.h"
#include "PratformUnit.h"
#include "BallUnit.h"
#include "BlockUnit.h"
#include "Effect.h"

#include <vector>

class Board {
public:

	int width;
	int height;
	bool isDefeat = false;
	bool isVictory = false;
	std::vector<BlockUnit*> blocks;
	std::vector<Effect*> effects;
	PratformUnit* platform;
	BallUnit* ball;
	Unit* cursor;


	Board(int width, int height);
	Board(int width, int height, Sprite* wall, Sprite* blueBlock, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball);

	bool intersects(Unit* other);
	bool addBlock(BlockUnit* block);
	void eraseBlock(BlockUnit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(BallUnit* ball);
	void addCursor(Unit* cursor);
	void addEffect(Effect* effect);
	void updateEffects();
	void launchBall();
	bool checkDefeat();
	bool checkVictory();
	bool tick(bool showBoard, Sprite* gameOver, Sprite* victory);

	void update();
	void draw();

private:
	std::pair<double, double> reflectionVector(std::pair<double, double> d, std::pair<double, double> n);
	Side checkIfCollideWithEdges(DynamicUnit* ball);
	Side checkIfCollideWithPlatform();
	void edgesCollision();
	void platformCollision();
	void blockCollision();
	void checkIfPLatformCollidesWithEdges();
	void eraseEffect(Effect* effect);
};