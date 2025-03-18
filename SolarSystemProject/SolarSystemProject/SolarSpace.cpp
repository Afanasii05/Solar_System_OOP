/*
#include "SolarSpace.h"

SolarSpace::SolarSpace(const int size_x, const int size_y, char name[30])
{
	this->size_x = size_x;
	this->size_y = size_y;
	strcpy(this->name, name);
}
void SolarSpace::AddSun(std::shared_ptr<Sun> sun) {
	suns.push_back(sun);
}
void SolarSpace::AddPlanet(std::shared_ptr<Planet> planet) {
	planets.push_back(planet);
}
SolarSpace::~SolarSpace()
{
	std::cout << "SolarSpace "<<name<<" destroyed" << std::endl;
};
*/