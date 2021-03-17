#pragma once
#include "app/controllers/game/game.h"
#include "library/httplib/httplib.h"

namespace NGameHandler { 
	void ApiNewGame(TGame&, httplib::Response&);
};