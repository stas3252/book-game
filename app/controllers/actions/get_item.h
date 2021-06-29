#pragma once

#include "action.h"
#include "app/models/player/player.h"
#include "app/models/items/item.h"

#include <memory>

class TGetItem : public TAction {
private:
	std::shared_ptr<TItem> Item;
public:
	TGetItem() = default;
	TGetItem(const std::shared_ptr<TItem> item);
	void Do(TPlayer& player);
};
