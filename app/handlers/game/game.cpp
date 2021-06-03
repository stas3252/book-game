#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include "library/json/json.h"

void NGameHandler::ApiNewGame(TGame& game, httplib::Response& res) {
	game.InitPlayer();
	res.set_content(game.GetPlayer().ToJson().dump(), "application/json");
}

void NGameHandler::ApiLevelGet(TGame& game, httplib::Response& res) {
	res.set_content(game.GetCurrentLevel().ToJson().dump(), "application/json");
}

void NGameHandler::ApiLevelPost(TGame& game, const httplib::Request& req, httplib::Response& res) {
	NJson::TJsonValue json = NJson::TJsonValue::parse(req.body);
	const std::string optionId = json["OptionId"];
	game.UpdateLevel(std::stoi(optionId));
	res.set_content(game.GetCurrentLevel().ToJson().dump(), "application/json");
}

void NGameHandler::ApiSetSpells(TGame& game, const httplib::Request& req, httplib::Response& res) {
	NJson::TJsonValue json = NJson::TJsonValue::parse(req.body);
	const std::string spells = json["MySpells"];
	std::cout << "Ну и где вывод?! я не понимаю!" << std::endl;
	std::vector<std::string> mySpells;
	std::string spell = "";
	for (int i = 0; i < spells.size(); i++) {
		spell.push_back(spells[i]);
		if (isdigit(spells[i])) {
			mySpells.push_back(spell);
			spell = "";
		}
	}
	game.InitPlayer(mySpells);
	res.set_content(game.GetPlayer().GetSpellsToJson().dump(), "application/json");
}
