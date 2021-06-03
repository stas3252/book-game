#include "game.h"
#include "app/views/console_editor/console_editor.h"
#include "app/views/menu/menu.h"
#include "app/util/dice/dice.h"
#include "library/json/json.h"
#include "app/util/decoder/decoder.h"
#include "app/util/point/point.h"
#include "app/controllers/actions/action.h"
#include "app/controllers/actions/add_strength.h"
#include "app/models/option/option.h"

#include <cstdio>
#include <windows.h>

#include <fstream>
#include <iostream>

TGame::TGame(const int currentLevel) : CurrentLevel(currentLevel) {}

void TGame::InitPlayer(const std::vector<std::string>& spells) {
	std::string name = "Stas";
	Player.SetName(name);
	Player.SetGold(15);
	Player.SetFlask(2);
	Player.SetAmountItems();
	Player.AddItem(0, "Еда");
	Player.SetCharacteristics();
	Player.LockLuck(NDice::Roll6());
	Player.LockLuck(NDice::Roll6());
	for(const auto& spell: spells) {
		Player.AddSpell({spell, 1});
	}
}

void TGame::ReadConfig() {
	std::ifstream file("./config.json");
	std::string s, res;

	while (getline(file, s)) {
		res += s;
	}
	NJson::TJsonValue data = NJson::TJsonValue::parse(res);

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
				std::shared_ptr<TAction> currentAction;
				if (act["name"] == "add_strength") {
					currentAction = std::make_shared<TAddStrengthAction>(act["amount"]);
				}
				actions.push_back(std::move(currentAction));
			}	
		}
		Levels[d["id"]] = TLevel(d["text"], options, actions);
	}
}

const TPlayer& TGame::GetPlayer() const {
	return Player;
}

const TLevel& TGame::GetCurrentLevel() const {
	return Levels.find(CurrentLevel)->second;
}

void TGame::UpdateLevel(const int optionId) {
	CurrentLevel = Levels[CurrentLevel].GetOptions()[optionId].To;
}
