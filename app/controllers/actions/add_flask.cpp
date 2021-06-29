#include "add_flask.h"

TAddFlask::TAddFlask(const int amount) : Amount(amount) {}

void TAddFlask::Do(TPlayer& player) {
	player.GainFlask(Amount);
}
