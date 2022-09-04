#pragma once
#include "Framework.h"
#include <vector>
#include <string>
#include <iostream>

class UI
{

private:

	std::vector<Sprite*> numbers;

public:

	UI(int width, int height);

	Sprite* scoreboardStart = NULL;
	Sprite* speedAbility = NULL;
	Sprite* sizeAbility = NULL;

	Sprite* one = NULL;
	Sprite* two = NULL;
	Sprite* three = NULL;
	Sprite* four = NULL;
	Sprite* five = NULL;
	Sprite* six = NULL;
	Sprite* seven = NULL;
	Sprite* eight = NULL;
	Sprite* nine = NULL;
	Sprite* zero = NULL;

	void tick(int score, int width, int height, bool showboard);

	void update(int score);
	void draw(int width, int height, int score, bool showboard);
	void drawNumber(int width, int height, int score);
	void addNumber(Sprite* num);

};
