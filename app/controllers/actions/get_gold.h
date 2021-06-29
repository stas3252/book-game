#pragma once

#include "action.h"
#include "app/models/player/player.h"

class TGetGold : public TAction {
private:
	int Amount;
public:
	TGetGold() = default;
	TGetGold(const int amount);
	void Do(TPlayer& player);
};
