#pragma once

#include <vector>

#include "Framework.h"
#include "Textures.h"
#include "PratformUnit.h"
#include "BallUnit.h"
#include "BlockUnit.h"
#include "Effect.h"
#include "Area.h"
#include "lib.h"


class Board {
public:

	int width;
	int height;
	int score;
	int playerHp;
	bool isDefeat = false;
	bool isVictory = false;
	std::vector<Unit*> units;
	std::vector<Effect*> effects;
	std::vector<Area*> areas;
	std::vector<Unit*> scoreboard;
	std::vector<Unit*> hp;
  
	Textures& textures;
	Unit& background;
	PratformUnit* platform;
	BallUnit* ball;
	Unit* cursor;
	Unit* savingWall;
	Unit* hud;

	Sprite* damagedBlock = NULL;

	Board(int width, int height);

	void loadLevel();
	void loadPyramid(int rows);
	void loadAreas();
	void loadHp();
	void reset();
	bool intersects(Unit* other);
	bool addUnit(Unit* block);
	void removeUnit(Unit* unit);
	bool addPlatform(PratformUnit* platform);
	bool addBall(BallUnit* ball);
	void addCursor(Unit* cursor);
	void addArea(Area* area);
	void addAccelerationArea(double x, double y, double width, double height);
	void addDecelerationArea(double x, double y, double width, double height);
	void applyEffect(Effect* effect);
	void addRandomEffect();
	void updateAreas();
	void updateEffects();
	void launchBall();
	bool checkVictory();
	void damagePlayer();
	void spawnSavingWall();
	void updateScore();
	bool tick();

	void update();
	void draw();

	void savingWallCollision();
	void edgesCollision(DynamicUnit* unit);
	void platformCollision();
	void blockCollision();
	void removeEffect(Effect* effect);

};