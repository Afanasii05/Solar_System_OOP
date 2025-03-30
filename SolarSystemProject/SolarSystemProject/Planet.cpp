#include "Planet.h"
#include "Sun.h"
#include <iostream>
#include "SolarSpace.h"
Planet::Planet(float size, bool habitable, std::string name,int orbitingSun) : CelestialEntity(size) {
	this ->habitable = habitable;
	this->orbitingSun = orbitingSun;
	this->name = name;
	std::cout << "Planet " << name << " created" << std::endl;
	setType("Planet");
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
