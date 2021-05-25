#pragma once

#include "app/models/player/player.h"

class TAction {
private:
public:
	TAction() = default;
	virtual void Do(TPlayer&) = 0;
};

