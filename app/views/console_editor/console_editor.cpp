#include "console_editor.h"

#include <conio.h>
#include <windows.h>

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


