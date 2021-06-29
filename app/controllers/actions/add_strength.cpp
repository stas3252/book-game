#include "add_strength.h"

TAddStrengthAction::TAddStrengthAction(const int amount) : Amount(amount) {}

void TAddStrengthAction::Do(TPlayer& player) {
	player.IncreaseStrength(Amount);
}
