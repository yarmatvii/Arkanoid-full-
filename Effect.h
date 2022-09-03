#pragma once
#include <functional>
#include "Framework.h"

class Effect {
public:
	Effect(std::function<void()> onCreate, std::function<void()> onDecsruct, int expires);
	~Effect();
	bool expired(int now);

private:
	std::function<void()> onCreate;
	std::function<void()> onDestruct;
	int expires;
};

