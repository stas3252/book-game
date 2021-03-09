#pragma once

#include <vector>
#include <string>

class TMenu {
private:
	std::vector<std::string> Options;
	std::string Header;
public:
	TMenu() = default;
	TMenu(const std::vector<std::string>& options, const std::string& header);
	int Show() const;
};

