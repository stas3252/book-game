#pragma once
#include <string>
#include <vector>
#include <memory>

#include "app/controllers/actions/action.h"
#include "app/models/option/option.h"
#include "app/models/player/player.h"
#include "library/json/json.h"

class TLevel {
private:
	int Id;
	std::string Text;
	std::vector<TOption> Options;
	std::vector<std::shared_ptr<TAction>> Actions;
public:
	TLevel() = default;
	TLevel(
		const int id,
		const std::string& text,
		const std::vector<TOption>& options,
		const std::vector<std::shared_ptr<TAction>>& actions
	);
	std::vector<TOption> GetOptions(const TPlayer& player) const;
	const std::string& GetText() const;
	const std::vector<std::shared_ptr<TAction>>& GetActions() const;
	void DoActions(TPlayer&);
	NJson::TJsonValue ToJson(const TPlayer& player) const;

};
