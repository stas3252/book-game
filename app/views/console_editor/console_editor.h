#pragma once
#include "app/util/point/point.h"
namespace NConsoleEditor {
	enum ConsoleColor {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
	bool IsEnter(const int key);
	bool IsDown(const int key);
	bool IsUp(const int key);
	int GetCh();
	void Clear();
	void SetColor(const ConsoleColor textColor, const ConsoleColor backGroundColor = Black);
	void GoToXY(const TPoint& point);
	bool IsRight(const int key);
	bool IsLeft(const int key);
};

