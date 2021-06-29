#include "spend_strength.h"

TSpendStrength::TSpendStrength(const int amount) : Amount(amount) {}

void TSpendStrength::Do(TPlayer& player) {
	player.SpendStrength(Amount);
}
