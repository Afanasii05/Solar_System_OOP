#include <iostream>
#include "CelestialEntity.h"
#include "Sun.h"

int main()
{
	float positions[2] = { 0,0 };
	Sun newsun(10, positions, 0, 10000, "yellow", "Marinica");

	return 0;
}