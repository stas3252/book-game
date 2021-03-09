#include "dice.h"
#include <stdlib.h>

int NDice::Roll6() {
	return (rand() % 6) + 1;
}
