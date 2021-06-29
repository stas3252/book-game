#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cstddef>
#include <memory>

#include "app/models/items/item.h"
#include "app/models/items/food.h"
#include "library/json/json.h"

class TPlayer {
private:
	std::string UserName;
	int Gold;
	int Flask;
	int Agility; 
	int Strength;
	int Charisma;
	int MaxStrength;
	std::vector<bool> Luck;
	std::multiset<std::string> Spells;
	std::unordered_map<std::string, std::shared_ptr<TItem>> Items;
	std::unordered_map<std::string, std::shared_ptr<TItem>> PlaceAddItems;
	std::unordered_set<std::string> ExtraInfo;
public:
	TPlayer();
	const std::string& GetName() const;
	void SetName(const std::string& userName);

	void AddExtraInfo(const std::string& info);
	bool HasExtraInfo(const std::string& info) const;
	void RemoveExtraInfo(const std::string& info);
	
	void AddItemToPlaceAddItems(const std::shared_ptr<TItem> item);
	const std::unordered_map<std::string, std::shared_ptr<TItem>>& GetPlaceAddItems() const;
	void RemoveAllItemsOnPlaceAddItems();

	void AddItem(const std::shared_ptr<TItem> item);
	const std::unordered_map<std::string, std::shared_ptr<TItem>>& GetItems() const;
	void RemoveAllItemsOnItems();
	void RemoveItem(const std::string& code);
	bool HasItem(const std::string& code) const;



	void LockLuck(const int);
	bool UseLuck();

	int GetAgility() const;
	
	int GetCharisma() const;
	std::tuple<int, int, int> GetRandomCharacteristics() const;
	void SetCharacteristics();
	
	void SetGold(const int);
	int GetGold()const;
	void GainGold(const int);
	void SpendGold(const int);
	bool HasEnoughGold(const int) const;
	
	int GetFlask() const;
	void SetFlask(const int);
	void GainFlask(const int);
	void SpendFlask(const int);
	bool HasEnoughFlask(const int) const;
	void DrinkFromFlask();

	int GetStrength() const;
	void IncreaseStrength(const int);
	void SpendStrength(const int);

	void InitSpells(const std::vector<std::string>&);
	void AddSpell(const std::string& spell);
	bool HasSpell(const std::string& nameSpell) const;
	void UseSpell(const std::string& nameSpell);
	NJson::TJsonValue GetSpellsJson() const;

	NJson::TJsonValue ToJson() const;
};
