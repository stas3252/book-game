#pragma once

#include "action.h"
#include "app/models/player/player.h"

class TSpendStrength : public TAction {
private:
	int Amount;
public:
	TSpendStrength() = default;
	TSpendStrength(const int amount);
	void Do(TPlayer& player);
};
