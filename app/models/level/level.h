#pragma once
#include <string>
#include <vector>

class TLevel {
private:
	std::string Text;
	std::vector<std::pair<int, std::string>> Options;
public:
	TLevel() = default;
	TLevel(const std::string& text, const std::vector<std::pair<int, std::string>>& options);
	std::vector<std::pair<int, std::string>> GetOptions();
	std::string GetText();
};
