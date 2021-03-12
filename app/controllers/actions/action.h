#pragma once
#include "app/models/player/player.h"
class TAction {
public:
	TAction() = default;
	virtual void Do(TPlayer& player) = 0;
};
