#pragma once

#include <vector>
#include <string>
#include "app/util/point/point.h"

class TMenu {
private:
	TPoint LeftUpAngle;
	TPoint RightDownAngle;
	std::vector<std::string> Options;
public:
	TMenu() = default;
	TMenu(const std::vector<std::string>& options, const TPoint& leftUpAngle, const TPoint& rightDownAngle);
	int Show() const;
	TPoint GetLeftUpAngle() const;
	TPoint GetRightDownAngle() const;
};

