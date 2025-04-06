#include "Planet.h"
#include "Sun.h"
#include <iostream>
#include "SolarSpace.h"
Planet::Planet(float size, std::string name, std::string color, SolarSpace* space) : CelestialEntity(size,name,color) {

	space->addPlanet(this);
	setType("Planet");
	std::cout << "CreatedPlanet\n";
}
bool Planet::checkTemperature()
{
	if (temperature > 100) {
		std::cout << "The temperature of the planet " << name << " is too high\nIt exploded." << std::endl;
		return true;
	}
	return false;
}

void Planet::setTemperature(float temperature)
{
	this->temperature = temperature ;
}



Planet::~Planet()
{
	std::cout << "Planet " << name << " destroyed" << std::endl;
}
