#include "menu.h"
#include "app/views/console_editor/console_editor.h"

#include <iostream>

TMenu::TMenu(const std::vector<std::string>& options, const std::string& header): Options(options), Header(header) {}

int TMenu::Show() const {
	int currentOption = 0;
	while (true) { 
	NConsoleEditor::Clear();
	std::cout << Header << std::endl;
		for (size_t i = 0; i < Options.size(); i++) {
			if (i == currentOption) {
				NConsoleEditor::SetColor(NConsoleEditor::White);
				std::cout << Options[i] << std::endl;
				NConsoleEditor::SetColor(NConsoleEditor::Red);
			} else {	
				std::cout << Options[i] << std::endl;
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
