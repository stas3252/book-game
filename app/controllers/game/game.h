#pragma once

#include "app/models/player/player.h"
#include "app/models/level/level.h"

#include <unordered_map>
#include <string>
#include <vector>

class TGame {
private:
	int CurrentLevel;
	TPlayer Player;
	std::unordered_map<int, TLevel> Levels;
public:
	TGame(const int currentLevel = 1);
	void Start();
	void New();
	void ReadConfig();
	void Run();
	void InitSpells();
	void InitPlayer();
	void ShowInfoAboutPlayer() const;
};

