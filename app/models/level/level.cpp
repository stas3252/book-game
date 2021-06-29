#include "level.h"
#include <iostream>

TLevel::TLevel(
	const int id,
	const std::string& text,
	const std::vector<TOption>& options,
	const std::vector<std::shared_ptr<TAction>>& actions
): Id(id), Text(text), Options(options), Actions(actions) {}

std::vector<TOption> TLevel::GetOptions(const TPlayer& player) const {
	std::vector<TOption> options;
	for (const auto& option: Options) {
		if (option.CanBeChoosen(player)) {
			options.push_back(option);
		}
	}
	return options;
}

const std::string& TLevel::GetText() const {
	return Text;
}

const std::vector<std::shared_ptr<TAction>>& TLevel::GetActions() const {
	return Actions;
}

void TLevel::DoActions(TPlayer& player) {
	for (const auto& act: Actions) {
		act->Do(player);
	}
}

NJson::TJsonValue TLevel::ToJson(const TPlayer& player) const {
	std::vector<std::string> vs;
	for (const auto& option: GetOptions(player)) {
		vs.push_back(option.Text);
	}
	return {
		{"Text", Text},
		{"TextOptions", vs},
		{"Id", Id}
	};
}
