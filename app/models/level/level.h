#pragma once
#include <string>
#include <vector>
#include <memory>

#include "app/controllers/actions/action.h"

class TLevel {
private:
	std::string Text;
	std::vector<std::pair<int, std::string>> Options;
	std::vector<std::shared_ptr<TAction>> Actions;
public:
	TLevel() = default;
	TLevel(
		const std::string& text,
		const std::vector<std::pair<int, std::string>>& options,
		const std::vector<std::shared_ptr<TAction>>& actions
	);
	const std::vector<std::pair<int, std::string>>& GetOptions() const;
	const std::string& GetText() const;
	const std::vector<std::shared_ptr<TAction>>& GetActions() const;
};
