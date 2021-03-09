#include "level.h"

TLevel::TLevel(const std::string& text, const std::vector<std::pair<int, std::string>>& options): Text(text), Options(options) {};

std::vector<std::pair<int, std::string>> TLevel::GetOptions() {
	return Options;
};
std::string TLevel::GetText() {
	return Text;
}
