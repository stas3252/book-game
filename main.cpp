#include "app/controllers/game/game.h"
#include "sources/application/application.h"
#include <windows.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	srand(time(0));
	std::unique_ptr<TApplication> application;
	application.reset(new TApplication());
	application->Start();
	return 0;
}
