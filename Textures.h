#pragma once

#define _WINDOWS

#include <memory>
#include <vector>
#include <functional>

#include "Framework.h"

class Textures {
	std::unordered_map<std::string, std::function<Sprite*()>> m;

	Sprite*_blueBlock;
	Sprite*_violetBlock;
	Sprite* _lightBlueBlock;

	Sprite* _ball;
	Sprite* _cursor;
	std::vector<Sprite*> _platform;
	
	Sprite* _restart;
	Sprite* _background;

	Sprite* _savingwall = NULL;
	Sprite* _accelerationArea = NULL;
	Sprite* _decelerationArea = NULL;

	Sprite* _zero;
	Sprite* _one;
	Sprite* _two;
	Sprite* _three;
	Sprite* _four;
	Sprite* _five;
	Sprite* _six;
	Sprite* _seven;
	Sprite* _eight;
	Sprite* _nine;
	Sprite* _heart;

public:
	Textures();
	Sprite* blueBlock();
	Sprite*	violetBlock();
	Sprite* lightBlueBlock();
	Sprite* ball();
	Sprite* cursor();
	std::vector<Sprite*> platform();
	Sprite* restart();
	Sprite* background();
	Sprite* savingwall();
	Sprite* accelerationArea();
	Sprite* decelerationArea();
	Sprite* zero();
	Sprite* one();
	Sprite* two();
	Sprite* three();
	Sprite* four();
	Sprite* five();
	Sprite* six();
	Sprite* seven();
	Sprite* eight();
	Sprite* nine();
	Sprite* heart();
};

