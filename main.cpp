#include "app/controllers/game/game.h"
#include <windows.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	// SetConsoleCP(1251);
	// SetConsoleOutputCP(1251);

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	srand(time(0));
	TGame game(1);
	game.Start();
	return 0;
}
