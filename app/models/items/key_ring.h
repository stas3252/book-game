#pragma once

#include "app/models/items/item.h"

class TKeyRing : public TItem {
private:
public:
	TKeyRing(const std::string& name, const std::string& code);
};
