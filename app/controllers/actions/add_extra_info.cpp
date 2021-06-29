#include "add_extra_info.h"

TAddExtraInfo::TAddExtraInfo(const std::string& info) : Info(info) {}

void TAddExtraInfo::Do(TPlayer& player) {
	player.AddExtraInfo(Info);
}
