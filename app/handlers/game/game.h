#pragma once
#include "app/controllers/game/game.h"
#include "library/httplib/httplib.h"

namespace NGameHandler { 
	void ApiNewGame(TGame&, httplib::Response&);
	void ApiLevelGet(TGame&, httplib::Response&);
	void ApiLevelPost(TGame&, const httplib::Request&, httplib::Response&);
	void ApiSetSpells(TGame&, const httplib::Request&, httplib::Response&);
};
