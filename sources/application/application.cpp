#include "application.h"
#include "app/handlers/game/game.h"

#include <iostream>

TApplication::TApplication() {
	Server.reset(new httplib::Server());
	Server->Get("/api/new-game", [&](const httplib::Request& req, httplib::Response& res){
		NGameHandler::ApiNewGame(Game, res);
	});
}

void TApplication::Start() {
	std::cout << "Server started" << std::endl;
	Server->listen("0.0.0.0", 1234);
	Game.ReadConfig();
}
