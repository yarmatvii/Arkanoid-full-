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
