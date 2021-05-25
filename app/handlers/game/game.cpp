#include "game.h"
#include <iostream>
#include <string>
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
	std::cout << "op: " << optionId << std::endl;
	game.UpdateLevel(std::stoi(optionId));
	res.set_content(game.GetCurrentLevel().ToJson().dump(), "application/json");
}
