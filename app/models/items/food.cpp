#include "food.h"

TFood::TFood(const std::string& nameFood, const std::string& code, const int amount) : TItem(nameFood, code), Amount(amount) {}
