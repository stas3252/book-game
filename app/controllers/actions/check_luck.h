#pragma once

#include "action.h"
#include "app/models/player/player.h"
#include "library/json/json.h"

class TCheckLuck : public TAction {
private:
	NJson::TJsonValue DataTrue;
	NJson::TJsonValue DataFalse;
public:
	TCheckLuck() = default;
	TCheckLuck(const NJson::TJsonValue& dataTrue, const NJson::TJsonValue& dataFalse);
	void Do(TPlayer& player);
};
