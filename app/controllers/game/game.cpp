#include "game.h"
#include "app/views/console_editor/console_editor.h"
#include "app/views/menu/menu.h"
#include "app/util/dice/dice.h"
#include "app/util/json/json.h"
#include "app/util/decoder/decoder.h"
#include "app/util/point/point.h"
#include "app/controllers/actions/action.h"
#include "app/controllers/actions/add_strength.h"

#include <cstdio>
#include <windows.h>

#include <fstream>
#include <iostream>

TGame::TGame(const int currentLevel) : CurrentLevel(currentLevel) {}

void TGame::Start() {
	ReadConfig();
	NConsoleEditor::SetColor(NConsoleEditor::Red);
	
	NConsoleEditor::Clear();
	TMenu menu({"Новая игра", "Çàãðèçèòü", "Ñîõðàíèòü", "Ñîõðàíèòü è âûéòè", "Âûéòè"}, TPoint(0, 0), TPoint(15, 10));
	
	int n = menu.Show();
	if (n == 0) {
		New();
	}
}

void TGame::New() {
	NConsoleEditor::Clear();
	InitPlayer();
	Run();
}

void TGame::InitPlayer() {
	std::cout << "Введите имя: ";
	std::string name;
	std::cin >> name;
	Player.SetName(name);
	Player.SetGold(15);
	Player.SetFlask(2);
	Player.SetAmountItems();
	Player.AddItem(0, "Åäà");
	Player.SetCharacteristics();
	Player.LockLuck(NDice::Roll6());
	Player.LockLuck(NDice::Roll6());
	InitSpells();
}

void TGame::ReadConfig() {
	std::ifstream file("../config.json");
	std::string s, res;

	while (getline(file, s)) {
		res += s;
	}
	NJson::TJsonValue data = NJson::TJsonValue::parse(res);

	for (const auto& d: data) {
		std::vector<std::pair<int, std::string>> options;
		std::vector<std::shared_ptr<TAction>> actions;
		for (const auto& op: d["options"]) {
			options.emplace_back(op["to"], op["text"]);
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

void TGame::Run() {
	while (true) {
		NConsoleEditor::Clear();
		ShowInfoAboutPlayer();
		std::vector<std::string> vs;
		for (const auto& s: Levels[CurrentLevel].GetOptions()) {
			vs.push_back(s.second);
		}
		std::cout << Levels[CurrentLevel].GetText() << std::endl;
		std::cout << "_______________________________" << std::endl;
		auto currentPoint = NConsoleEditor::GetCursorPosition();
		TMenu menu(vs, TPoint(currentPoint.X, currentPoint.Y + 1), TPoint(currentPoint.X + 10, currentPoint.Y + 5));
		int chosen = menu.Show();
		CurrentLevel = Levels[CurrentLevel].GetOptions()[chosen].first;
	}
}

void TGame::ShowInfoAboutPlayer() const {
	std::cout << "Èìÿ: " << Player.GetName() <<", Çîëîòî: " << Player.GetGold() << ", Ôëÿãà: " << Player.GetFlask()
		<< ", Ëîâêîñòü: " << Player.GetAgility() << ", Ñèëà: " << Player.GetStrength() << ", Õàðçìà: " << Player.GetCharisma() 
		<< std::endl;
		std::cout << "Çàêëèíàíèÿ:" << std::endl;
	for (const auto& spell: Player.GetSpells()) {
		std::cout << spell.first << " " << spell.second << std::endl;
	}
	for (const auto& item: Player.GetItems()) {
		if (item != nullptr) {
			std::cout << item->GetName() << " " << item->GetCode() << std::endl;
		} else {
			std::cout << "Ïóñòî" << std::endl;
		}
	}
	std::cout << "_________________________" << std::endl;
}

void TGame::InitSpells() {
	std::vector<std::pair<std::string, int> > spells = {
		{"à", 0},
		{"á", 0},
		{"â", 0},
		{"ã", 0},
		{"ä", 0},
		{"å", 0},
		{"¸", 0},
		{"æ", 0}};
	std::string header = "Âûáåðèòå çàêëèíàíèÿ!";
	int currentOption = 0;
	const int maxWidget = 10;
	int currentWidget = 0;
	while (true) { 
		NConsoleEditor::Clear();
		std::cout << header << std::endl;
		for (size_t i = 0; i < spells.size(); i++) {
			if (i == currentOption) {
				NConsoleEditor::SetColor(NConsoleEditor::White);
				std::cout << spells[i].first << " " << spells[i].second << std::endl;
				NConsoleEditor::SetColor(NConsoleEditor::Red);
			} else {
				std::cout << spells[i].first << " " << spells[i].second << std::endl;
			}
		}
		int key = NConsoleEditor::GetCh();
		if (NConsoleEditor::IsRight(key)) {
			if (currentWidget < maxWidget) {
				spells[currentOption].second++;
				currentWidget++;
			}
		} else if (NConsoleEditor::IsLeft(key)) {
			if (spells[currentOption].second > 0) {
				spells[currentOption].second--;
				currentWidget--;
			}
		}
		if (NConsoleEditor::IsDown(key)) {
			currentOption++;
		} else if (NConsoleEditor::IsUp(key)) {
			currentOption--;
		}
		if (currentOption >= (int)spells.size()) {
			currentOption = 0;
		} else if (currentOption < 0) {
			currentOption = spells.size() - 1;
		}
		if (NConsoleEditor::IsEnter(key)) {
			if (currentWidget == 10) {
				for (const auto& spell: spells) {
					if (spell.second) {
						Player.AddSpell(spell);
					}
				}
				break;
			}	
		}
	}
	return;
}

