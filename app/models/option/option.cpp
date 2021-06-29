#include "option.h"

#include <iostream>

TOption::TOption(const int to, const std::string text, const std::vector<std::pair<std::string, std::string>>& price)
	: To(to), Text(text), Price(price) {} 
TOption::TOption(const int to, const std::string text) : To(to), Text(text) {}

bool TOption::CanBeChoosen(const TPlayer& player) const {
	for (const auto& price: Price) {
		if (price.first == "spell") {
			if (!player.HasSpell(price.second)) {
				return false;
			}
		}
		if (price.first == "spend_flask") {
			if (!player.HasEnoughFlask(atoi(price.second.c_str()))) {
				return false;
			}
		}
		if (price.first == "item") {
			if (!player.HasItem(price.second)) {
				return false;
			}
		}
		if (price.first == "extra_info") {
			if (!player.HasExtraInfo(price.second)) {
				return false;
			}
		}
		if (price.first == "gold") {
			if (!player.HasEnoughGold(atoi(price.second.c_str()))) {
				return false;
			}
		}
	}
	return true;
}

void TOption::Pay(TPlayer& player) const {
	for (const auto& price: Price) {
		if (price.first == "spell") {
			player.UseSpell(price.second);
		}
		if (price.first == "spend_flask") {
			player.SpendFlask(atoi(price.second.c_str()));
		}
		if (price.first == "item") {
			player.RemoveItem(price.second);
		}
		if (price.first == "extra_info") {
			player.RemoveExtraInfo(price.second);
		}
		if (price.first == "gold") {
			player.SpendGold(atoi(price.second.c_str()));
		}
	}
}