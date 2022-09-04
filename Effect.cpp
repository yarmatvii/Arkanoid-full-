#define _WINDOWS
#include "Effect.h"

Effect::Effect(std::function<void()> onCreate, std::function<void()> onDestruct, int duration)
{
	this->onCreate = onCreate;
	this->onDestruct = onDestruct;

	this->expires = getTickCount() + duration;
	onCreate();
};

Effect::~Effect() 
{
	this->onDestruct();
};

bool Effect::expired(int now) 
{
	return now > expires;
}


AccelerateEffect::AccelerateEffect(DynamicUnit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->accelerate(coef); },
		[unit, coef]() { unit->decelerate(coef); },
		duration
	) 
{
}


DecelerateEffect::DecelerateEffect(DynamicUnit* unit, double coef, int duration) :
	Effect(
		[unit, coef]() { unit->decelerate(coef); },
		[unit, coef]() { unit->accelerate(coef); },
		duration
	) 
{
}
