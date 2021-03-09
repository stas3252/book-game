#include "menu.h"
#include "app/views/console_editor/console_editor.h"

#include <iostream>

TMenu::TMenu(const std::vector<std::string>& options, const TPoint& leftUpAngle, const TPoint& rightDownAngle) : 
	Options(options), LeftUpAngle(leftUpAngle), RightDownAngle(rightDownAngle) {}

int TMenu::Show() const {
	int currentOption = 0;
	while (true) { 
	NConsoleEditor::ClearAreaSquare(LeftUpAngle, RightDownAngle);
		for (size_t i = 0; i < Options.size(); i++) {
			NConsoleEditor::GoToXY(TPoint(LeftUpAngle.X, LeftUpAngle.Y + i));
			if (i == currentOption) {
				NConsoleEditor::SetColor(NConsoleEditor::White);
				std::cout << Options[i];
				NConsoleEditor::SetColor(NConsoleEditor::Red);
			} else {	
				std::cout << Options[i];
			}
		}
		int key = NConsoleEditor::GetCh();
		if (NConsoleEditor::IsDown(key)) {
			currentOption++;
		} else if (NConsoleEditor::IsUp(key)) {
			currentOption--;
		}
		if (currentOption >= (int)Options.size()) {
			currentOption = 0;
		} else if (currentOption < 0) {
			currentOption = Options.size() - 1;
		}
		if (NConsoleEditor::IsEnter(key)) {
			break;
		};
	}
	return currentOption;
}

TPoint TMenu::GetLeftUpAngle() const {
	return LeftUpAngle;
}

TPoint TMenu::GetRightDownAngle() const {
	return RightDownAngle;
}
