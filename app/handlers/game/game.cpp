#include "game.h"

void NGameHandler::ApiNewGame(TGame& game, httplib::Response& res) {
	game.InitPlayer();
	res.set_content(game.GetPlayer().ToJson().dump(), "application/json");
}