#include "Planet.h"
#include "Sun.h"
#include <iostream>
#include "SolarSpace.h"
Planet::Planet(float size, std::string name, std::string color, SolarSpace* space) : CelestialEntity(size,name,color) {

	space->addCelBody(this);
	setType("Planet");
	std::cout << "CreatedPlanet\n";
	density = 10000;
}

Planet::~Planet()
{
	std::cout << "Planet " << name << " destroyed" << std::endl;
}
