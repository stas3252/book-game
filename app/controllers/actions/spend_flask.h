#pragma once

#include "action.h"
#include "app/models/player/player.h"

class TSpendFlask : public TAction {
private:
	int Amount;
public:
	TSpendFlask() = default;
	TSpendFlask(const int amount);
	void Do(TPlayer& player);
};
