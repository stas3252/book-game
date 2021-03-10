#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>

class TPlayer {
private:
	std::string UserName;
	int Gold;
	int Flask;
	int Agility; 
	int Strength;
	int Charisma;
	int MaxStrength;
	std::vector<bool> Luck;
	std::unordered_map<std::string, int> Spells;
public:
	TPlayer();
	const std::string& GetName() const;
	void SetName(const std::string& userName);
	
	void LockLuck(const int);
	int GetAgility() const;
	int GetStrength() const;
	int GetCharisma() const;
	std::tuple<int, int, int> GetRandomCharacteristics() const;
	void SetCharacteristics();
	
	void SetGold(const int);
	int GetGold()const;
	void GainGold(const int);
	void SpendGold(const int);
	bool HasEnoughGold(const int) const;
	
	int GetFlask() const;
	void SetFlask(const int);
	void GainFlask(const int);
	void SpendFlask(const int);
	bool HasEnoughFlask(const int) const;
	void DrinkFromFlask();

	void IncreaseStrenght(const int);

	void AddSpell(const std::pair<std::string, int>& spell);
	std::unordered_map<std::string, int> GetSpells() const;
};