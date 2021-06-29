#pragma once

#include "app/models/player/player.h"
#include "app/models/level/level.h"
#include "library/json/json.h"
#include "app/models/items/item.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>

class TGame {
private:
	int CurrentLevel;
	TPlayer Player;
	std::unordered_map<int, TLevel> Levels;
	std::unordered_map<std::string, std::shared_ptr<TItem>> AllItems;
public:
	TGame(const int currentLevel = 1);
	void ReadConfig();
	void InitPlayer();
	TPlayer& GetPlayer();
	TLevel& GetCurrentLevel();
	void UpdateLevel(const int optionId);
	void InitSpells(const std::vector<std::string>&);
	NJson::TJsonValue GetPlayerSpellsJson() const;
	std::shared_ptr<TItem> CreateItem(const NJson::TJsonValue& item);
	void UpdateBag(const std::unordered_multiset<std::string>& wonnaAddItems);
	bool ValidAddItems(const std::unordered_multiset<std::string>& wonnaAdd) const;
};
