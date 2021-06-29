#include "get_item.h"
#include <iostream>

TGetItem::TGetItem(const std::shared_ptr<TItem> item) : Item(item) {}

void TGetItem::Do(TPlayer& player) {
	player.AddItemToPlaceAddItems(Item);
}
