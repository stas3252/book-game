#pragma once

#include "action.h"
#include "app/models/player/player.h"

#include <string>

class TAddExtraInfo : public TAction {
private:
	std::string Info;
public:
	TAddExtraInfo() = default;
	TAddExtraInfo(const std::string& info);
	void Do(TPlayer& player);
};
