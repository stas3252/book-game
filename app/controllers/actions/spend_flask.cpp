#include "spend_flask.h"

TSpendFlask::TSpendFlask(const int amount) : Amount(amount) {}

void TSpendFlask::Do(TPlayer& player) {
	player.SpendFlask(Amount);
}
