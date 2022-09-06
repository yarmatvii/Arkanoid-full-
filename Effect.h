#pragma once
#include <functional>
#include "DynamicUnit.h"


class Effect {
	std::function<void()> onCreate;
	std::function<void()> onDestruct;
	int expires;

public:
	Effect(std::function<void()> onCreate, std::function<void()> onDecsruct, int expires);
	~Effect();
	bool expired(int now);

};


class AccelerateEffect : public Effect {
public:
	AccelerateEffect(DynamicUnit* unit, double coef, int duration);
};


class DecelerateEffect : public Effect {
public:
	DecelerateEffect(DynamicUnit* unit, double coef, int duration);
};


class IncreaseEffect : public Effect {
public:
	IncreaseEffect(Unit* unit, double coef, int duration);
};


class DecreaseEffect : public Effect {
public:
	DecreaseEffect(Unit* unit, double coef, int duration);
};

