#include "level.h"

TLevel::TLevel(
	const std::string& text,
	const std::vector<TOption>& options,
	const std::vector<std::shared_ptr<TAction>>& actions
): Text(text), Options(options), Actions(actions) {}

const std::vector<TOption>& TLevel::GetOptions() const {
	return Options;
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

NJson::TJsonValue TLevel::ToJson() const {
	std::vector<std::string> vs;
	for (const auto& s: GetOptions()) {
		vs.push_back(s.Text);
	}
	return {
		{"Text", Text},
		{"TextOptions", vs}
	};
}
