#include "magic_belt.h"

TMagicBelt::TMagicBelt(const std::string& name, const std::string& code) : TItem(name, code) {
	/*
	-сразу +1 удача
	-если на каком-то левеле увидели Черный замок, можем призвать крота, он нам пророет путь
	в этот замок. (это типо переход на 167 левел)
	*/
}