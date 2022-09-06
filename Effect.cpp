#define _WINDOWS

#include "Effect.h"

Effect::Effect(std::function<void()> onCreate, std::function<void()> onDestruct, int duration) {
	this->onCreate = onCreate;
	this->onDestruct = onDestruct;

	this->expires = getTickCount() + duration;
	this->onCreate();
};

Effect::~Effect() {
	this->onDestruct();
};

bool Effect::expired(int now) {
	return now > this->expires;
}


IncreaseEffect::IncreaseEffect(Unit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->increase(coef); },
		[unit, coef]() { unit->decrease(coef); },
		duration
	) {
}


DecreaseEffect::DecreaseEffect(Unit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->decrease(coef); },
		[unit, coef]() { unit->increase(coef); },
		duration
	) {
}
