#pragma once

#include "Framework.h"
#include "PratformUnit.h"
#include "BallUnit.h"
#include "BlockUnit.h"
#include "Effect.h"
#include "Tools.h"

#include <vector>
#include <iostream>

class Board {
public:

	int width;
	int height;
	int score;
	int streak;
	bool isDefeat = false;
	bool isVictory = false;
	std::vector<BlockUnit*> blocks;
	std::vector<Effect*> effects;
	std::vector<BlockUnit*> undestructableBlocks;
  
	PratformUnit* platform;
	BallUnit* ball;
	Unit* cursor;

	Sprite* damagedBlock = NULL;

	Board(int width, int height);
	Board(int width, int height, Sprite* wall, Sprite* yellowBlock, Sprite* goldBlock, std::vector<Sprite*> platforms, Sprite* cursor, Sprite* ball);

	bool intersects(Unit* other);
	bool addBlock(BlockUnit* block);
	bool addUndestructableBlock(BlockUnit* block);
	void eraseBlock(BlockUnit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(BallUnit* ball);
	void addCursor(Unit* cursor);
	void addEffect(Effect* effect);
	void addRandomEffect();
	void updateEffects();
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
	void undestructableBlockCollision();
	void checkIfPLatformCollidesWithEdges();
	void eraseEffect(Effect* effect);

};