#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include "library/json/json.h"
#include "app/models/items/item.h"

void NGameHandler::ApiNewGame(TGame& game, httplib::Response& res) {
	game.InitPlayer();
	res.set_content(game.GetPlayer().ToJson().dump(), "application/json");
}

void NGameHandler::ApiLevelGet(TGame& game, httplib::Response& res) {
	const NJson::TJsonValue& result = {
		{ "Level", game.GetCurrentLevel().ToJson(game.GetPlayer()) },
		{ "Player", game.GetPlayer().ToJson() }
	};
	res.set_content(result.dump(), "application/json");
}

void NGameHandler::ApiLevelPost(TGame& game, const httplib::Request& req, httplib::Response& res) {
	NJson::TJsonValue json = NJson::TJsonValue::parse(req.body);
	const std::string items = json["Bag"];
	std::string codeItem;
	std::unordered_multiset<std::string> wonnaAddItems;
	for (const auto& c: items) {
		if (c == '/') {
			wonnaAddItems.insert(codeItem);
			codeItem = "";
		} else {
			codeItem.push_back(c);
		}
	} 
	if (game.ValidAddItems(wonnaAddItems)) {
		//валицация прошла, меняем рюкзак
		game.GetPlayer().RemoveAllItemsOnPlaceAddItems();
		game.GetPlayer().RemoveAllItemsOnItems();
		game.UpdateBag(wonnaAddItems);
	} else {
		std::cout << "validate for Items error (game/handler::ApiLevelPost)" << std::endl;
		exit(0);
	}
	const std::string optionId = json["OptionId"];
	game.UpdateLevel(std::stoi(optionId));
	game.GetCurrentLevel().DoActions(game.GetPlayer());
	res.set_content(game.GetCurrentLevel().ToJson(game.GetPlayer()).dump(), "application/json");
}

void NGameHandler::ApiSetSpells(TGame& game, const httplib::Request& req, httplib::Response& res) {
	NJson::TJsonValue json = NJson::TJsonValue::parse(req.body);
	const std::string spells = json["MySpells"];
	std::vector<std::string> mySpells;
	std::string spell = "";
	for (int i = 0; i < spells.size(); i++) {
		if (spells[i] == '/') {
			mySpells.push_back(spell);
			spell = "";
		} else {
			spell.push_back(char(spells[i]));
		}
	}
	game.InitSpells(mySpells);
	res.set_content(game.GetPlayerSpellsJson().dump(), "application/json");
}
