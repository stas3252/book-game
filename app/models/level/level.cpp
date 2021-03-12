#include "level.h"

TLevel::TLevel(
	const std::string& text,
	const std::vector<std::pair<int, std::string>>& options,
	const std::vector<std::shared_ptr<TAction>>& actions
): Text(text), Options(options), Actions(actions) {}

const std::vector<std::pair<int, std::string>>& TLevel::GetOptions() const {
	return Options;
}

const std::string& TLevel::GetText() const {
	return Text;
}

const std::vector<std::shared_ptr<TAction>>& TLevel::GetActions() const {
	return Actions;
}
