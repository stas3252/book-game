#pragma once
#include <string>

class TItem {
private:
	std::string RussianName;
	std::string Code;
public:
	TItem() = default;
	TItem(const std::string& russianName, const std::string& code);
	const std::string& GetName() const;
	const std::string& GetCode() const;
};
