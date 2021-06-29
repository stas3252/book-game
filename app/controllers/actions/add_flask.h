#pragma once

#include "action.h"
#include "app/models/player/player.h"

class TAddFlask : public TAction {
private:
	int Amount;
public:
	TAddFlask() = default;
	TAddFlask(const int amount);
	void Do(TPlayer& player);
};
