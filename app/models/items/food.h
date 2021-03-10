#pragma once

#include "app/models/items/item.h"

class TFood : public TItem {
private:
	int Amount;
public:
	TFood(const std::string& nameFood, const std::string& code, const int amount);
};
