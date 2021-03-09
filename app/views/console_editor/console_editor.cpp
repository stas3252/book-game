#include "console_editor.h"

#include <conio.h>
#include <windows.h>
#include <iostream>

bool NConsoleEditor::IsEnter(const int key) {
	return key == 13;
}

bool NConsoleEditor::IsDown(const int key) {
	return key == 1080;
}

bool NConsoleEditor::IsUp(const int key) {
	return key == 1072;
}

bool NConsoleEditor::IsRight(const int key)  {
	return key == 1077;
}

bool NConsoleEditor::IsLeft(const int key) {
	return key == 1075;
}

int NConsoleEditor::GetCh() {
	int key = getch();
	if (key == 224) {
		key = 1000 + getch();
	}
	return key;
}

void NConsoleEditor::Clear() {
	system("cls");
}	

void NConsoleEditor::SetColor(const ConsoleColor textColor, const ConsoleColor backGroundColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD) ((backGroundColor << 4) | textColor));
}

void NConsoleEditor::GoToXY(const TPoint& point) {
	COORD kursor;
	kursor.X = point.X;
	kursor.Y = point.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
}

void NConsoleEditor::ClearAreaSquare(const TPoint& leftUpAngle, const TPoint& rightDownAngle) {
	for (int i = leftUpAngle.Y; i <= rightDownAngle.Y; ++i) {
		for (int j = leftUpAngle.X; j<= rightDownAngle.X; ++j) {
			GoToXY(TPoint(j, i));
			std::cout << " ";
		}
	}
}

TPoint NConsoleEditor::GetCursorPosition() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (!GetConsoleScreenBufferInfo(hConsole, &cbsi)) {
		throw "Error with cursor";
	}
	return TPoint(cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y);
}