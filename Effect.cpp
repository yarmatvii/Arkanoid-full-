#define _WINDOWS
#include "Effect.h"

Effect::Effect(std::function<void()> onCreate, std::function<void()> onDestruct, int duration) {
	this->onCreate = onCreate;
	this->onDestruct = onDestruct;

	this->onCreate();
	this->expires = getTickCount() + duration;
};

Effect::~Effect() {
	this->onDestruct();
};

bool Effect::expired(int now) {
	return now > expires;
}


AccelerateEffect::AccelerateEffect(DynamicUnit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->accelerate(coef); },
		[unit, coef]() { unit->decelerate(coef); },
		duration
	) {
}


DecelerateEffect::DecelerateEffect(DynamicUnit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->decelerate(coef); },
		[unit, coef]() { unit->accelerate(coef); },
		duration
	) {
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
