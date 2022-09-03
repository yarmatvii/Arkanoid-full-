#pragma once
#include "Framework.h"
#include <vector>
#include <iostream>

class UI
{

private:

	int score;
	std::vector<Sprite*> scoreboardSprites;

public:

	UI(int width, int height);

	Sprite* scoreboardStart = NULL;

	int getScore();
	void scoreCalculate();

	void tick(int score, int width, int height);

	void update(int score);
	void draw(int width, int height);

};

