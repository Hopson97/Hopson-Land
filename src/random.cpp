#include "random.h"



int Random::num(int low, int high)// Generates a random number
{
	return rand() % (high - low + 1) + low;
}
