#include "check_luck.h"
#include <iostream>

TCheckLuck::TCheckLuck(const NJson::TJsonValue& dataTrue, const NJson::TJsonValue& dataFalse) : DataTrue(dataTrue), DataFalse(dataFalse) {}

void TCheckLuck::Do(TPlayer& player) {
	bool result = player.UseLuck();
	if (result == true) {
		if (DataTrue["type"] == "add_extra_info") {
			player.AddExtraInfo(DataTrue["info"]);
		}
	} else {
		std::cout << "FALSE" << std::endl;
	}
}
