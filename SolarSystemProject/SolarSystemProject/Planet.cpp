#include "Planet.h"
#include "Sun.h"
#include <iostream>
Planet::Planet(int size, int positions[2], float initialVelocity, bool habitable, std::string name,float distance_from_sun) :CelestialEntity(size, positions, initialVelocity) {
	this ->habitable = habitable;
	this->name = name;
	this->distance_from_sun = distance_from_sun;
	std::cout << "Planet " << name << " created" << std::endl;
}
bool Planet::checkTemperature()
{
	if (temperature > 100) {
		std::cout << "The temperature of the planet " << name << " is too high\nIt exploded." << std::endl;
		return true;
	}
	return false;
}
void Planet::increaseTemperature() {
	temperature += distance_from_sun/100;
	std::cout <<"Planet " <<name<<": " << temperature << '\n';
}

Planet::~Planet()
{
	std::cout << "Planet " << name << " destroyed" << std::endl;
}
