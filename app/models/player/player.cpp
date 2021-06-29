#include "player.h"

#include "app/util/dice/dice.h"

#include <algorithm>
#include <iostream>

TPlayer::TPlayer(): Luck(std::vector<bool>(6, true)) {}

const std::string& TPlayer::GetName() const {
	return UserName;
}

void TPlayer::AddExtraInfo(const std::string& info) {
	ExtraInfo.insert(info);
}
bool TPlayer::HasExtraInfo(const std::string& info) const {
	return ExtraInfo.find(info) != ExtraInfo.end();
}
void TPlayer::RemoveExtraInfo(const std::string& info) { // тут тоже аккуратно. только при проверке удаляем!
	ExtraInfo.erase(ExtraInfo.find(info));
}

void TPlayer::AddItemToPlaceAddItems(const std::shared_ptr<TItem> item) {
	PlaceAddItems[item->GetCode()] = item;
}
const std::unordered_map<std::string, std::shared_ptr<TItem>>& TPlayer::GetPlaceAddItems() const {
	return PlaceAddItems;
}
void TPlayer::RemoveAllItemsOnPlaceAddItems() {
	PlaceAddItems.clear();
}

void TPlayer::AddItem(const std::shared_ptr<TItem> item) {
	Items[item->GetCode()] = item;
}
const std::unordered_map<std::string, std::shared_ptr<TItem>>& TPlayer::GetItems() const {
	return Items;
}
void TPlayer::RemoveAllItemsOnItems() {
	Items.clear();
}
void TPlayer::RemoveItem(const std::string& code) { // это дело сделано опасно, надежда, что перед удалением, мы уверены, что этот предмет точно есть
	for (auto item = Items.begin(); item != Items.end(); item++) {
		if (item->first == code) {
			Items.erase(item);
			return;
		}
	}
}
bool TPlayer::HasItem(const std::string& code) const {
	for (const auto& item: Items) {
		if (item.first == code) {
			return true;
		} 
	}
	return false;
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
	IncreaseStrength(2);
}
void TPlayer::IncreaseStrength(const int strength) {
	Strength = std::min(Strength + strength, MaxStrength);
}
void TPlayer::SpendStrength(const int strength) {
	Strength -= strength;
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
bool TPlayer::UseLuck() {
	int res = NDice::Roll6();
	if (Luck[res - 1] == true) {
		LockLuck(res);
		return true;
	} else {
		return false;
	}
}

void TPlayer::InitSpells(const std::vector<std::string>& spells) {
	for (const auto& spell: spells) {
		AddSpell(spell);
	}
}

void TPlayer::AddSpell(const std::string& spell) {
	Spells.insert(spell);
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
	Spells.erase(currentSpell);
}

NJson::TJsonValue TPlayer::GetSpellsJson() const {
	std::vector<std::string> spells;
	for (const auto& spell: Spells) {
		spells.push_back(spell);
	}
	return {{"MySpells", spells}};
}

NJson::TJsonValue TPlayer::ToJson() const {
	std::vector<std::string> myItems;
	for (const auto& item: Items) {
		myItems.push_back(item.first);
	}

	std::vector<std::string> placeAddItems;
	for (const auto& item: PlaceAddItems) {
		placeAddItems.push_back(item.first);
	}
	return {
		{"Name", UserName}, 
		{"Gold", Gold},
		{"Flask", Flask},
		{"Agility", Agility},
		{"Strength", Strength},
		{"Charisma", Charisma},
		{"MaxStrength", MaxStrength},
		{"Luck", Luck},
		{"MySpells", Spells},
		{"MyItems", myItems},
		{"PlaceAddItems", placeAddItems}
	};
}