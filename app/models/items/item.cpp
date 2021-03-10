#include "item.h"

TItem::TItem(const std::string& russianName, const std::string& code): RussianName(russianName), Code(code) {}

const std::string& TItem::GetName() const {
	return RussianName;
}

const std::string& TItem::GetCode() const {
	return Code;
}
