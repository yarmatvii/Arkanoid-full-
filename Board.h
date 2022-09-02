#pragma once

#include "Framework.h"
#include "Unit.h"
#include "DynamicUnit.h"
#include "PratformUnit.h"
#include "BallUnit.h"
#include "BlockUnit.h"
#include "Tools.h"

#include <vector>
#include <iostream>

class Board {
public:

	int width;
	int height;
	bool isDefeat = false;
	bool isVictory = false;
	std::vector<BlockUnit*> blocks;
	PratformUnit* platform;
	BallUnit* ball;
	Unit* cursor;
	Sprite* damagedBlock = NULL;

	Board(int width, int height);
	Board(int width, int height, Sprite* wall, Sprite* yellowBlock, Sprite* goldBlock, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball);

	bool intersects(Unit* other);
	bool addBlock(BlockUnit* block);
	void eraseBlock(BlockUnit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(BallUnit* ball);
	void addCursor(Unit* cursor);
	void launchBall();
	bool checkDefeat();
	bool checkVictory();
	bool tick(bool showBoard, Sprite* gameOver, Sprite* victory, Sprite* bg);

	void update();
	void draw();

private:
	Side checkIfCollideWithEdges(DynamicUnit* ball);
	Side checkIfCollideWithPlatform();
	void edgesCollision();
	void platformCollision();
	void blockCollision();
	void checkIfPLatformCollidesWithEdges();
};