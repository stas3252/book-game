#include "option.h"

TOption::TOption(const int to, const std::string text, const std::vector<std::pair<std::string, std::string>>& price)
	: To(to), Text(text), Price(price) {} 
TOption::TOption(const int to, const std::string text) : To(to), Text(text) {}