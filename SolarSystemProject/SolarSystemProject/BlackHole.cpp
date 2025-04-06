#include "BlackHole.h"
#include <iostream>

BlackHole::BlackHole(float size, std::string name, std::string color, SolarSpace* space) : CelestialEntity(size, name, color)
{
	space->addBlackHole(this);
	setType("BlackHole");
	std::cout << "CreatedBlackHole!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}
