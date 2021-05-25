#pragma once

#include "library/httplib/httplib.h"
#include "app/controllers/game/game.h"
#include <memory>

class TApplication {
private:
	std::unique_ptr<httplib::Server> Server;
	TGame Game;
public:
	TApplication();
	void Start();
};
