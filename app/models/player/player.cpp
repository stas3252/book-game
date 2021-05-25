#include "player.h"

#include "app/util/dice/dice.h"

#include <algorithm>
#include <iostream>

TPlayer::TPlayer(): Luck(std::vector<bool>(6, true)) {}

const std::string& TPlayer::GetName() const {
	return UserName;
}

void TPlayer::SetAmountItems() {
	Items.resize(7, nullptr);
}
void TPlayer::AddItem(const int position, const std::string& nameItem) {
	if (position >= 0 && position < 7) {
		if (nameItem == "Еда") {
			Items[position] = new TFood(nameItem, nameItem, 3);
		}
	} else {
		throw "addItem unreal position, position diapason (0 - 7)";
	}
}
void RemoveItem(const int position) {
	if (position >= 0 && position < 7) {
		void RemoveItem(const int position);
	} else {
		throw "RemoveItem unreal position, position diapason (0 - 7)";
	}
}
const std::vector<TItem*>& TPlayer::GetItems() const {
	return Items;
}

int TPlayer::GetAgility() const {
	return Agility;
}

int TPlayer::GetStrength() const {
	return Strength;
}

int TPlayer::GetCharisma() const {
	return Charisma;
}

void TPlayer::SetName(const std::string& userName) {	
	UserName = userName;
}

void TPlayer::SetGold(const int gold) {
	Gold = gold;
}
int TPlayer::GetGold()const {
	return Gold;
}
void TPlayer::GainGold(const int gold) {
	Gold += gold;
}
void TPlayer::SpendGold(const int gold) {
	if (!HasEnoughGold(gold)) {
		throw "not enough gold";
	}
	Gold -= gold;
}
bool TPlayer::HasEnoughGold(const int gold) const {
	return Gold >= gold;
}

int TPlayer::GetFlask() const {
	return Flask;
}
void TPlayer::SetFlask(const int flask) {
	Flask = flask;
}
void TPlayer::GainFlask(const int flask) { 
	Flask += flask;
}
void TPlayer::SpendFlask(const int flask) {
	if (!HasEnoughFlask(flask)) {
		throw "not enough flask";
	}
	Flask -= flask;
}
bool TPlayer::HasEnoughFlask(const int flask) const {
	return Flask >= flask;
}
void TPlayer::DrinkFromFlask() {
	SpendFlask(1);
	IncreaseStrenght(2);
}
void TPlayer::IncreaseStrenght(const int strength) {
	Strength = std::min(Strength + strength, MaxStrength);
}

std::tuple<int, int, int> TPlayer::GetRandomCharacteristics() const {
	std::vector<std::tuple<int, int, int>> characteristics = {
		{8, 22, 8}, 
		{10, 20, 6},
		{12, 16, 5},
		{9, 18, 8},
		{11, 20, 6},
		{9, 20, 7},
		{10, 16, 7},
		{8, 24, 7},
		{9, 22, 6},
		{10, 18, 7},
		{11, 20, 5}
	};
	return characteristics[NDice::Roll6() + NDice::Roll6() - 2];
};

void TPlayer::SetCharacteristics() {
	const auto characteristics = TPlayer::GetRandomCharacteristics();
	Agility = std::get<0>(characteristics);
	Charisma = std::get<1>(characteristics);
	Strength = std::get<2>(characteristics);
	MaxStrength = Strength;
};

void TPlayer::LockLuck(const int roll) {
	Luck[roll - 1] = false;
}

void TPlayer::AddSpell(const std::pair<std::string, int>& spell) {
	Spells[spell.first] = spell.second;
}

std::unordered_map<std::string, int> TPlayer::GetSpells() const {
	return Spells;
}

bool TPlayer::HasSpell(const std::string& nameSpell) const {
	auto spell = Spells.find(nameSpell);
	return spell != Spells.end();
}

void TPlayer::UseSpell(const std::string& nameSpell) {
	if (!HasSpell(nameSpell)) {
		throw "not use spell";
	} 
	auto currentSpell = Spells.find(nameSpell);
	if (--currentSpell->second == 0) {
		Spells.erase(currentSpell);
	}
}

NJson::TJsonValue TPlayer::ToJson() const {
	return {
		{"Name", UserName}, 
		{"Gold", Gold},
		{"Flask", Flask},
		{"Agility", Agility},
		{"Strength", Strength},
		{"Charisma", Charisma},
		{"MaxStrength", MaxStrength},
		{"Luck", Luck},
		{"Spells", Spells},
		//{"Items", Items}
	};
}