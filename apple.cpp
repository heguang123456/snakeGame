#include "apple.h"
#include <stdlib.h>
APPLE* p_apple = (APPLE*)malloc(sizeof(APPLE));
void newApple(void)
{
	p_apple->hang = (unsigned)rand() % 14 + 3;
	p_apple->lie = (unsigned)rand() % 14 + 3;
}
