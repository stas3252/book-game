#include "get_gold.h"

TGetGold::TGetGold(const int amount) : Amount(amount) {}

void TGetGold::Do(TPlayer& player) {
	player.GainGold(Amount);
}
