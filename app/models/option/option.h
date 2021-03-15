#pragma once

#include <string>
#include <vector>

struct TOption {
	int To;
	std::string Text;
	std::vector<std::pair<std::string, std::string>> Price;
	TOption() = default;
	TOption(const int to, const std::string text);
	TOption(const int to, const std::string text, const std::vector<std::pair<std::string, std::string>>& price);
};
