#include "BlackHole.h"
#include <iostream>

BlackHole::BlackHole(float size, std::string name, std::string color) : CelestialEntity(size, name, color)
{
	
	setType("BlackHole");
	std::cout << "CreatedBlackHole\n";
	density = 200000000;//densitate foarte mare
}
