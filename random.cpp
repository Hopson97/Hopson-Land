#include "random.h"



random::random()
{
    //ctor
}

int random::num(int low, int high)// Generates a random number
{
	return rand() % (high - low + 1) + low;
}

random::~random()
{
    //dtor
}
