#pragma once

#include "action.h"
#include "app/models/player/player.h"

class TAddStrengthAction : public TAction {
private:
	int Amount;
public:
	TAddStrengthAction() = default;
	TAddStrengthAction(const int amount);
	void Do(TPlayer& player);
};
