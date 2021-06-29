#include "game.h"
#include "app/views/console_editor/console_editor.h"
#include "app/views/menu/menu.h"
#include "app/util/dice/dice.h"
#include "app/util/decoder/decoder.h"
#include "app/util/point/point.h"
#include "app/controllers/actions/action.h"
#include "app/controllers/actions/add_strength.h"
#include "app/controllers/actions/get_item.h"
#include "app/controllers/actions/get_gold.h"
#include "app/controllers/actions/add_flask.h"
#include "app/controllers/actions/add_extra_info.h"
#include "app/controllers/actions/spend_flask.h"
#include "app/controllers/actions/check_luck.h"
#include "app/controllers/actions/spend_strength.h"
#include "app/models/option/option.h"
#include "app/models/items/gold_whistle.h"
#include "app/models/items/awesome_diamant.h"
#include "app/models/items/food.h"
#include "app/models/items/lamp.h"
#include "app/models/items/silver_ring.h"
#include "app/models/items/amulet_with_bear_hair.h"
#include "app/models/items/fox_skin.h"
#include "app/models/items/magic_belt.h"
#include "app/models/items/claw_of_dragon.h"
#include "app/models/items/comb.h"
#include "app/models/items/stork_feather.h"
#include "app/models/items/deer_skin.h"
#include "app/models/items/key_ring.h"

#include <cstdio>
#include <windows.h>

#include <fstream>
#include <iostream>

TGame::TGame(const int currentLevel) : CurrentLevel(currentLevel) {}

void TGame::InitPlayer() {
	std::string name = "Stas";
	Player.SetName(name);
	Player.SetGold(15);
	Player.SetFlask(2);
	Player.AddItem(std::make_shared<TFood>("food", "food", 3));
	AllItems["food"] = std::make_shared<TFood>("food", "food", 3);
	Player.SetCharacteristics();
	Player.LockLuck(NDice::Roll6());
	Player.LockLuck(NDice::Roll6());
}

void TGame::InitSpells(const std::vector<std::string>& spells) {
	Player.InitSpells(spells);
}

NJson::TJsonValue TGame::GetPlayerSpellsJson() const {
	return Player.GetSpellsJson();
}

void TGame::ReadConfig() {
	std::ifstream file("./config.json");
	std::string s, res;

	while (getline(file, s)) {
		res += s;
	}
	NJson::TJsonValue data;
	try {
		data = NJson::TJsonValue::parse(res);	
	} catch(...) {
		std::cout << "check your json config" << std::endl;
		exit(0);
	}
	for (const auto& d: data) {
		std::vector<TOption> options;
		std::vector<std::shared_ptr<TAction>> actions;
		for (const auto& op: d["options"]) {
			if (op.find("price") != op.end()) {
				std::vector<std::pair<std::string, std::string>> price;
				for (const auto& pr: op["price"]) {
					price.emplace_back(pr["type"], pr["value"]);
				}
				options.emplace_back(op["to"], op["text"], price);
			} else {
				options.emplace_back(op["to"], op["text"]);
			}
		}

		if (d.find("actions") != d.end()) {
			for (const auto& act: d["actions"]) {
				if (act.find("name") == act.end()) continue;
				std::shared_ptr<TAction> currentAction;

				if (act["name"] == "add_strength") {
					currentAction = std::make_shared<TAddStrengthAction>(act["amount"]);
				}
				if (act["name"] == "spend_strength") {
					currentAction = std::make_shared<TSpendStrength>(act["amount"]);
				}
				if (act["name"] == "get_gold") {
					currentAction = std::make_shared<TGetGold>(act["amount"]);
				}
				if (act["name"] == "add_flask") {
					currentAction = std::make_shared<TAddFlask>(act["amount"]);
				}
				if (act["name"] == "spend_flask") {
					currentAction = std::make_shared<TSpendFlask>(act["amount"]);
				}
				if (act["name"] == "get_item") {
					currentAction = std::make_shared<TGetItem>(CreateItem(act));
				}
				if (act["name"] == "add_extra_info") {
					currentAction = std::make_shared<TAddExtraInfo>(act["info"]);
				}
				if (act["name"] == "check_luck") {
					currentAction = std::make_shared<TCheckLuck>(act["true"], act["false"]);
				}

				actions.push_back(std::move(currentAction));
			}	
		}
		Levels[d["id"]] = TLevel(d["id"], d["text"], options, actions);
	}
}

TPlayer& TGame::GetPlayer() {
	return Player;
}

TLevel& TGame::GetCurrentLevel() {
	return Levels.find(CurrentLevel)->second;
}

void TGame::UpdateLevel(const int optionId) {
	int tmpIdLevel = Levels[CurrentLevel].GetOptions(Player)[optionId].To;
	Levels[CurrentLevel].GetOptions(Player)[optionId].Pay(Player);
	CurrentLevel = tmpIdLevel;
}

std::shared_ptr<TItem> TGame::CreateItem(const NJson::TJsonValue& item) {
	if (AllItems.find(item["code"]) == AllItems.end()) {
		if (item["code"] == "awesome_diamant") {
			return AllItems[item["code"]] = std::make_shared<TAwesomeDiamant>(item["value"], item["code"]);
		}
		if (item["code"] == "gold_whistle") {
			return AllItems[item["code"]] = std::make_shared<TGoldWhistle>(item["value"], item["code"]);
		}
		if (item["code"] == "food") {
			return AllItems[item["code"]] = std::make_shared<TFood>(item["value"], item["code"], item["amount"]);
		}
		if (item["code"] == "silver_ring") {
			return AllItems[item["code"]] = std::make_shared<TSilverRing>(item["value"], item["code"]);
		}
		if (item["code"] == "lamp") {
			return AllItems[item["code"]] = std::make_shared<TLamp>(item["value"], item["code"]);
		}
		if (item["code"] == "amulet_with_bear_hair") {
			return AllItems[item["code"]] = std::make_shared<TAmuletWithBearHair>(item["value"], item["code"]);
		}
		if (item["code"] == "fox_skin") {
			return AllItems[item["code"]] = std::make_shared<TFoxSkin>(item["value"], item["code"]);
		}
		if (item["code"] == "magic_belt") {
			return AllItems[item["code"]] = std::make_shared<TMagicBelt>(item["value"], item["code"]);
		}
		if (item["code"] == "claw_of_dragon") {
			return AllItems[item["code"]] = std::make_shared<TClawOfDragon>(item["value"], item["code"]);
		}
		if (item["code"] == "comb") {
			return AllItems[item["code"]] = std::make_shared<TComb>(item["value"], item["code"]);
		}
		if (item["code"] == "stork_feather") {
			return AllItems[item["code"]] = std::make_shared<TStorkFeather>(item["value"], item["code"]);
		}
		if (item["code"] == "deer_skin") {
			return AllItems[item["code"]] = std::make_shared<TDeerSkin>(item["value"], item["code"]);
		}
		if (item["code"] == "key_ring") {
			return AllItems[item["code"]] = std::make_shared<TKeyRing>(item["value"], item["code"]);
		}
		std::cout << "code = " << item["code"] << std::endl;
		std::cout << "error has not this items!" << std::endl;
	} else {
		return AllItems[item["code"]];
	}
}

void TGame::UpdateBag(const std::unordered_multiset<std::string>& wonnaAddItems) {
	for (const auto& code: wonnaAddItems) {
		Player.AddItem(AllItems[code]);
	}
}

bool TGame::ValidAddItems(const std::unordered_multiset<std::string>& wonnaAddItems) const {
	std::unordered_multiset<std::string> realItems;
	for (const auto& item: Player.GetPlaceAddItems()) {
		realItems.insert(item.first);
	}
	for (const auto& item: Player.GetItems()) {
		realItems.insert(item.first);
	}
	for (const auto& code: wonnaAddItems) {
		if (realItems.count(code) < wonnaAddItems.count(code)) return false;
	}
	return true;
}
